//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa3
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj
{
    List *adj_arr; // adjacency array
    int *par_arr;  // parents array
    int *col_arr;  // color array; w=0, g=1, b=2
    int *dist_arr; // distance array
    int *discover_arr;
    int *finish_arr;
    int order;
    int size;
    int source;
    //int num_components;
    //List *comp_arr;
} GraphObj;

/*** Constructors-Desctructors ***/

Graph newGraph(int n)
{
    Graph G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    //G->num_components = 0;
    G->adj_arr = (List *)calloc(n + 1, sizeof(List));
    //G->comp_arr = (List *)calloc(n + 1, sizeof(List));
    G->par_arr = (int *)calloc(n + 1, sizeof(int));
    G->col_arr = (int *)calloc(n + 1, sizeof(int));
    G->dist_arr = (int *)calloc(n + 1, sizeof(int));
    G->discover_arr = (int *)calloc(n + 1, sizeof(int));
    G->finish_arr = (int *)calloc(n + 1, sizeof(int));
    for (int i = 1; i < n + 1; i++)
    {
        G->dist_arr[i] = INF;
        G->col_arr[i] = WHITE;
        G->par_arr[i] = NIL;
        G->adj_arr[i] = newList();
        //G->comp_arr[i] = newList();
        G->discover_arr[i] = UNDEF;
        G->finish_arr[i] = UNDEF;
    }
    return G;
}

void freeGraph(Graph *pG)
{
    if (pG == NULL)
    {
        fprintf(stderr, "Graph Error: calling freeGraph() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < getOrder(*pG) + 1; i++)
    {
        freeList(&((*pG)->adj_arr[i]));
        //freeList(&((*pG)->comp_arr[i]));
    }
    free((*pG)->par_arr);
    free((*pG)->adj_arr);
    //free((*pG)->comp_arr);
    free((*pG)->col_arr);
    free((*pG)->dist_arr);
    free((*pG)->discover_arr);
    free((*pG)->finish_arr);
    free(*pG);
    *pG = NULL;
    return;
}

/*** Access functions ***/

int getOrder(Graph(G))
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getSize on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getSoruce on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

int getParent(Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getParent() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->par_arr[u];
}

int getDist(Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getDist() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->dist_arr[u];
}

void getPath(List L, Graph G, int u)
{
    if (L == NULL)
    {
        fprintf(stderr, "Graph Error: calling getPath on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getPath on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    List P = newList();
    int curr_node = u;
    while (curr_node != G->source)
    {
        prepend(P, curr_node);
        curr_node = G->par_arr[curr_node];
        if (curr_node == NIL)
        {
            append(L, NIL);
            return;
        }
    }
    prepend(P, G->source);
    for (moveFront(P); index(P) >= 0; moveNext(P))
    {
        append(L, get(P));
    }
    freeList(&P);
    return;
}

int getDiscover(Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getDiscover on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || (u > getOrder(G)))
    {
        fprintf(stderr, "Graph Error: calling getDiscover when u is outside of range\n");
        exit(EXIT_FAILURE);
    }
    return G->discover_arr[u];
}

int getFinish(Graph G, int u)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getFinish on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || (u > getOrder(G)))
    {
        fprintf(stderr, "Graph Error: calling getFinish when u is outside of range\n");
        exit(EXIT_FAILURE);
    }
    return G->finish_arr[u];
}

/*
int getNumComponents(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getNumComponents on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->num_components;
}
*/
/*** Manipulation procedures ***/

// this may have memory leaks because clear from List.c does not free nodes
void makeNull(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling makeNULL on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G); i++)
    {
        clear(G->adj_arr[i]);
    }
    return;
}

