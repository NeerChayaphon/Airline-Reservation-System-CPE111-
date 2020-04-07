/**
 *  networkWriter.c 
 *
 *  Writes a file that defines a network, by calling functions
 *  in the abstractNetwork ADT. The file it writes can be read
 *  by networkBuilder.c
 *
 *  Created by Sally Goldin, 15 March 2016 for CPE 113 (Lab 9-2)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractNetwork.h"
#include "networkWriter.h"

/*********************************************************************
 The network definition file is a text file. Its format is as follows.

  Line 1              NumVertices  bDirected     e.g.    "100  1"

  Following lines are either VERTEX lines or EDGE lines
  A VERTEX line must have the form

      VERTEX keyvalue              e.g. "VERTEX A"

  An EDGE line must have the form 

      EDGE key1 key2 weight        e.g. "EDGE A C 13"

  VERTEX and EDGE lines can be in any order, but both keys referenced
  in an EDGE line must have been mentioned in VERTEX lines earlier in
  the file. That is, both vertices must exist before they can be linked
  with an edge.

  (There should not be any quotation marks around the commands.)

  If the format of the file is bad, the readNetworkDefinition function returns
  an error status value. However, if the format is okay but there are semantic
  errors (e.g. trying to define a vertex or edge more than once, trying to
  create an edge before its vertices are defined, trying to define an edge
  more than once), the function simply prints an error message but then
  ignores the bad line.
 **************************************************************************
 */

/* free a list of adjacentKeys constructed by the getAdjacents function.
 * We free both the keys themselves and the array.
 */
void freeAdjacents(char** keyList, int count)
{
    int i = 0;
    for (i = 0; i < count; i++)
       free(keyList[i]);
    free(keyList);
}

/* Given an array of all the keys, write out all the edges.
 * For each key, we get the adjacents. Then we call findEdge to
 * get the weight for each edge.
 * If this is an undirected graph, we want to avoid duplicate edges.
 * NOT HANDLED YET
 *     pOut        Open file handle for output file
 *     keyArray    Keys to all the vertices in the network
 *     vertexCount Number of items in the keyArray
 */
int writeEdges(FILE* pOut, char* keyArray[], int vertexCount)
{
    int i = 0;
    int adj = 0;  /* index into the array of adjacents. */
    int weight = 0;
    int adjacentCount = 0;
    for (i = 0; i < vertexCount; i++)
       {    
       char ** endKeys = getAdjacentVertices(keyArray[i],&adjacentCount);
       if (adjacentCount < 0) /* key doesn't exist? should not happen! */
           continue;  /* just skip it */
       for (adj=0; adj < adjacentCount; adj++)
           {
           weight = findEdge(keyArray[i],endKeys[adj]);
           if (weight >= 0)
	     fprintf(pOut,"EDGE %s %s %d\n",keyArray[i],endKeys[adj],weight);
           }  
       freeAdjacents(endKeys,adjacentCount); 
       }
}

/* Main function to open and write the file.
 *    outputfile    Name of file to create.
 * Returns 1 if everything is fine, 0 if there is 
 * either a file error or an error accessing the network information.
 */
int writeNetwork(char* outputfile)
{
    int status = 1;  /* for returning success/failure */
    FILE * pOut = NULL;
    int vertexCount = 0;  /* actual number of vertices */
    char** allKeys = NULL; /* save all the keys in a local array */
    char* pKey = NULL;
    char* pKey2 = NULL;
    int maxVertices = getMaxVertices(); /* we'll use this to allocate the key array */ 
    if (maxVertices == 0)
       {
       printf("Error - network has not been initialized\n");
       return 0;
       }
    pOut = fopen(outputfile,"w");
    if (pOut == NULL)
       {
       status = 0;
       printf("Error - cannot open file %s\n", outputfile);
       } 
    else
       {
       /* write initialization information */
       allKeys = (char**) calloc(maxVertices,sizeof(char*));
       if (allKeys == NULL)
          {
          printf("Memory allocation error creating key array!\n");
          status = 0;
          }   
       else
          { 
          fprintf(pOut,"%d %d\n", maxVertices, isDirected());
          /* now write all the vertices */
          resetVertexList();
          pKey = getNextVertex();
          while (pKey != NULL)
            {
            allKeys[vertexCount++] = pKey;
            fprintf(pOut,"VERTEX %s\n",pKey); 
            pKey = getNextVertex();
            }
          /* Okay, now we need to write all the edges */
          writeEdges(pOut,allKeys,vertexCount);           
          }
       fclose(pOut);
       if (allKeys != NULL)
          free(allKeys);
       return status; 
       }
}   

