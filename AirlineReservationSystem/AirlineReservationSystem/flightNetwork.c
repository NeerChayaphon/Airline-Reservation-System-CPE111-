/*
 *  matrixGraph.c
 *
 *  Implements an abstractGraph using an adjacency matrix.
 *
 *  Key values are strings and are copied when vertices are inserted into
 *  the graph. Every vertex has a void* pointer to ancillary data which
 *  is simply stored.
 *
 *  Created by Sally Goldin, 12 March 2015 for CPE 113
 *  Solution to Lab 8-2
 *  Modified 9 March 2016 to remove edges when we remove a vertex
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractNetwork.h"
#include "abstractQueue.h"

#define WHITE 0
#define GRAY  1
#define BLACK 2

char* colorName[] = {"WHITE", "GRAY", "BLACK"};


/* Structure for the main vertex list.*/
typedef struct _vertex
{
    char * key;               /* key for this vertex */
    void * data;              /* ancillary data for this vertex */
    int index;                /* array index. Makes using the queue easier */
    int color;                /* used to mark nodes as visited */
    int dValue;               /* total weight so far, for Dijkstra's algo */
}  VERTEX_T;

VERTEX_T * vertices = NULL;   /* array of vertices. Will be allocated
                   * in initGraph based on maximum passed in.
                               */
int ** edges = NULL;          /* matrix (2D array) of edges. Will
                               * be allocated in initGraph     */
int maxVertices = 0;          /* set by initGraph */
int bGraphDirected = 0;       /* if true, this is a directed graph */
int vertexCount = 0;          /* keep track of the number of vertices */
                              /* updated in addVertex and removeVertex */
int lastIndex = -1;          /* last item in array that is in use */
                              /* could be > than vertexCount if we have
                   * removed some vertices
                               */
/** Private functions */

/* Finds the vertex that holds the passed key
 * (if any) and returns a pointer to that vertex.
 * Arguments
 *       key    -  Key we are looking for
 * Returns index of vertex in the vertices array, or -1
 * if not found.
 */
int findVertexByKey(char* key)
{
    int found = -1;
    int i = 0;
    /* loop through the array looking for the one we wnat */
    for (i=0; (i <= lastIndex) && (found < 0); i++)
       {
       if ((vertices[i].key != NULL) && (strcmp(vertices[i].key,key) == 0))
          {
      found = i;
      }
       }
    return found;
}

/* Finds the first unused slot in the vertices array.
 * This may be a slot make available by a 'remove', or
 * the slot after the current 'lastIndex'
 * Returns the first available index or -1 if array is full.
 * Updates lastIndex as a side effect if it returns lastIndex+1
 */
int findFirstUnused()
{
    int i = 0;
    int returnidx = -1;
    if (vertexCount < maxVertices)
      {
      for (i=0; i <= lastIndex; i++)
     {
     if (vertices[i].key == NULL)
        {
        returnidx = i;
            break;
            }
         }
      if (returnidx == -1) /* no slots in the middle of the array */
     {
     lastIndex++;
         returnidx = lastIndex;
         }
      }
    return returnidx;
}

/* Count adjacent vertices to a vertex.
 * Argument
 *    whichVertex   -   Index of vertex whose adjacent nodes we want to count
 * Returns integer value for count (could be zero)
 */
/*int countAdjacent(int whichVertex)
{
    int count = 0;
    int i = 0;
    for (i = 0; i <= lastIndex; i++)
       {
       if ((vertices[i].key != NULL) && (edges[whichVertex][i] > 0))
           count += 1;
       }
    return count;
}*/

/* Set all vertices to the passed color.
 * Argument
 *    A color constant
 * 12 Mar 2015 Also set pFrom to NULL
 */
void colorAll(int color)
{
    int i = 0;
    for (i = 0; i <= lastIndex; i++)
       {
       vertices[i].color = color;
       }
}

/* Execute a breadth first search from a vertex,
 * calling the function (*vFunction) on each vertex
 * as we visit it and color it black.
 * Arguments
 *    vIndex  - Index of the starting vertex
 */