void addEdge(Graph G, int u, int v)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling addEdege on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    if ((u < 1) || (u > getOrder(G)))
    {
        fprintf(stderr, "Graph Error: calling addEdge; %d is not a vertex\n", u);
        exit(EXIT_FAILURE);
    }
    if ((v < 1) || (v > getOrder(G)))
    {
        fprintf(stderr, "Graph Error: callign addEdge; %d is not a vertex\n", v);
        exit(EXIT_FAILURE);
    }

    moveFront(G->adj_arr[u]);
    while ((index(G->adj_arr[u]) != -1) && (get(G->adj_arr[u]) < v))
    {
        moveNext(G->adj_arr[u]);
    }
    if (index(G->adj_arr[u]) == -1)
    {
        append(G->adj_arr[u], v);
    }
    else
    {
        insertBefore(G->adj_arr[u], v);
    }
    moveFront(G->adj_arr[v]);
    while ((index(G->adj_arr[v]) != -1) && (get(G->adj_arr[v]) < u))
    {
        moveNext(G->adj_arr[v]);
    }
    if (index(G->adj_arr[v]) == -1)
    {
        append(G->adj_arr[v], u);
    }
    else
    {
        insertBefore(G->adj_arr[v], u);
    }
    G->size += 1;
    //append(G->adj_arr[u],v);
    //append(G->adj_arr[v],u);
    return;
}

void addArc(Graph G, int u, int v)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling addArc on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    
    if ((u < 1) || (u > getOrder(G)))
    {
        fprintf(stderr, "Graph Error: calling addArc; %d is not a vertex\n", u);
        exit(EXIT_FAILURE);
    }
    if ((v < 1) || (v > getOrder(G)))
    {
        fprintf(stderr, "Graph Error: callign addArc; %d is not a vertex\n", v);
        exit(EXIT_FAILURE);
    }
    
    moveFront(G->adj_arr[u]);
    while ((index(G->adj_arr[u]) != -1) && (get(G->adj_arr[u]) < v))
    {
        moveNext(G->adj_arr[u]);
    }
    if (index(G->adj_arr[u]) == -1)
    {
        append(G->adj_arr[u], v);
    }
    else
    {
        insertBefore(G->adj_arr[u], v);
    }

    G->size++;
    return;
}

void BFS(Graph G, int s)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling BFS on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    int curr_node;
    for (int i = 1; i < getOrder(G) + 1; i++)
    {
        G->dist_arr[i] = INF;
        G->col_arr[i] = WHITE;
        G->par_arr[i] = NIL;
    }
    G->source = s;
    G->col_arr[s] = GRAY;
    G->dist_arr[s] = 0;
    G->par_arr[s] = NIL;
    List Q = newList();
    append(Q, s);

    while (!isEmpty(Q))
    {
        moveBack(Q);
        curr_node = get(Q);
        deleteBack(Q);
        for (moveFront(G->adj_arr[curr_node]); index(G->adj_arr[curr_node]) >= 0; moveNext(G->adj_arr[curr_node]))
        {
            if (G->col_arr[get(G->adj_arr[curr_node])] == WHITE)
            {
                G->col_arr[get(G->adj_arr[curr_node])] = GRAY;
                G->dist_arr[get(G->adj_arr[curr_node])] = G->dist_arr[curr_node] + 1;
                G->par_arr[get(G->adj_arr[curr_node])] = curr_node;
                prepend(Q, get(G->adj_arr[curr_node]));
            }
        }
        G->col_arr[curr_node] = BLACK;
    }
    freeList(&Q);
    return;
}

void Visit(Graph G, int x, int *time)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling Visit() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    //append(G->comp_arr[G->num_components], x);
    G->discover_arr[x] = (++(*time));
    G->col_arr[x] = GRAY;
    for (moveFront(G->adj_arr[x]); index(G->adj_arr[x]) >= 0; moveNext(G->adj_arr[x]))
    {
        if (G->col_arr[get(G->adj_arr[x])] == WHITE)
        {
            G->par_arr[get(G->adj_arr[x])] = x;
            Visit(G, get(G->adj_arr[x]), time);
        }
    }

    G->col_arr[x] = BLACK;
    G->finish_arr[x] = (++(*time));
    return;
}

