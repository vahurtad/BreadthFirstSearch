/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[])
{
   int i, s, max, d, size = 20;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   graphG G = NULL;

   printf("----Graph ----\n");
   G = newGraph(size);
   for(i = 1; i < size; i++)
   {
      if(i%5 != 0)  
		addEdge(G, i, i+1);
      if(i <= 15) 
		addEdge(G, i, i+5);
   }
   
   printGraph(stdout, G);

   for(s = 1; s <= size; s++)
   {
      BFS(G, s);
      max = getDist(G, 1);
      for(i = 2; i <= size; i++)
     {
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }
   
   printf("\nSource is 1\n");
   BFS(G,1);
   getPath(C, G, 20);
   getPath(P, G, 1);
   printf("The shortest path from source %d to vertex 20 is: ", getSource(G));
   printList(stdout, C);
   printf("\nThe distance from source %d to vertex 20 is: %d\n", getSource(G), getDist(G,20));
   clear(C);
   clear(P);
   
   printf("\nSource is 10\n");
   BFS(G, 10);
   getPath(C, G, 20);
   getPath(P, G, 10);
   printf("The shortest path from source %d to vertex 20 is: ", getSource(G));
   printList(stdout, C);
   printf("\nThe distance from source %d to vertex 20 is: %d\n", getSource(G), getDist(G,20));
    
   clear(C);
   clear(P);
   
   printf("\nSource is 20\n");
   BFS(G, 20);
   getPath(C, G, 20);
   getPath(P, G, 20);
   printf("The shortest path from source %d to vertex 20 is: ", getSource(G));
   printList(stdout, C);
   printf("\nThe distance from source %d to vertex 20 is: %d\n", getSource(G), getDist(G,20));   
   
   clear(C);
   clear(P);
   
   printf("\nGraph is now deleted.\n");
   makeNull(G);
   printGraph(stdout, G);

   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);
}
