/*
 *  queueTester.c 
 *
 *  Driver program for illustrating a queue
 *
 *  Created by Sally Goldin, 21 December 2011 for CPE 113
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abstractQueue.h"

int getMenuOption();
char * getTimestampString();

/* Loop asking for actions until the user chooses to exit */
int main(int arc, char* argv[])
{
    int handle = 0;
    char input[64];
    char stringval[64];
    char* removedString = NULL;
    char* newString = NULL;
    int retval = 0;
    
    int choice = getMenuOption();
    while (choice != 5)
    {
	switch (choice)
	{
	    case 1:  /* enqueue */
	        {
		newString = getTimestampString();
		printf("About to enqueue: %s\n", newString);
                if (!enqueue(newString))
		   {
		   printf("Error! queue is full!\n");
		   free(newString);
		   } 
		break;
	        }
	    case 2:
	        {
		removedString = dequeue();
		if (removedString == NULL)
		   {
		   printf("Error! queue is empty!\n");
		   } 
                else
		   {
		   printf("Dequeued: %s\n", removedString);
		   free(removedString);
                   }
		break;
	        }
	    case 3:
	        {
	        queueClear();
		break;
		}
	    case 4:
	        {
	        printDebug();
		break;
		}
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
       printf("\nQueue Tester options:\n");
       printf("  1 - Add an item to the queue (enqueue)\n");
       printf("  2 - Remove an item from the queue (dequeue)\n");
       printf("  3 - Clear and reset queue\n");
       printf("  4 - Show current queue contents\n");
       printf("  5 - Exit\n");
       printf("Which option? ");
       fgets(input,sizeof(input),stdin);
       sscanf(input,"%d",&option);
       if ((option > 5) || (option < 1))
           {
	   printf("Invalid selection - choose 1 to 4\n");
	   option = -1;
	   }
       }
    printf("\n");
    return option;
}

/* Create a string that shows the current date and time
 * and return it. Note that this function allocates memory
 * which should be freed.
 */
char * getTimestampString()
{

     char * format = "Created at %T";
     char * buffer = (char*) malloc(32);
     time_t t;
     struct tm *tmp;
     if (buffer == NULL)
        {
	fprintf(stderr,"Memory allocation error in getTimestampString\n");
	exit(1);
        } 
     t = time(NULL);
     tmp = localtime(&t);
     strftime(buffer, 32, format, tmp);
     return buffer;  
}
