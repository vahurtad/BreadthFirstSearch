/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------


#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include "List.h"

#define INF -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct Graph *graphG;

/*** Constructors-Destructors ***/
graphG newGraph(int n);
void freeGraph(graphG* pG);
/*** Access functions ***/
int getOrder(graphG G);
int getSize(graphG G);
int getSource(graphG G);
int getParent(graphG G, int u);
int getDist(graphG G, int u);
void getPath(List L, graphG G, int u);
/*** Manipulation procedures ***/
void makeNull(graphG G);
void addEdge(graphG G, int u, int v);
void insertionSort(List L, int u);
void addArc(graphG G, int u, int v);
void BFS(graphG G, int s);
/*** Other operations ***/
void printGraph(FILE* out, graphG G);

#endif