void traverseBreadthFirst(int vIndex, void (*vFunction)(VERTEX_T*))
{
    queueClear();
    colorAll(WHITE);
    int adjacentIndex = -1;
    int i = 0;
    VERTEX_T * pCurrent = NULL;
    VERTEX_T * pAdjacent = NULL;
    enqueue(&vertices[vIndex]);   /* Our queue requires pointers as data */
    while (queueSize() > 0)
        {
        pCurrent = (VERTEX_T*) dequeue();
        if (pCurrent->color != BLACK)
           {
           (*vFunction)(pCurrent);
            pCurrent->color = BLACK;
            for (i = 0; i <= lastIndex; i++)
               {
           /* if there is an edge from current to this vertex */
               if ((vertices[i].key != NULL) && (edges[pCurrent->index][i] > 0))
          {
          pAdjacent = &vertices[i];
              if (pAdjacent->color != BLACK)
                 {
             enqueue(pAdjacent);
                 }
          } /* end if */
           } /* end for */
      }
       } /* end while queue has data */
}


/* Execute a depth first search from a single vertex,
 * calling the function (*vFunction) on the lowest level
 * vertex we visit, and coloring it black.
 * Arguments
 *    vIndex  - Index of the starting vertex
 */

void traverseDepthFirst(int vIndex, void (*vFunction)(VERTEX_T*))
{
    VERTEX_T * pAdjacent = NULL;
    int i = 0;
    for (i = 0; i <= lastIndex; i++)
        {
        /* if there is an edge from current to this vertex */
        if ((vertices[i].key != NULL) && (edges[vIndex][i] > 0))
       {
           if (vertices[i].color == WHITE)
           {
           vertices[i].color = GRAY;
               traverseDepthFirst(i,vFunction);
               }
       } /* end if this index is adjacent to vertex at vIndex*/
    } /* end looking at the adjacents */
    (*vFunction)(&vertices[vIndex]);
    vertices[vIndex].color = BLACK;
}


/* Function to print the information about a vertex
 * Argument
 *   pVertex   -   vertex we want to print
 */
void printVertexInfo(VERTEX_T* pVertex)
{
    printf("== Vertex key |%s| - data |%s|\n",
       pVertex->key, pVertex->data);
}


/********************************/
/** Public functions start here */
/********************************/

/* Initialize or reintialize the graph.
 * Argument
 *    max          - how many vertices can this graph
 *                   handle.
 *    bDirected    - If true this is a directed graph.
 *                   Otherwise undirected.
 * Returns 1 unless there is a memory allocation error,
 * in which case it returns zero.
 */
int initGraph(int max, int bDirected)
{
    int returnval = 1;
    clearGraph();
    bGraphDirected = bDirected;
    maxVertices = max;
    /* do the memory allocation */
    vertices = (VERTEX_T*) calloc(maxVertices,sizeof(VERTEX_T));
    if (vertices != NULL)
         {
     int i = 0;
         /* allocate an array of rows */
     edges = (int **) calloc(max,sizeof(int*));
         if (edges == NULL)
         returnval = 0;
         for (i=0; (i < max) && (returnval); i++)
             {
         /* allocate each row */
         edges[i] = (int*) calloc(max,sizeof(int));
         if (edges[i] == NULL)
             returnval = 0;
             /* if any allocation fails, we'll stop the loop */
             }
     }
    else
         {
     returnval = 0;
         }
    return returnval;
}


/* Free all memory associated with the graph and
 * reset all parameters.
 */
void clearGraph()
{
    int i;
    for (i = 0; i < maxVertices; i++)
       {
       if (vertices[i].key != NULL)
      free(vertices[i].key);  /* because it was strduped */
       free(edges[i]);
       }
    free(vertices);
    vertices = NULL;
    free(edges);
    edges = NULL;
    bGraphDirected = 0;
    maxVertices = 0;
    lastIndex = -1;
    vertexCount = 0;
}

/* Add a vertex into the graph.
 * Arguments
 *     key   -   Key value or label for the
 *               vertex
 *     pData -   Additional information that can
 *               be associated with the vertex.
 * Returns 1 unless there is an error, in which case
 * it returns a 0. An error could mean a memory allocation
 * error or running out of space, depending on how the
 * graph is implemented. Returns -1 if the caller tries
 * to add a vertex with a key that matches a vertex
 * already in the graph.
 */
