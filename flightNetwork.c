/* flightNetwork.c
 * Using file from simpleNetwork.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "flightNetwork.h"

#define MAXVERT 100
#define HUGEVALUE 99999
#define WHITE 0
#define BLACK 1

typedef struct
{
    char keyValue[32];
    int myIndex;
    int dValue;
    int parentIndex;
    int color;

} VERTEX_T;

VERTEX_T loctionVertice[MAXVERT];

int loctionCount = 0;

int flightEdges[MAXVERT][MAXVERT];

int findVertex(char key[])
    {
    int found = -1;
    int i = 0;
    for (i = 0; (i < loctionCount) && (found < 0); i++)
        {
        if (loctionVertice[i].keyValue == key)
            {
            found = i;
            }
        }
    return found;
    }

int main()
{
    char inputLine[32];
    char key1[32];
    char key2[32];
    char startIndex,endIndex;
    int timeWeight = 0;
    FILE * pLocation = NULL;
    FILE * pAirlineMap = NULL;
    
    memset(loctionVertice,0,sizeof(loctionVertice));
    
    pLocation = fopen("loction.txt","r");
    
    if (pLocation == NULL)
    {
        printf("Can't open loction.txt\n");
        exit(0);
    }
    
    while (fgets(inputLine,sizeof(inputLine),pLocation) != NULL)
    {
        sscanf(inputLine,"%s",loctionVertice[loctionCount].keyValue);
        loctionCount++;
    }
    
    pAirlineMap = fopen("airlineMap.txt","r");
    
    if (pAirlineMap == NULL)
    {
        printf("Can't open airlineMap.txt\n");
        exit(1);
    }
    
    while (fgets(inputLine,sizeof(inputLine),pAirlineMap) != NULL)
    {
        sscanf(inputLine,"%s %s %d",key1,key2,&timeWeight);
        startIndex = findVertex(key1);
        endIndex = findVertex(key2);
        
        flightEdges[startIndex][endIndex] = timeWeight;
    }
}
