/*  TryThis7
 *
 *  Very simple example of coding an adjacency matrix
 *
 *  Created by Sally Goldin, 3 March 2020
 *
 *  [YOUR NAME]  [YOUR ID]
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXVERT 10

/* Array of vertices. 
 * Vertices have numeric keys and no additional data
 */
int vertices[MAXVERT];


/* keep track of how many vertices we have */
int vertexcount = 0; 


/* Matrix of edges.
 * edges[x][y] is an edge between the xth and yth vertex
 * in the vertices array. If the value is 0, no edge
 * exists. If the value is 1, an edge exists 
 */
int edges[MAXVERT][MAXVERT];

/* Check to see if the vertices array
 * holds a vertex with the specified key.
 * If so, return the index into the array.
 * Otherwise return -1
 */
int findVertex(int key)
{
  int found = -1;
  int i = 0;
  for (i = 0; (i < vertexcount) && (found < 0); i++)
    {
    if (vertices[i] == key)
	found = i;
    }
  return found;
}


int main()
{
  char inputline[32];
  int bDone = 0;
  int key1, key2;
  int startIndex, endIndex; 
  printf("First let's create some vertices!\n");
  while (!bDone)
    {
    printf("Enter a positive 3 digit integer (negative to stop): ");
    fgets(inputline,sizeof(inputline),stdin);
    sscanf(inputline,"%d",&key1);
    if (key1 < 0)
       bDone = 1;
    else if (vertexcount < MAXVERT)
      {
      vertices[vertexcount] = key1;
      vertexcount++;	
      }
    else
      {
      printf("Sorry, you've defined the max number of vertices\n");
      bDone = 1;	
      }
    }
  
  bDone = 0;
  printf("\nNow let's create some edges!\n");
  while (!bDone)
    {
    printf("Enter key for start vertex (negative to stop): ");
    fgets(inputline,sizeof(inputline),stdin);
    sscanf(inputline,"%d",&key1);
    if (key1 < 0)
      bDone = 1;
    else
      {
      startIndex = findVertex(key1);
      if (startIndex >= 0)
	{
        printf("Enter key for end vertex: ");
	fgets(inputline,sizeof(inputline),stdin);
	sscanf(inputline,"%d",&key2);
	endIndex = findVertex(key2);
	if (endIndex >= 0)
	   {
	   printf("Creating edge from '%d' to '%d'\n",key1,key2);
	   /* ADD CODE HERE TO CREATE THE EDGE */
	   }
        else
	   printf("End vertex does not exist!\n");
	}
      else 
	printf("Start vertex does not exist!\n");
      } 
    } 

  bDone = 0;
  printf("\nPrint adjacency relationships\n");
  while (!bDone)
    {
    printf("Enter key whose adjacent vertices you want (negative to stop): ");
    fgets(inputline,sizeof(inputline),stdin);
    sscanf(inputline,"%d",&key1);
    if (key1 < 0)
      bDone = 1;
    else
      {
      startIndex = findVertex(key1);
      if (startIndex >= 0)
	{
	printf("The following vertices are adjacent to vertex '%d'\n",
		 key1);
        /* WRITE CODE HERE TO PRINT THE KEYS OF ALL VERTICES
         * THAT ARE ADJACENT TO VERTEXT 'key1' 
         */
	}
      else 
	printf("Specified vertex does not exist!\n");
      } 
    } 

}
