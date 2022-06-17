//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa2
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj{
    List *adj_arr; // adjacency array
    int *par_arr; // parents array
    int *col_arr; // color array; w=0, g=1, b=2
    int *dist_arr; // distance array
    int order;
    int size;
    int source;
} GraphObj;

/*** Constructors-Desctructors ***/

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    G->adj_arr = (List *)calloc(n+1,sizeof(List));
    G->par_arr = (int *)calloc(n+1, sizeof(int));
    G->col_arr = (int *)calloc(n+1, sizeof(int));
    G->dist_arr = (int*)calloc(n+1, sizeof(int));
    for (int i = 1; i < n+1; i++){
        G->dist_arr[i] = INF;
        G->col_arr[i] = WHITE;
        G->par_arr[i] = NIL;
        G->adj_arr[i] = newList();
    }
    return G;
}

void freeGraph(Graph* pG){
    if (pG == NULL){
        fprintf(stderr,"Graph Error: calling freeGraph() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < getOrder(*pG)+1;i++){
        freeList(&((*pG)->adj_arr[i]));
    }
    free((*pG)->par_arr);
    free((*pG)->adj_arr);
    free((*pG)->col_arr);
    free((*pG)->dist_arr);
    free(*pG);
    *pG = NULL;
    return;
}

/*** Access functions ***/

int getOrder(Graph(G)){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getOrder() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G){
    if (G == NULL){
        fprintf(stderr,"Graph Error: calling getSize on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getSoruce on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

int getParent(Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getParent() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->par_arr[u];
}

int getDist(Graph G, int u){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getDist() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->dist_arr[u];
}

void getPath(List L, Graph G, int u){
    if (L == NULL){
        fprintf(stderr, "Graph Error: calling getPath on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling getPath on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    List P = newList();
    int curr_node = u;
    while(curr_node != G->source){
        prepend(P,curr_node);
        curr_node = G->par_arr[curr_node];
        if (curr_node == NIL){
            append(L,NIL);
            return;
        }
    }
    prepend(P,G->source);
    for (moveFront(P);index(P)>=0;moveNext(P)){
        append(L,get(P));
    }
    freeList(&P);
    return;
}

/*** Manipulation procedures ***/

// this may have memory leaks because clear from List.c does not free nodes
void makeNull(Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling makeNULL on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G); i++){
        clear(G->adj_arr[i]);
    }
    return;
}

void addEdge(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling addEdege on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || (u > getOrder(G))){
        fprintf(stderr, "Graph Error: calling addEdge; %d is not a vertex\n",u);
        exit(EXIT_FAILURE);
    }
    if ((v < 1) || (v > getOrder(G))){
        fprintf(stderr, "Graph Error: callign addEdge; %d is not a vertex\n",v);
        exit(EXIT_FAILURE);
    }

    // 

    /*
    for(moveFront(G->adj_arr[u]);index(G->adj_arr[u]);moveNext(G->adj_arr[u])){
        if (index(G->adj_arr[u]) == 0){
            append
    */
    moveFront(G->adj_arr[u]);
    while((index(G->adj_arr[u]) != -1) && (get(G->adj_arr[u]) < v)){
        moveNext(G->adj_arr[u]);
    }
    if(index(G->adj_arr[u]) == -1){
        append(G->adj_arr[u],v);
    } else {
        insertBefore(G->adj_arr[u],v);
    }
    moveFront(G->adj_arr[v]);
    while((index(G->adj_arr[v]) != -1) && (get(G->adj_arr[v]) < u)){
        moveNext(G->adj_arr[v]);
    }
    if(index(G->adj_arr[v]) == -1){
        append(G->adj_arr[v],u);
    } else {
        insertBefore(G->adj_arr[v],u);
    }
    G->size+=1;
    //append(G->adj_arr[u],v);
    //append(G->adj_arr[v],u);
    return;
}

void addArc(Graph G, int u, int v){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling addArc on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || (u > getOrder(G))){
        fprintf(stderr, "Graph Error: calling addArc; %d is not a vertex\n",u);
        exit(EXIT_FAILURE);
    }
    if ((v < 1) || (v > getOrder(G))){
        fprintf(stderr, "Graph Error: callign addArc; %d is not a vertex\n",v);
        exit(EXIT_FAILURE);
    }
    append(G->adj_arr[u],v);
    G->size++;
    return;
}

void BFS(Graph G, int s){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling BFS on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    int curr_node;
    for (int i = 1; i < getOrder(G) + 1; i++){
        G->dist_arr[i] = INF;
        G->col_arr[i] = WHITE;
        G->par_arr[i] = NIL;
    }
    //List adj_list;
    G->source = s;
    G->col_arr[s] = GRAY;
    G->dist_arr[s] = 0;
    G->par_arr[s] = NIL;
    List Q = newList();
    append(Q,s);

    while(!isEmpty(Q)){
        moveBack(Q);
        curr_node = get(Q);
        deleteBack(Q);
        //adj_list = copyList(G->adj_arr[curr_node]);
        //printf("current adj_list\n");
        //printf("\n");
        for(moveFront(G->adj_arr[curr_node]);index(G->adj_arr[curr_node])>=0;moveNext(G->adj_arr[curr_node])){
            if (G->col_arr[get(G->adj_arr[curr_node])] == WHITE){
                G->col_arr[get(G->adj_arr[curr_node])] = GRAY;
                G->dist_arr[get(G->adj_arr[curr_node])] = G->dist_arr[curr_node] + 1;
                G->par_arr[get(G->adj_arr[curr_node])] = curr_node;
                prepend(Q,get(G->adj_arr[curr_node]));
            }
        }
        G->col_arr[curr_node] = BLACK;
    }
    freeList(&Q);
    return;
}


/*** Other operations ***/

void printGraph(FILE* out, Graph G){
    if (G == NULL){
        fprintf(stderr, "Graph Error: calling printGraph on NULL graph reference");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G)+1;i++){
        fprintf(out,"%d: ",i);
        for(moveFront(G->adj_arr[i]);((index(G->adj_arr[i]) != -1) && (i < getOrder(G)+1));moveNext(G->adj_arr[i])){
            fprintf(out,"%d",get(G->adj_arr[i]));
            if (index(G->adj_arr[i]) != (length(G->adj_arr[i]) - 1)){
                fprintf(out," ");
            }
        } 
        fprintf(out,"\n");
    }
    return;
}


/*
int main(void){
    Graph G = newGraph(5);
    List L = newList();

    addEdge(G,1,2);
    addEdge(G,2,3);
    addEdge(G,3,4);
    addEdge(G,3,5);

    BFS(G,1);
    getPath(L, G, 5);
    printList(stdout,L);
    printf("\n");
    printf("Success!\n");
    freeList(&L);
    freeGraph(&G);
    return 0;
}

// there needs to be an array of Lists
// the number of lists is equal to num_vertices
//
*/