void DFS(Graph G, List S){
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling DFS() on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (S == NULL)
    {
        fprintf(stderr, "Graph Error: calling DFS() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G))
    {
        fprintf(stderr, "Graph Error: callign DFS() when length of S != order of G\n");
        fprintf(stderr, "length: %d\n", length(S));
        fprintf(stderr, "order: %d\n", getOrder(G));
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G)+1; i++)
    {
        G->col_arr[i] = WHITE;
        G->par_arr[i] = NIL;
        G->finish_arr[i] = 0;
        G->discover_arr[i] = 0;
    }
    
    int time = 0;
    for (moveFront(S); index(S) >= 0; moveNext(S)){
        if (G->col_arr[get(S)] == WHITE)
        {
            //G->num_components += 1;
            Visit(G, get(S), &time);
        }
    }
//---------------------------------
// this was added to fix the tests that called dfs multiple times in a row

    List L = newList();
    for(moveFront(S);index(S)>=0;moveNext(S)){
        if(index(S)==0){
            append(L,get(S));
            continue;
        }
        moveFront(L);
        while ((index(L)!=-1)&&(getFinish(G,get(S))>getFinish(G,get(L)))){
            moveNext(L);
        }
        if(index(L)==-1){
            append(L,get(S));
        }else{
            insertBefore(L,get(S));
        }
    }
    clear(S);
    
    for(moveFront(L);index(L)>=0;moveNext(L)){
        prepend(S,get(L));
    }
    freeList(&L);
    //L = reverse(L);
    //S=copyList(L);
    //S = reverse(L);
    //--------------------------
    return;
}

/*** Other operations ***/

Graph transpose(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graphh Error: calling transpose on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    Graph T = newGraph(getOrder(G));
    for (int i = 1; i < getOrder(G) + 1; i++)
    {
        for (moveFront(G->adj_arr[i]); index(G->adj_arr[i]) >= 0; moveNext(G->adj_arr[i]))
        {
            addArc(T, get(G->adj_arr[i]), i);
        }
    }
    return T;
}

Graph copyGraph(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    Graph C = newGraph(getOrder(G));
    for (int i = 1; i < getOrder(G); i++)
    {
        for (moveFront(G->adj_arr[i]); index(G->adj_arr[i]) >= 0; moveNext(G->adj_arr[i]))
        {
            addArc(C, i, get(G->adj_arr[i]));
        }
    }
    return C;
}

void printGraph(FILE *out, Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling printGraph on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G) + 1; i++)
    {
        fprintf(out, "%d: ", i);
        for (moveFront(G->adj_arr[i]); ((index(G->adj_arr[i]) != -1) && (i < getOrder(G) + 1)); moveNext(G->adj_arr[i]))
        {
            fprintf(out, "%d", get(G->adj_arr[i]));
            if (index(G->adj_arr[i]) != (length(G->adj_arr[i]) - 1))
            {
                fprintf(out, " ");
            }
        }
        fprintf(out, "\n");
    }
    return;
}
/*
void printComponents(FILE *out, Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling printGraph on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G) + 1; i++)
    {
        if (length(G->comp_arr[i]) == 0)
        {
            break;
        }
        fprintf(out, "Component %d: ", i);
        for (moveFront(G->comp_arr[i]); ((index(G->comp_arr[i]) != -1) && (i < getOrder(G) + 1)); moveNext(G->comp_arr[i]))
        {
            fprintf(out, "%d", get(G->comp_arr[i]));
            if (index(G->comp_arr[i]) != (length(G->comp_arr[i]) - 1))
            {
                fprintf(out, " ");
            }
        }
        fprintf(out, "\n");
    }
    return;
}

bool isReflexive(Graph G, int x)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling isReflexive() on NULL graph refernce\n");
        exit(EXIT_FAILURE);
    }
    if ((x < 1) || (x > getOrder(G)))
    {
        fprintf(stderr, "Graph Error: calling isReflexive when x: %d is out of range\n", x);
        exit(EXIT_FAILURE);
    }
    if (length(G->adj_arr[x]) == 0)
    {
        return false;
    }
    for (moveFront(G->adj_arr[x]); index(G->adj_arr[x]) >= 0; moveNext(G->adj_arr[x]))
    {
        if (get(G->adj_arr[x]) == x)
        {
            return true;
        }
    }
    return false;
}
*/