int addVertex(char* key, void* pData)
{
    int retval = 1;
    int location  = findVertexByKey(key);
    if (location >=0)  /* key is already in the graph */
       {
       retval = -1;
       }
    else
       {
       char * pKeyval = strdup(key);
           if (pKeyval == NULL)
          {
      retval = 0;  /* allocation error */
      }
       else
          {
      int newloc = findFirstUnused();
          if (newloc < 0)
         retval = 0;  /* graph is full */
      else
         {
         vertices[newloc].key = pKeyval;
         vertices[newloc].data = pData;
             vertices[newloc].index = newloc;
         vertexCount++;
         }
      }
       }
    return retval;
}


/* Remove a vertex from the graph.
 * Arguments
 *     key   -   Key value or label for the
 *               vertex to remove
 * Returns a pointer to the data stored at that
 * vertex, or NULL if the vertex could not be
 * found.
 */
void* removeVertex(char* key)
{
   int i;
   void * pData = NULL; /* data to return */
   int idx = findVertexByKey(key);
   if (idx >= 0)
      {
      free(vertices[idx].key);
      vertices[idx].key = NULL;
      pData = vertices[idx].data;
      vertices[idx].data = NULL;
      vertices[idx].index = -1;
      vertexCount--;
      if (idx == lastIndex)
     lastIndex--;
      /* now remove any edges where this vertex
         is either the start or the end vertex
       */
      for (i=0; i < maxVertices; i++)
      {
      edges[idx][i] = 0;
          edges[i][idx] = 0;
          }
      }
   return pData;
}


/* Add an edge between two vertices
 * Arguments
 *    key1  -  Key for the first vertex in the edge
 *    key2  -  Key for the second vertex
 * Returns 1 if successful, 0 if failed due to
 * memory allocation error, or if either vertex
 * is not found. Returns -1 if an edge already
 * exists in this direction.
 */
int addEdge(char* key1, char* key2,unsigned int weight)
{
    int retval = 1;
    int fromidx = findVertexByKey(key1);
    int toidx = findVertexByKey(key2);
    if ((fromidx <0) || (toidx < 0))
       {
       retval = 0;
       }
    else if (edges[fromidx][toidx] != 0)
       {
       retval = -1;
       }
    else
       {
       edges[fromidx][toidx] = weight;
       /* If undirected, add an edge in the other direction */
       if ((retval) && (!bGraphDirected))
           edges[toidx][fromidx] = weight;
       }
    return retval;
}


/* Remove an edge between two vertices
 * Arguments
 *    key1  -  Key for the first vertex in the edge
 *    key2  -  Key for the second vertex
 * Returns 1 if successful, 0 if failed
 * because either vertex is not found or there
 * is no edge between these items.
 */
int removeEdge(char* key1, char* key2)
{
   int bOk = 1;
   int fromidx = findVertexByKey(key1);
   int toidx = findVertexByKey(key2);
   if ((fromidx < 0) || (toidx < 0))
       {
       bOk = 0;
       }
   else if (edges[fromidx][toidx] == 0) /* no edge to remove */
       {
       bOk = 0;
       }
   else
       {
       edges[fromidx][toidx] = 0;
       /* If undirected, remove edge in the other direction */
       if (!bGraphDirected)
           edges[toidx][fromidx] = 0;
 
       }
   return bOk;
}

/* Find a vertex and return its data
 * Arguments
 *    key  -  Key for the vertex to find
 * Returns the data for the vertex or NULL
 * if not found.
 */
void* findVertex(char* key)
{
    void* pData = NULL;
    int index = findVertexByKey(key);
    if (index >= 0)
       {
       pData = vertices[index].data;
       }
    return pData;
}



/* Return an array of copies of the keys for all nodes
 * adjacent to a node. The array and its
 * contents should be freed by the caller when it
 * is no longer needed.
 * Arguments
 *    key   -  Key for the node whose adjacents we want
 *    pCount - Return number of elements in the array
 * Returns array of char* which are the keys of adjacent
 * nodes. Returns number of adjacent vertices in pCount.
 * If pCount holds -1, the vertex does not exist.
 */
/*char** getAdjacentVertices(char* key, int* pCount)
{
    char** keyArray = NULL;
    int foundidx = findVertexByKey(key);
    if (foundidx >=0)
       {
       *pCount = countAdjacent(foundidx);
       if (*pCount > 0)
          {
      int dest = 0;
          int i = 0;
      keyArray = (char**) calloc(*pCount, sizeof(char*));
          if (keyArray != NULL)
         {
         for (i = 0; i <= lastIndex; i++)
            {
        if ((edges[foundidx][i] > 0) && (vertices[i].key != NULL))
            {
            keyArray[dest] = strdup(vertices[i].key);
            dest += 1;
            }
            }
         }
          }
       }
    else
       {
       *pCount = -1;
       }
    return keyArray;
} */


