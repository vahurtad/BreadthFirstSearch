/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------

#include <stdlib.h>
#include "List.h"
#include "Graph.h"

// Private Structs -----------------------------------------------------------
typedef struct Graph
{
	List* a;
	int* color;
	int* parent;
	int* distance;
	int vertices, edges, source;
	////order  -- size -- 
} Graph;

// Constructors-Destructors ---------------------------------------------------
/* Creates a new Graph object reference with initialized fields */
graphG newGraph(int n)
{
	graphG g = malloc(sizeof(struct Graph));
	g->vertices = n;
	g->edges = 0;
	g->source = NIL;
	g->color = calloc(n+1, sizeof(int));
	g->parent = calloc(n+1, sizeof(int));
	g->distance = calloc(n+1, sizeof(int));
	g->a = calloc(n+1, sizeof(List));
	
	int i;
	for(i = 0; i <= n; i++)
	{
		g->color[i] = WHITE;
		g->distance[i] = INF;
		g->parent[i] = NIL;
		g->a[i] = newList();
	}
	return g;	
}
/* Frees all synamic memory associated with the graph then sets it to null*/
void freeGraph(graphG* pG)
{
	if(!(pG == NULL) && !(*pG == NULL))
	{
		int i;
		for(i = 1; i <= (*pG)->vertices; i++)
			freeList(&(*pG)->a[i]);
	}
	free((*pG)->a);
	free((*pG)->color);
	free((*pG)->distance);
	free((*pG)->parent);
	
	free(*pG);
	*pG = NULL;
}

// Access functions -----------------------------------------------------------
/* Returns corresponding field values. */
int getOrder(graphG G)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	return G->vertices;
}

int getSize(graphG G)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	return G->edges;
}

int getSource(graphG G)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	return G->source;
}

int getParent(graphG G, int u)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	
	if(u < 1 || u > getOrder(G))
		exit(1);
	return G->parent[u];
}

int getDist(graphG G, int u)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
		exit(1);
	return G->distance[u];
}

void getPath(List L, graphG G, int u)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	if(u < 1 || u > getOrder(G))
		exit(1);
		
	if(getSource(G) == NIL)
		exit(1);
		
	int s = getSource(G);
	if(u == s)
		append(L, s);
	else if(G->parent[u] == NIL)
		append(L, NIL);
	else
	{
		getPath(L, G, G->parent[u]);
		append(L,u);
	}
}

// Manipulation procedures ----------------------------------------------------
/* Deletes all edges of G, restoring to its original state. */
void makeNull(graphG G)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	int i;
	for(i = 1; i <= getOrder(G); i++)
		clear(G->a[i]);
	G->edges = 0;
}
/* Inserts new edge joining u to v. */
void addEdge(graphG G, int u, int v)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	
	if(u < 1 || u > getOrder(G))
	{
		printf("Edge is out of bound.");
		exit(1);
	}
	
	if(v < 1 || v > getOrder(G))
	{
		printf("Edge is out of bound.");
		exit(1);
	}
	
	List U = G->a[u];
	List V = G->a[v];
	
	insertionSort(U, v);
	insertionSort(V, u);
	G->edges++;
}

/* Helper function for adding objects to the graph, it sorts objects in order. */
void insertionSort(List L, int u)
{
	if(length(L) == 0)
	{
		append(L, u);
		return;
	}
	
	for(moveTo(L,0); getIndex(L) != -1; moveNext(L))
	{
		if(getElement(L) > u)
		{
			insertBefore(L,u);
			break;
		}
	}
	if(getIndex(L) == -1)
		append(L, u);
}

/* Inserts a new directed edge from u to v. */
void addArc(graphG G, int u, int v)
{
	if(G == NULL)
	{
		printf("Empty Graph.");
		exit(1);
	}
	
	if(u < 1 || u > getOrder(G))
	{
		printf("Edge is out of bound.");
		exit(1);
	}
	
	if(v < 1 || v > getOrder(G))
	{
		printf("Edge is out of bound.");
		exit(1);
	}
	insertionSort(G->a[u], v);
	G->edges++;
}

/* Runs Breadth-First Search algorithm on G, getting color, distance, parent and source fields. */
void BFS(graphG G, int s)
{
	int u;
	for(u = 1; u <= getOrder(G); u++)
	{
		G->color[u] = WHITE;
		G->distance[u] = INF;
		G->parent[u] = NIL;
	}
	//INITIALIZE SOURCE
	G->source = s;
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	
	List Q = newList();
	append(Q, s);

	while(length(Q) > 0)
	{
		int h = front(Q);
		deleteFront(Q);
		List adj = G->a[h];

		for(moveTo(adj, 0); getIndex(adj) != -1; moveNext(adj))
		{
			int v = getElement(adj);
			
			if(G->color[v] == WHITE)
			{
				G->color[v] = GRAY;
				G->distance[v] = G->distance[h] + 1;
				G->parent[v] = h;
				append(Q, v);
			}
		}
		G->color[h] = BLACK;
	}
	freeList(&Q);
}

// Other operations -----------------------------------------------------------
/* Prints the adjacency list of G */

void printGraph(FILE *out, graphG G)
{
	int i;
	for(i = 1; i <= G->vertices; i++)
	{
		fprintf(out, "%d:", i);
		printList(out, G->a[i]);
		fprintf(out, "\n");
	}
	
}
