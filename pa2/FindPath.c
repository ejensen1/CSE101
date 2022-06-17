//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa2
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include"Graph.h"

int main(int argc, char * argv[]){
    FILE *in, *out;
    int node_count, i, j;
    Graph G;
    List L;

    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n",argv[0]);
        exit(1);
    }
    in = fopen(argv[1],"r");
    if (in == NULL){
        printf("Unable to open file %s for reading\n",argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    fscanf(in,"%d\n", &node_count);
    G = newGraph(node_count);

    while((fscanf(in,"%d" "%d", &i, &j))!=EOF){
        if ((i == 0) && (j == 0)){
            break;
        }
        addEdge(G,i,j);
    }

    // should be out instead of stdout
    printGraph(out,G);

    L = newList();
    while((fscanf(in,"%d" "%d", &i, &j))!=EOF){
        if ((i == 0) && (j == 0)){
            break;
        }
        fprintf(out,"\n");
        clear(L);
        BFS(G,i);
        getPath(L,G,j);
        moveBack(L);

        
        if ((getDist(G,j) == INF) ||(get(L) == NIL) ){
            fprintf(out,"The distance from %d to %d is infinity\n",i,j);
            fprintf(out,"No %d-%d path exists\n",i,j);
        } else {
            fprintf(out,"The distance from %d to %d is %d\n",i,j,getDist(G,j));
            fprintf(out,"A shortest %d-%d path is: ",i,j);
            printList(out,L);
            fprintf(out,"\n");
        }
    }

    freeList(&L);
    freeGraph(&G);

    return 0;
}
