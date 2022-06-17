//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa3
#include<stdio.h>
#include<stdlib.h>

#include"Graph.h"
#include"List.h"

int main(void){
    Graph A = newGraph(100);
    List L = newList();
    for (int i = 1; i <= 100; i++){
        if (getDiscover(A, i) != UNDEF){
            printf("1\n");
        }
    }
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    for (int i = 1; i <= 100; i++) {
        prepend(L, i);
    }
    DFS(A, L);
    if (getDiscover(A, 100) != 1) printf("2\n");
    if (getDiscover(A, 64) != 73) printf("3\n");
    if (getDiscover(A, 4) != 80) printf("4\n");
    DFS(A, L);
    if (getDiscover(A, 4) != 126) printf("5\n");
    if (getDiscover(A, 63) != 117) printf("6\n");
    DFS(A, L);
    if (getDiscover(A, 65) != 71) printf("7\n");
    if (getDiscover(A, 1) != 199) printf("8\n");
    printf("getting to the end with no errors\n");
    return 0;
}