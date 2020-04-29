/**
 *  minPriorityQueue.h
 *
 *  Header file defining the operations that one can
 *  do on a minimum priority queue. The elements of
 *  the list are pointers to structures. We also need to
 *  provide a comparison function during the initialization.
 *
 *  Created by Sally Goldin, 3 February for CPE113
 *
 */

#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

/**
 * Add a data item to the queue (end of the list)
 * Arguments:
 *   data      -   Pointer to string we want to add to queue   
 * Returns 1 if successful, 0 if we have run out of space.
 */
int enqueueMin(void* data);

/* Get the next item in the queue. This is the element 
 * that has the smallest data value
 * Also removes that item from the queue.
 * Returns NULL if the queue is empty.
 */
void* dequeueMin();

/* Find out how many items are currently in the queue.
 * Return number of items in the queue (could be zero)
 */
int queueMinSize();

/* Initialize or clear so we can reuse 
 */
void queueMinInit(int (*compareFunction)(void* data1, void* data2));


/** DEBUGGING FUNCTION PRINTS SOME INFO ABOUT THE QUEUE **/
void queueMinDebug();

#endif
