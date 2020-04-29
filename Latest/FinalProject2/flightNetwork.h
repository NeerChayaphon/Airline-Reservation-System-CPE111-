/* flightNetwork.h Create by Chayaphon Bunyakan (Neer) 62070503412
Team valid */


#ifndef flightNetwork_h
#define flightNetwork_h

#include <stdio.h>
#include "flightNetwork.h"

typedef struct _flight
{
    char *departure;
    char *arrival;
    char *flightID;
    char *departureHour;
    char *departureMinute;
    char *arrivalHour;
    char *arrivalMinute;
    char *airport1;
    char *airport2;
    unsigned int dayOfMonth;

    struct _flight *next;
    struct _flight *transit;

} FLIGHT_T;

typedef struct _adjacent
{
    void *pVertex;          /* pointer to the VERTEX_T this
                               * item refers to.
                               */
    unsigned int weight;    /* weight of this edge */
    struct _adjacent *next; /* next item in the ajacency list */
    FLIGHT_T *flightHead;
    FLIGHT_T *flightTail;
} ADJACENT_T;

/* List items for the main vertex list.*/
typedef struct _vertex
{
    char *key;                /* key for this vertex */
    void *data;               /* ancillary data for this vertex */
    int color;                /* used to mark nodes as visited */
    int dValue;               /* sum of weights for shortest path so far to this vertex */
    struct _vertex *parent;   /* pointer to parent found in Dijkstra's algorithm */
    struct _vertex *next;     /* next vertex in the list */
    ADJACENT_T *adjacentHead; /* pointer to the head of the
                       * adjacent vertices list
                               */
    ADJACENT_T *adjacentTail; /* pointer to the tail of the
                   * adjacent vertices list
                               */
} VERTEX_T;

int checkReachableFlight(char *key1, char *key2);
FLIGHT_T *findFlightInEdge(char *key1, char *key2);

#endif /* flightNetwork_h */
