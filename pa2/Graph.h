//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa2
#include"List.h"
#define INF -1
#define NIL -2
#define WHITE 0
#define GRAY 1
#define BLACK 2
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
typedef struct GraphObj* Graph;
/*** Constructors-Descturctors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G , int u);
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph g, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
#endif
