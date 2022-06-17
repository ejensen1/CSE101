//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa3
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include"Graph.h"

int main(int argc, char * argv[]){
    FILE *in, *out;
    int node_count, i, j;
    Graph G, T;
    List L, A;

    // set up the reading and writing of the input and output files
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

    // process the input file and create the graph
    fscanf(in,"%d\n", &node_count);
    G = newGraph(node_count);

    while((fscanf(in,"%d" "%d", &i, &j))!=EOF){
        if ((i == 0) && (j == 0)){
            break;
        }
        addArc(G,i,j);
    }

    fprintf(out,"Adjacency list representation of G:\n");
    printGraph(out,G);
    
    // generate the order that the vertices will be processed in DFS
    L = newList();
    for (int i = 1; i <getOrder(G)+1; i++){
        append(L,i);
    }
    
    // generate the topological sort using DFS of L
    DFS(G,L);

    T = transpose(G);

    // Create the trees of strongly connected components
    DFS(T,L);
   
    int branch_num = 0;
    for(moveBack(L);index(L)>=0;movePrev(L)){        
        if (getParent(T,get(L)) == NIL){
            branch_num++;
        }
    }

    fprintf(out,"\nG contains %d strongly connected components:\n",branch_num);

    branch_num=1;
    A = newList();
    for(moveBack(L);index(L)>=0;movePrev(L)){
        prepend(A,get(L));
        if (getParent(T,get(L)) == NIL){
            fprintf(out,"Component %d: ",branch_num);
            printList(out,A);
            clear(A);
            branch_num++;
            fprintf(out,"\n");
        }
    }

    freeList(&A);
    freeGraph(&G);
    freeGraph(&T);
    freeList(&L);
 
    return 0;
}