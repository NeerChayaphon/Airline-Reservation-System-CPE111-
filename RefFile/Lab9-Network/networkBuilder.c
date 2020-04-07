/**
 *  networkBuilder.c 
 *
 *  Reads a file that defines a network, and builds that network
 *  by calling functions in the abstractNetwork ADT.
 *
 *  Created by Sally Goldin, 1 February 2012 for CPE 113
 *  Modified 20 April 2018 to use JavaDoc keywords in comments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractNetwork.h"
#include "networkBuilder.h"

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


void processCommand(char* command, int bVerbose);


/** Opens and reads a network definition file that is supposed to follow
 * the structure explained above. If 'bVerbose' is true, displays messages
 * as it processes the file, explaining what it is doing.
 * @param   filename  Filename to read, with path
 * @param   bVerbose  If non-zero, print messages as processing goes on
 *                    if zero, prints only error messages
 * @return 1 if successful, -1 if any error occurs.
 */  
int readNetworkDefinition(char* filename, int bVerbose)
{
    int status = 1;
    FILE* pFp = NULL;
    char inputline[128];
    char key1[64];
    char key2[64];
    int weight = 0;
    int vertexCount = 0;
    int bDirected = 0;
    pFp = fopen(filename,"r");
    if (pFp == NULL)
       {
       status = -1;
       fprintf(stderr,"Error - cannot open file %s\n", filename);
       }
    else
       {
       if (bVerbose)
           fprintf(stdout,">> Successfully opened file %s\n", filename);
       if (fgets(inputline,sizeof(inputline),pFp) != NULL)
           {
           sscanf(inputline,"%d %d",&vertexCount,&bDirected);
           if (vertexCount == 0)  /* bad format */
               {
               status = -1;
               fprintf(stderr,"Error - file %s has bad format\n", filename);
               } 
           else if (initGraph(vertexCount,bDirected))
               { 
               if (bVerbose)
                   fprintf(stdout,
                        "Successfully initialized %s network with %d vertices\n",
                       (bDirected? "DIRECTED" : "UNDIRECTED"), vertexCount);
	       while (fgets(inputline,sizeof(inputline),pFp) != NULL)
		   {
		   inputline[strlen(inputline) - 1] = '\0';  
		   processCommand(inputline,bVerbose);
		   }
               }
           else
               {
               status = -1;
               fprintf(stderr,"Error - cannot initialize network\n");
               }          
           } 
	fclose(pFp);
       }
    return status;
}

/** Parse a line from the network builder file. If the
 * syntax is correct, call the addVertex or addEdge
 * function as appropriate. Handle errors and 
 * give feed back if bVerbose is set to true.
 * @param  command  Line read from network builder file
 * @param  bVerbose If true, give information about all operations executed
 */
void processCommand(char* command, int bVerbose)
{
    char keystring1[64] = "";
    char keystring2[64] = "";
    char* newString = NULL;
    char* key = NULL;
    int weight = -1;
    int retval = 0;

    memset(keystring1,0,sizeof(keystring1));
    memset(keystring2,0,sizeof(keystring2));
    if (strncmp(command,"VERTEX",strlen("VERTEX")) == 0)
       {
       sscanf(command,"VERTEX %s",keystring1);
       if (strlen(keystring1) == 0) 
	 {
	 fprintf(stderr,"Error: Missing key\n  |%s|\n",
		   command);
	 }
       else
	 {
         key = strdup(keystring1);
         newString = strdup(keystring1);  /* use the key as data as well */
	 retval = addVertex(key,newString);
	 if (retval == 1) 
	    {
	    if (bVerbose)
	       fprintf(stdout,"Vertex |%s| added\n",key);
	    }
	 else if (retval < 0)
	    {
	    fprintf(stderr,
                  "Error: Vertex with key |%s| already exists in graph\n", key);
	    free(key);
	    free(newString);
	    }
	 else 
	    {
	    fprintf(stderr,
                "Error: Trying to insert vertex with {%s|- allocation error or graph full\n",key);
	    free(key);
	    free(newString);
	    }
	 }
       }
    else if (strncmp(command,"EDGE",strlen("EDGE")) == 0)
       {
       sscanf(command,"EDGE %s %s %d",keystring1,keystring2,&weight);
       if ((strlen(keystring1) == 0) || (strlen(keystring2) == 0))
	  {
	  fprintf(stderr,
		  "Error: At least one key missing in edge command\n  |%s|\n",
		  command);
	  }
       else if (strcmp(keystring1,keystring2) == 0)
	  {
	  fprintf(stderr,
		  "Error: 'From' and 'To' vertices are the same\n  |%s|\n",
		  command);
	  }
       else if (weight < 0)
	  {
	  fprintf(stderr,"Error: weight must be specified as non negative integer\n  |%s|\n",
		  command);
	  }
       else
	  {
	  retval = addEdge(keystring1,keystring2, weight);  
	  if (retval == 1) 
	     {
	     if (bVerbose)
	         fprintf(stdout,
                     "Added edge from |%s| to |%s| with weight %d\n",
			 keystring1,keystring2, weight);
	     }
	  else if (retval < 0)
	     {
	     fprintf(stderr,"Error: Edge from |%s| to |%s| already exists\n  |%s|\n",
		     keystring1,keystring2,command);
	     }
	  else 
	     {
	     fprintf(stderr,
                     "Error: At least one vertex doesn't exist or memory allocation error\n  |%s|\n", command);
	     }
	  }
       }
    else
       {
       fprintf(stderr,"Incorrect command found in file - ignoring\n");
       fprintf(stderr,"  |%s|\n",command);
       }
}

