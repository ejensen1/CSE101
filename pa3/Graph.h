//Name: Elliott Jensen
//CruzID: egjensen
//Assignment: pa3
#include"List.h"
#define INF -1
#define NIL -2
#define UNDEF -3
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
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
//int getNumComponents(Graph G);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph g, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
bool isReflexive(Graph G, int x);
#endif
