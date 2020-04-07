/*
 *  graphTester.c 
 *
 *  Driver program for testing/exploring graphs
 *
 *  Created by Sally Goldin, 25 January 2012 for CPE 113
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractGraph.h"

int getMenuOption();

/* Loop asking for actions until the user chooses to exit */
int main(int argc, char* argv[])
{
    int maxVertices = 0;
    int bDirected = 0;
    char input[64];
    char keystring1[64] = "";
    char keystring2[64] = "";
    char* removedString = NULL;
    char* newString = NULL;
    char* key = NULL;
    int retval = 0;
    int i = 0;

    int choice = getMenuOption();
    while (choice != 9)
    {
        memset(keystring1,0,sizeof(keystring1));
        memset(keystring2,0,sizeof(keystring2));
        newString = key = NULL;
	switch (choice)
	{
	    case 1:  /* create the graph */ 
                printf("Enter max number of vertices: ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&maxVertices);
		if (maxVertices <= 0)
		   {
		   printf(">>> Error! number of vertices should be positive\n");
		   }
                else
		   {
                   printf("Directed graph (Y/N)? ");
		   fgets(input,sizeof(input),stdin);
                   if ((input[0] == 'Y') || (input[0] == 'y'))
                       bDirected = 1;
		   else
                       bDirected = 0;
                   clearGraph();
                   if (!initGraph(maxVertices, bDirected))
		      {
		      printf(">>> Error! Cannot initialize graph\n");
		      }
		   }
		break;
	    case 2:  /* add vertex */
                memset(input,0,sizeof(input));
		printf("Enter key value for vertex: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring1);  
		key = strdup(keystring1);
                memset(input,0,sizeof(input));
		printf("Enter data for vertex: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		newString = strdup(input);
                if ((strlen(key) == 0) || (strlen(newString) == 0))
		   {
		   printf("Input error - key or data empty!\n");
		   free(key);
		   free(newString);
		   }
                else
		   { 
		   retval = addVertex(key,newString);
		   if (retval == 1) 
		      {
		      printf("Vertex |%s| added\n",key);
		      }
		   else if (retval < 0)
		      {
		      printf(">>> Vertex with key |%s| already exists in graph\n", key);
		      }
		   else 
		      {
		      printf(">>> Memory allocation error or graph full!\n");
		      }
		   }
		break;
	    case 3: /* add edge */
                memset(input,0,sizeof(input));
		printf("Enter key value for 'From' vertex: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring1);  
                memset(input,0,sizeof(input));
		printf("Enter key value for 'To' vertex: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring2);
                if ((strlen(keystring1) == 0) || (strlen(keystring2) == 0))
		   {
		   printf("Input error - key or data empty!\n");
		   }
		else if (strcmp(keystring1,keystring2) == 0)
		   {
		   printf("Input error - 'From' must be different from 'To'!\n");
		   }
                else
		   {
		   retval = addEdge(keystring1,keystring2);  
		   if (retval == 1) 
		       {
		       printf("Added edge from |%s| to |%s|\n",
				  keystring1,keystring2);
		       }
		       else if (retval < 0)
		       {
		       printf(">>> Edge from |%s| to |%s| already exists!\n",
				  keystring1,keystring2);
		       }
		       else 
		       {
		       printf(">>> Vertex doesn't exist or memory allocation error!\n");
		       }
		   }
		break;
   	    case 4:   /* remove vertex */
                memset(input,0,sizeof(input));
		printf("Enter key value for vertex to remove: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring1);  
                char* returnData = removeVertex(keystring1);
                if (returnData != NULL)
		   {
		   printf(
                      "Vertex |%s| held data |%s| - now removed from graph\n",
		      keystring1,returnData);
		   }
                else
		   {
		   printf(
		       ">>> Error removing - maybe vertex |%s| didn't exist!\n",
		       keystring1);

		   }
		break;
	    case 5:   /* remove edge */
                memset(input,0,sizeof(input));
		printf("Enter key value for 'From' vertex: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring1);  
                memset(input,0,sizeof(input));
		printf("Enter key value for 'To' vertex: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring2);
                retval = removeEdge(keystring1,keystring2);  
                if (retval == 1) 
		   {
		   printf("Removed edge from |%s| to |%s|\n",
			  keystring1,keystring2);
		   }
		else 
		   {
		   printf(">>> Edge or vertex did not exist!\n");
		   }
		break;
	    case 6:   /* get adjacent */
	        {
                int count;
                char** adjacentKeys = NULL;
                memset(input,0,sizeof(input));
		printf("Enter key value: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring1);  
                adjacentKeys = getAdjacentVertices(keystring1,&count);
                if (count == 0)
		   {
		   printf(">>> Vertex |%s| has no adjacent vertices\n",
			      keystring1);
		   }
                else if (count < 0)
		   { 
		   printf(">>> Vertex |%s| does not exist\n",
			      keystring1);
		   }
		else
		   {
		   int i = 0;
		   printf("The following vertices are incident from |%s|\n",
			  keystring1);
		   for (i = 0; i < count; i++)
		      {
		      printf("     %s\n",adjacentKeys[i]);
		      free(adjacentKeys[i]);
		      }
		   free(adjacentKeys);
		   }
		break;
		}
	    case 7:   /* breadth first traversal */
                memset(input,0,sizeof(input));
                printf("Want breadth first (Y or N, N=depth first)? ");
		fgets(input,sizeof(input),stdin);
		if ((input[0] == 'Y') || (input[0] == 'y'))
		    {
		    printf("Start traversal at what vertex? ");
		    fgets(input,sizeof(input),stdin);
		    input[strlen(input) - 1] = '\0';  
		    sscanf(input,"%s",keystring1);  
		    retval = printBreadthFirst(keystring1);
		    if (retval < 0)
		       { 
		       printf(">>> Vertex |%s| does not exist\n",
			      keystring1);
		       }
		    }
		else
		    {
		    printDepthFirst();
		    }
		break;
	    case 8:   /* check reachable */
                memset(input,0,sizeof(input));
		printf("Enter key value for 'From' vertex: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring1);  
                memset(input,0,sizeof(input));
		printf("Enter key value for 'To' vertex: ");
		fgets(input,sizeof(input),stdin);
		input[strlen(input) - 1] = '\0';  
		sscanf(input,"%s",keystring2);
                if ((strlen(keystring1) == 0) || (strlen(keystring2) == 0))
		   {
		   printf("Input error - key or data empty!\n");
		   }
		else if (strcmp(keystring1,keystring2) == 0)
		   {
		   printf("Input error - 'From' must be different from 'To'!\n");
		   }
                else
		   {
		   printf("Do you want to print the path (Y/N)? ");
                   fgets(input,sizeof(input),stdin);
                   if ((input[0] == 'Y') || (input[0] == 'y'))
		       retval = isReachablePrintPath(keystring1,keystring2);  
		   else 
		       retval = isReachable(keystring1,keystring2);  
		   if (retval == 1) 
		       {
		       printf("Vertex |%s| IS reachable from |%s|\n",
				  keystring2,keystring1);
		       }
		       else if (retval == 0)
		       {
		       printf("Vertex |%s| IS NOT reachable from |%s|\n",
				  keystring2,keystring1);
		       }
		       else 
		       {
		       printf(">>> At least one vertex doesn't exist!\n");
		       }
		   }
		break;
	    default:
	        printf("Invalid option - we should never get here!\n");
	}  /* end switch  */
	choice = getMenuOption();
    }      /* end while loop */

/* exit here - we're done */
}


/* Show menu of options. Return the user-selected option
 */
int getMenuOption()
{
    char input[32];
    int option = -1;
    while (option < 0)
       {
       printf("\nGraph Tester options:\n");
       printf("  1 - Create, or empty and recreate, graph\n");
       printf("  2 - Insert a vertex into the graph\n");
       printf("  3 - Insert an edge into the graph\n");
       printf("  4 - Remove a vertex from the graph\n");
       printf("  5 - Remove an edge from the graph\n");
       printf("  6 - Get adjacent vertices\n");
       printf("  7 - Print breadth first or depth first\n");
       printf("  8 - Check if reachable\n");
       printf("  9 - Exit\n");
       printf("Which option? ");
       fgets(input,sizeof(input),stdin);
       sscanf(input,"%d",&option);
       if ((option > 9) || (option < 1))
           {
	   printf("Invalid selection - choose 1 to 9\n");
	   option = -1;
	   }
       }
    printf("\n");
    return option;
}

