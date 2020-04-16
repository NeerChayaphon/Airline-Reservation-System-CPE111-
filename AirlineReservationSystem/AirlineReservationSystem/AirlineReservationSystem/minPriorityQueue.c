/*
 *   minPriorityQueue.c 
 *
 *   Linked list implementation of an abstract min priority queue
 *   This implementation is not at all efficient as it uses
 *   a linear search to find the minimum item
 *
 *   Created by Sally Goldin, 18 January 2012, for CPE 113
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "minPriorityQueue.h"


/* Structure that represents one item of the list */
typedef struct _listitem
{
    void* data;               /* Pointer to the data for this node */
    struct _listitem * next;  /* Link to the next item in the list */
} LISTITEM_T;

static int count = 0;              /* number of items in the queue */
static LISTITEM_T * head = NULL;   /* front item in the queue */
static LISTITEM_T * tail = NULL;   /* end item in the queue */

/* comparison function must work like strcmp.
 * Return -1 if data1 < data2, 0 if they are equivalent, 1 if data1 > data2 */
int (*compare)(void * data1, void * data2) = NULL;


/* Use the comparison function to find the smallest
 * item currently in the list
 * Argument
 *  pPredecessor  -  Used to return the previous item
 *                   so we can unlink the minimum
 * Returns a pointer to the minimum item. Returns null
 * if the queue is empty.
 */
LISTITEM_T * findMinimum(LISTITEM_T ** pPredecessor)
{
   LISTITEM_T * pMinItem = NULL;
   LISTITEM_T * pCurrentItem = NULL;
   LISTITEM_T * pPredItem = NULL;
   *pPredecessor = NULL;
   if (count == 1)
      {
      pMinItem = head;
      }
   else if (count > 1)
      {
      pCurrentItem = head;
      while (pCurrentItem != NULL)
	 {
	 /* if this is the first item in the list, or
          * this item is less than the current min
          */
	 if ((pMinItem == NULL) ||
	     ((*compare)(pCurrentItem->data,pMinItem->data) < 0))
	    {
	    pMinItem = pCurrentItem;
   	    *pPredecessor = pPredItem;
            /* reset current min and also set predecessor */
	    }
         pPredItem = pCurrentItem;
         pCurrentItem = pCurrentItem->next;
	 }
      }
   return pMinItem;
}

/**
 * Add a data item to the queue (end of the list)
 * Arguments:
 *   data      -   Pointer to generic data we want to add to queue   
 * Returns 1 if successful, 0 if we have run out of space.
 */
int enqueueMin(void* data)
{
   int bOk = 1;
   LISTITEM_T * newItem = (LISTITEM_T *)calloc(1,sizeof(LISTITEM_T));
   if (newItem == NULL)
       {
       bOk = 0;
       }
   else
       {
       newItem->data = data;  /* store the data */
       if (head == NULL)       /* nothing in the queue yet */
          {
	  head = newItem;      
          }
       else
          {
	  tail->next = newItem;  /* add to the end of the queue */ 
          }
       tail = newItem;         /* either way the new item is now the end */
       count++;
       }
   return bOk;
}


/* Get the next item in the queue. This is the minimum 
 * element as defined by applying the compareFunction. 
 * Returns the data stored in that item.
 * Also removes that item from the queue.
 * Returns NULL if the queue is empty.
 */
void * dequeueMin()
{
   void * returnData = NULL;
   if (count > 0)
      {
      LISTITEM_T* pPredItem = NULL;  /* preceding item */
      LISTITEM_T* pMinItem = findMinimum(&pPredItem);
      returnData = pMinItem->data;
      if (pPredItem != NULL)
	 {
	 pPredItem->next = pMinItem->next;
	 }
      if (pMinItem == head)
	 {
         head = pMinItem->next;
	 } 
      if (pMinItem == tail)
	 {
	 tail = pPredItem;
	 }
      free(pMinItem);
      count--;
      }
   return returnData;
}


/* Find out how many items are currently in the queue.
 * Return number of items in the queue (could be zero)
 */
int queueMinSize()
{
   return count;
}


/* Clear so we can reuse 
 */
void queueMinInit(int (*compareFunction)(void* data1, void* data2))
{
    int i = 0;
    compare = compareFunction;
    LISTITEM_T * item = head;
    LISTITEM_T * freeItem = NULL;
    while (item != NULL)
       {
       freeItem = item;
       item = item->next;
       free(freeItem);
       }
    /* reset head, tail and count */
    head = NULL;
    tail = NULL;
    count = 0;
}


/** DEBUGGING FUNCTION PRINTS SOME INFO ABOUT THE QUEUE **/
void queueMinDebug()
{
   int i, j;
   printf("count = %d   head = %p  tail = %p\n",
	  count, head, tail);
   if (count > 0)
      {
      printf("Contents: \n");
      LISTITEM_T * item = head;
      while (item != NULL)
        {
	printf("\t\t%s\n", item->data);
	item = item->next;
	}
      }
}
