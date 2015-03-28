/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Graph.h"
#define MAX_LEN 300

int main(int argc, char* argv[])
{
	char line[MAX_LEN];
	int size = 0;
	graphG G;
	
	if(argc != 3)
	{
		printf("Wrong Usage: input file output file");
		exit(1);
	}
	
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");
	if(in == NULL || out == NULL)
	{
		printf("File does not exist.");
		exit(1);
	}
	
	//Reads first line and gets size for graph
	fscanf(in, "%d", &size);
	G = newGraph(size);
	
	//get vertices from file to graph
	int v1, v2;
	while(fgets(line, MAX_LEN, in) != NULL)
	{
		fscanf(in, "%d", &v1);
		fscanf(in, "%d", &v2);
		
		if(v1 == 0 && v2 == 0)
			break;
		addEdge(G, v1, v2);
	}
	
	printGraph(out, G);
	
	//gets source and destination for each vertex using BFS
	int s, d;
	List L;
	while(fgets(line, MAX_LEN, in) != NULL)
	{
		fscanf(in, "%d", &s);
		fscanf(in, "%d", &d);
		
		if(s == 0 && d == 0)
			break;
	
		L = newList();
		BFS(G, s);
		getPath(L, G, d);
		
		//prints to the out file
		if(getDist(G, d) != INF)
		{
			fprintf(out,"\nThe distance from %d to %d is %d", s, d, getDist(G, d));
			fprintf(out, "\n A shortest %d-%d path is: ", s, d);
			printList(out, L);
			fprintf(out, "\n");
		}
		else
		{
			fprintf(out,"\nThe distance from %d to %d is infinity.", s, d);
			fprintf(out, "\nNo %d-%d path exists", s, d);
			fprintf(out, "\n");
		}
		freeList(&L);	
	}
	freeGraph(&G);
	fclose(in);
	fclose(out);
	
	return(0);	
}