/* Print out all the nodes reachable from a node by a
 * breadth-first search.
 * Arguments
 *   startKey   -  Key for start vertex
 * Returns 1 if successful, -1 if the vertex does not exist.
 */
int printBreadthFirst(char* startKey)
{
   int retval = 1;
   if (vertexCount == 0)
      {
      printf("The graph is empty\n");
      }
   int foundidx = findVertexByKey(startKey);
   if (foundidx < 0)
      {
      printf("Vertex |%s| does not exist\n", startKey);
      retval = -1;
      }
   else
      {
      traverseBreadthFirst(foundidx,&printVertexInfo);
      }
   return retval;
}

/* Print out all the nodes by a depth-first search.
 */
/*void printDepthFirst()
{
   if (vertexCount == 0)
      {
      printf("The graph is empty\n");
      }
   else
      {
      int i = 0;
      colorAll(WHITE);
      for (i = 0; i <= lastIndex; i++)
         {
     if ((vertices[i].key != NULL) &&
         (vertices[i].color == WHITE))
        {
        printf("\nStarting new traversal from |%s|\n",
                   vertices[i].key);
        vertices[i].color = GRAY;
            traverseDepthFirst(i,&printVertexInfo);
        }
     }
      }
}*/

/**/

/* No-op function allows us to traverse without
 * doing anything other than setting colors
 * Argument
 *   pVertex   -   vertex - will be ignored
 */
void emptyFunction(VERTEX_T* pVertex)
{
}


/* Return information as to whether two vertices are
 * connected by a path.
 * Arguments
 *    key1 -  Key for the start vertex
 *    key2 -  Key for the second vertex to check
 * Returns 1 if the two vertices are connected, 0 if they
 * are not. Returns -1 if either vertex does not exist.
 */
int isReachable(char* key1, char* key2)
{
   int retval = 1;
   int startindex = findVertexByKey(key1);
   int endindex = findVertexByKey(key2);
   if ((startindex < 0) || (endindex < 0))
      {
      retval = -1;
      }
   else
      {
      traverseBreadthFirst(startindex,&emptyFunction);
      /* if after a breadth first traversal, we didn't reach the
       * the end vertex, it is not reachable.
       */
      if (vertices[endindex].color != BLACK)
          retval = 0;

      }
   return retval;

}

/* Return information as to whether two vertices are
 * connected by a path. Also print the path if it
 * exists. We do this by keeping track of source vertices
 * as we do the breadth first traversal.
 * Arguments
 *    key1 -  Key for the start vertex
 *    key2 -  Key for the second vertex to check
 * Returns 1 if the two vertices are connected, 0 if they
 * are not. Returns -1 if either vertex does not exist.
 */
int isReachablePrintPath(char* key1, char* key2)
{
   printf("Path printing not implemented!\n");
   return isReachable(key1,key2);
}

 
void createNetwork()
{
    char inputLine[32];
    char key1[32];
    char key2[32];
    char data[32];
    char startIndex[32],endIndex[32];
    int timeWeight = 0;
    int count = 0;
    int max;
    FILE * pLocation = NULL;
    FILE * pAirlineMap = NULL;
    
    
    pLocation = fopen("loction.txt","r");
    
    if (pLocation == NULL)
    {
        printf("Can't open loction.txt\n");
        exit(0);
    }
    fgets(inputLine,sizeof(inputLine),pLocation);
    sscanf(inputLine,"%d",&max);
    
    initGraph(max,0);
    
    while (fgets(inputLine,sizeof(inputLine),pLocation) != NULL)
    {
        sscanf(inputLine,"%s %s",key1,data);
        addVertex(key1,data);
    }
    
    fclose(pLocation);
    pAirlineMap = fopen("airlineMap.txt","r");
    
    if (pAirlineMap == NULL)
    {
        printf("Can't open airlineMap.txt\n");
        exit(1);
    }
    
    while (fgets(inputLine,sizeof(inputLine),pAirlineMap) != NULL)
    {
        sscanf(inputLine,"%s %s %d",key1,key2,&timeWeight);
        addEdge(key1,key2,timeWeight);
    }
    
}
