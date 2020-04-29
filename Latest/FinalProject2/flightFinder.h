//
//  flightFinder.h
//  FinalProject2
//
//  Created by chayaphon bunyakan on 28/4/2563 BE.
//  Copyright © 2563 chayaphon bunyakan. All rights reserved.
//

#ifndef flightFinder_h
#define flightFinder_h

#include <stdio.h>
#include "flightNetwork.h"
#include "flightFinder.h"

void findFlightInPath(char *origin, char *destination, int day);
void printfAllFlight(FLIGHT_T *pFlight,int pathCount,int travelTime);
int checkflightInDate(VERTEX_T **pathVertices,int pathCount, int day);

#endif /* flightFinder_h */
