//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa2
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"
#include"List.h"

int main(void){
    Graph G = newGraph(5);
    List L = newList();
    addEdge(G,1,2);
    addEdge(G,2,3);
    addEdge(G,3,4);
    addEdge(G,3,5);

    printf("order: %d\n",getOrder(G));
    printf("size: %d\n",getSize(G));
    
    BFS(G,1);
    getPath(L,G,4);
    printf("source: %d\n",getSource(G));
    for(int i = 0; i < getOrder(G); i++){
        printf("%d: %d\n",i,getParent(G,i));
        printf("%d: %d\n",i,getDist(G,i));
    }
    printList(stdout,L);
    printf("\n");

    freeGraph(&G);
    freeList(&L);
    return 0;
}

