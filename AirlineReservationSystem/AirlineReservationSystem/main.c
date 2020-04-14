//
//  main.c
//  AirlineReservationSystem
//
//  Created by chayaphon bunyakan on 4/4/2563 BE.
//  Copyright © 2563 chayaphon bunyakan. All rights reserved.
//

#include <stdio.h>
#include "networkBuilder.h"
#include "abstractNetwork.h"
#include "flightNetwork.h"

int main(int argc, const char * argv[])
{
    readNetworkDefinition("flightInput.txt",1);
    printShortestPath("A","D");
    testExample();
}
