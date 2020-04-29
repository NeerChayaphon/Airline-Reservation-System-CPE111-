//
//  flightFinder.c
//  FinalProject2
//
//  Created by chayaphon bunyakan on 28/4/2563 BE.
//  Copyright © 2563 chayaphon bunyakan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flightFinder.h"
#include "flightNetwork.h"
#include "abstractNetwork.h"


void findFlightInPath(char *origin, char *destination, int day)
{
    printShortestPath(origin,destination,day);
}

void selectFlight(FLIGHT_T *pFlight,int pathCount,int intineraryCount)
{
    char input[64];
    int choice = 0;
    FLIGHT_T *pCurrent = NULL;
    int count = 0;
    while (1)
    {
        printf("Enter what intineray do you want : ");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d",&choice);
        if (choice > 0 && choice <= intineraryCount)
        {
            break;
        }
        else
        {
            printf("Wrong number. please enter again\n");
        }
    }
    
    count = 1;
    pCurrent = pFlight;
    while (pCurrent != NULL)
    {
        if (count == choice)
        {
            break;
        }
        else
        {
            count++;
            pCurrent = pCurrent->next;
        }
    }
    if (pathCount == 2)
    {
        printf("choice is |%s %d|\n",pCurrent->flightID,pCurrent->dayOfMonth);
    }
    
    else if (pathCount == 3)
    {
        printf("choice is |%s %d| -> |%s %d|\n",pCurrent->flightID,pCurrent->dayOfMonth,pCurrent->transit->flightID,pCurrent->transit->dayOfMonth);
    }
    
    else if (pathCount == 4)
    {
        printf("choice is |%s %d| -> |%s %d| ->|%s %d|\n",pCurrent->flightID,pCurrent->dayOfMonth,pCurrent->transit->flightID,pCurrent->transit->dayOfMonth,pCurrent->transit->transit->flightID,pCurrent->transit->transit->dayOfMonth);
    }
    
    
}

int timeSubtraction(FLIGHT_T *firstFlight, FLIGHT_T *secondFlight,int *hour,int *minute,int *totalMinute)
{
    int check = 0;
    int departureHour;
    int departureMinute;
    int arrivalHour;
    int arrivalMinute;
    
    int subtractHour = 0;
    int subtractMinute = 0;
    
    arrivalHour = atoi(firstFlight->arrivalHour);
    arrivalMinute = atoi(firstFlight->arrivalMinute);
    departureHour = atoi(secondFlight->departureHour);
    departureMinute = atoi(secondFlight->departureMinute);
    
    subtractHour = departureHour - arrivalHour;
    subtractMinute = departureMinute - arrivalMinute;
    
    if (subtractMinute < 0)
    {
        subtractMinute = subtractMinute + 60;
        subtractHour = subtractHour - 1;
    }
    if (subtractHour < 0)
    {
        subtractHour = subtractHour + 24;
    }
    
    *hour = subtractHour;
    *minute = subtractMinute;
    *totalMinute = (subtractHour * 60) + subtractMinute;
    
    if (*totalMinute >= 120)
    {
        check = 1;
    }
    return check;
}

void printfAllFlight(FLIGHT_T *pFlight,int pathCount,int travelTime)
{
    FLIGHT_T *pCurrent = NULL;
    int transitTime = 0;
    int secondtransitTime = 0;
    int hour = 0;
    int minute = 0;
    int count = 0;

    if (pathCount == 2)
    {
        pCurrent = pFlight;
        while (pCurrent != NULL)
        {
            ++count;
            printf("%d.|%s %d| travel time : %d minute\n",count,pCurrent->flightID,pCurrent->dayOfMonth,travelTime);
            pCurrent = pCurrent->next;
        }
    }
    else if (pathCount == 3)
    {
        pCurrent = pFlight;
        while (pCurrent != NULL)
        {
            if (pCurrent->transit != NULL)
            {
                ++count;
            timeSubtraction(pCurrent,pCurrent->transit,&hour,&minute,&transitTime);
            printf("%d.|%s %d| -> |%s %d| travel time : %d minute\n",count,pCurrent->flightID,pCurrent->dayOfMonth,pCurrent->transit->flightID,pCurrent->transit->dayOfMonth,travelTime + transitTime);
            }
            pCurrent = pCurrent->next;
        }
    }
    else if (pathCount == 4)
    {
        pCurrent = pFlight;
        while (pCurrent != NULL)
        {
            if ((pCurrent->transit != NULL) && (pCurrent->transit->transit != NULL))
            {
            timeSubtraction(pCurrent,pCurrent->transit,&hour,&minute,&transitTime);
            hour = 0;
            minute = 0;
            timeSubtraction(pCurrent->transit,pCurrent->transit->transit,&hour,&minute,&secondtransitTime);
            
            transitTime = transitTime + secondtransitTime;
            printf("%d.|%s %d| -> |%s %d| ->%s %d| travel time : %d minute\n",count,pCurrent->flightID,pCurrent->dayOfMonth,pCurrent->transit->flightID,pCurrent->transit->dayOfMonth,pCurrent->transit->transit->flightID,pCurrent->transit->transit->dayOfMonth,travelTime + transitTime);
                ++count;
            }
            pCurrent = pCurrent->next;
        }
    }
    selectFlight(pFlight,pathCount,count);
}



int checkflightInDate(VERTEX_T **pathVertices,int pathCount, int day)
{
    int bOk = 1;
    FLIGHT_T *firstFlight = NULL;
    FLIGHT_T *secondFlight = NULL;
    FLIGHT_T *thirdFlight = NULL;
    FLIGHT_T *pCurrentFlight = NULL;
    FLIGHT_T *pCurrentFlight2 = NULL;
    FLIGHT_T *pCurrentFLight3 = NULL;
    FLIGHT_T *pCurrentFlight4 = NULL;
    FLIGHT_T *shortTransitFlight = NULL;
    FLIGHT_T *shortTransitFlight2 = NULL;
    FLIGHT_T *pFlight = NULL;
    FLIGHT_T * pHead = NULL;
    FLIGHT_T * pTail = NULL;
    int i = 0;
    int hour = 0;
    int minute = 0;
    int totalMinute = 0;
    int shortestTime = 0;
    int check = 0;
    int travelTime = 0;
    travelTime = 0;
    
    if (pathCount == 2)
    {
        firstFlight = findFlightInEdge(pathVertices[pathCount - 1]->key, pathVertices[pathCount - 2]->key);
        pCurrentFlight = firstFlight;
        while (pCurrentFlight != NULL)
        {
            if (pCurrentFlight->dayOfMonth == day)
            {
            pFlight = (FLIGHT_T*) calloc(1,sizeof(FLIGHT_T));
                
            if (pFlight == NULL)
                {
                printf("Error allocate pFlight\n");
                exit(0);
                }
            pFlight = pCurrentFlight;
            if (pHead == NULL)
                {
                pHead = pFlight;
                }
            else
                {
                pTail->next = pFlight;
                }
            pTail = pFlight;
            }
            pCurrentFlight = pCurrentFlight->next;
        }
        printf("\n");
        pTail->next = NULL;
        travelTime = findEdge(pathVertices[pathCount - 1]->key, pathVertices[pathCount - 2]->key);
        printfAllFlight(pHead,pathCount,travelTime);
        
    }
    else if (pathCount == 3)
    {
        firstFlight = findFlightInEdge(pathVertices[pathCount - 1]->key, pathVertices[pathCount - 2]->key);
        secondFlight = findFlightInEdge(pathVertices[pathCount - 2]->key, pathVertices[pathCount - 3]->key);
        pCurrentFlight = firstFlight;
        while (pCurrentFlight != NULL)
        {
            if (pCurrentFlight->dayOfMonth == day)
            {
                pCurrentFlight2 = secondFlight;
                while (pCurrentFlight2 != NULL)
                {
                    hour = 0;
                    minute = 0;
                    totalMinute = 0;
                    check = timeSubtraction(pCurrentFlight, pCurrentFlight2, &hour, &minute, &totalMinute);

                    if (check == 1)
                    {
                        if (atoi(pCurrentFlight->arrivalHour) - atoi(pCurrentFlight->departureHour) < 0)
                        {
                            if (pCurrentFlight2->dayOfMonth == (day + 1))
                            {
                                if (shortestTime == 0)
                                {
                                    shortTransitFlight = pCurrentFlight2;
                                    shortestTime = totalMinute;
                                }
                                else if (totalMinute < shortestTime)
                                {
                                    shortTransitFlight = pCurrentFlight2;
                                    shortestTime = totalMinute;
                                }
                            }
                        }
                        else
                        {
                            if ((pCurrentFlight2->dayOfMonth == day) || (pCurrentFlight2->dayOfMonth == (day + 1)))
                            {
                                if (shortestTime == 0)
                                {
                                    shortTransitFlight = pCurrentFlight2;
                                    shortestTime = totalMinute;
                                }
                                else if (totalMinute < shortestTime)
                                {
                                    shortTransitFlight = pCurrentFlight2;
                                    shortestTime = totalMinute;
                                }
                            }
                        }
                    }
                    pCurrentFlight2 = pCurrentFlight2->next;
                }
                if ((shortestTime >= 120) && (shortTransitFlight != NULL))
                {

                    pFlight = (FLIGHT_T *)calloc(1, sizeof(FLIGHT_T));

                    if (pFlight == NULL)
                    {
                        printf("Error allocate pFlight\n");
                        exit(0);
                    }
                    pFlight = pCurrentFlight;

                    pFlight->transit = shortTransitFlight;

                    shortestTime = 0;
                    check = 0;

                    if (pHead == NULL)
                    {
                        pHead = pFlight;
                    }
                    else
                    {
                        pTail->next = pFlight;
                    }
                    pTail = pFlight;
                }
            }
            pCurrentFlight = pCurrentFlight->next;
        }
        printf("\n");
        pTail->next = NULL;
        travelTime = findEdge(pathVertices[pathCount - 1]->key, pathVertices[pathCount - 2]->key) + findEdge(pathVertices[pathCount - 2]->key, pathVertices[pathCount - 3]->key);
        printfAllFlight(pHead,pathCount,travelTime);
    }
    else if (pathCount == 4)
    {
        firstFlight = findFlightInEdge(pathVertices[pathCount - 1]->key, pathVertices[pathCount - 2]->key);
        secondFlight = findFlightInEdge(pathVertices[pathCount - 2]->key, pathVertices[pathCount - 3]->key);
        pCurrentFlight = firstFlight;
        while (pCurrentFlight != NULL)
        {
            if (pCurrentFlight->dayOfMonth == day)
            {
            pFlight = (FLIGHT_T*) calloc(1,sizeof(FLIGHT_T));
                
            if (pFlight == NULL)
                {
                printf("Error allocate pFlight\n");
                exit(0);
                }
            pFlight = pCurrentFlight;
                
            pCurrentFlight2 = secondFlight;
            while (pCurrentFlight2 != NULL)
            {
                hour = 0;
                minute = 0;
                totalMinute = 0;
                check = timeSubtraction(pCurrentFlight,pCurrentFlight2,&hour,&minute,&totalMinute);
                
                if (check == 1)
                {
                    if (atoi(pCurrentFlight->arrivalHour) - atoi(pCurrentFlight->departureHour) < 0)
                    {
                        if (pCurrentFlight2->dayOfMonth == (day + 1))
                        {
                            if (shortestTime == 0)
                            {
                                shortTransitFlight = pCurrentFlight2;
                                shortestTime = totalMinute;
                            }
                            else if (totalMinute < shortestTime)
                            {
                                shortTransitFlight = pCurrentFlight2;
                                shortestTime = totalMinute;
                            }
                        }
                    }
                    else
                    {
                        if ((pCurrentFlight2->dayOfMonth == day) || (pCurrentFlight2->dayOfMonth == (day + 1)))
                        {
                            if (shortestTime == 0)
                            {
                                shortTransitFlight = pCurrentFlight2;
                                shortestTime = totalMinute;
                            }
                            else if (totalMinute < shortestTime)
                            {
                                shortTransitFlight = pCurrentFlight2;
                                shortestTime = totalMinute;
                            }
                        }
                    }
                }
                pCurrentFlight2 = pCurrentFlight2->next;
            }
            if (shortestTime >= 120)
            {
                pFlight->transit = shortTransitFlight;
            }
            shortestTime = 0;
            check = 0;
            if (pHead == NULL)
                {
                pHead = pFlight;
                }
            else
                {
                pTail->next = pFlight;
                }
            pTail = pFlight;
            }
            pCurrentFlight = pCurrentFlight->next;
        }
        pTail->next = NULL;
        
        thirdFlight = findFlightInEdge(pathVertices[pathCount - 3]->key, pathVertices[pathCount - 4]->key);
        pCurrentFLight3 = pHead;
        while (pCurrentFLight3 != NULL)
        {
            shortestTime = 0;
            check = 0;
            pCurrentFlight4 = thirdFlight;
            while (pCurrentFlight4 != NULL)
            {
                hour = 0;
                minute = 0;
                totalMinute = 0;
                check = timeSubtraction(pCurrentFlight->transit,pCurrentFlight4,&hour,&minute,&totalMinute);
                
                if (check == 1)
                {
                    if (atoi(pCurrentFlight->transit->arrivalHour) - atoi(pCurrentFlight->transit->departureHour) < 0)
                    {
                        if (pCurrentFlight4->dayOfMonth == (day + 1))
                        {
                            if (shortestTime == 0)
                            {
                                shortTransitFlight2 = pCurrentFlight4;
                                shortestTime = totalMinute;
                            }
                            else if (totalMinute < shortestTime)
                            {
                                shortTransitFlight2 = pCurrentFlight2;
                                shortestTime = totalMinute;
                            }
                        }
                    }
                    else
                    {
                        if ((pCurrentFlight4->dayOfMonth == day) || (pCurrentFlight4->dayOfMonth == (day + 1)))
                        {
                            if (shortestTime == 0)
                            {
                                shortTransitFlight2 = pCurrentFlight4;
                                shortestTime = totalMinute;
                            }
                            else if (totalMinute < shortestTime)
                            {
                                shortTransitFlight2 = pCurrentFlight4;
                                shortestTime = totalMinute;
                            }
                        }
                    }
                }
                pCurrentFlight4 = pCurrentFlight4->next;
            }
            pCurrentFLight3 = pCurrentFLight3->next;
        }
        
        travelTime = findEdge(pathVertices[pathCount - 1]->key, pathVertices[pathCount - 2]->key) + findEdge(pathVertices[pathCount - 2]->key, pathVertices[pathCount - 3]->key) + findEdge(pathVertices[pathCount - 3]->key, pathVertices[pathCount - 4]->key);
        printfAllFlight(pHead,pathCount,travelTime);
    }
    //free(pFlight);
    return bOk;
}

/*
 pCurrentFlight2 = secondFlight;
 while (pCurrentFlight2 != NULL)
 {
     check = 0;
     hour = 0;
     minute = 0;
     totalMinute = 0;
     check = timeSubtraction(pCurrentFlight,pCurrentFlight2,&hour,&minute,&totalMinute);
     
     if (((pCurrentFlight2->dayOfMonth - day) == 0) || ((pCurrentFlight2->dayOfMonth - day) == 1))
     {
         check = 1;
     }
     else
     {
         check = 0;
     }
     
     if (check == 1)
     {
         if (shortestTime == 0)
         {
             shortTransitFlight = pCurrentFlight2;
             shortestTime = totalMinute;
         }
         else if (totalMinute < shortestTime)
         {
             shortTransitFlight = pCurrentFlight2;
             shortestTime = totalMinute;
         }
     }
     pCurrentFlight2 = pCurrentFlight2->next;
 }
     
 if (check == 1)
 {
     pFlight->transit = shortTransitFlight;
 }
 */

/* if (((pCurrentFlight2->dayOfMonth - day) == 0) || ((pCurrentFlight2->dayOfMonth - day) == 1))
{
    check = 1;
}
else
{
    check = 0;
}*/

/*
 BANGKOK HONGKONG FD502 17 40 21 40 DMK HKG 1
 BANGKOK HONGKONG FD508 06 25 10 11 DMK HKG 1
 BANGKOK HONGKONG FD500 10 30 14 35 DMK HKG 1
 BANGKOK HONGKONG FD502 15 25 19 20 DMK HKG 1
 HONGKONG BANGKOK FD503 22 10 23 50 DMK HKG 1
 HONGKONG BANGKOK FD501 15 35 17 25 DMK HKG 1
 HONGKONG BANGKOK FD509 10 45 12 35 DMK HKG 1
 HONGKONG BANGKOK FD505 19 50 21 45 DMK HKG 1
 BANGKOK MANILA PR731 13 30 18 00 BKK MNL 1
 MANILA HONGKONG PR310 19 20 21 35 MNL HKG 1
 BANGKOK MANILA PR733 22 55 03 15 BKK MNL 1
 MANILA HONGKONG PR300 07 55 10 10 MNL HKG 1
 HONGKONG MANILA PR301 11 10 13 30 HKG MNL 1
 MANILA BANGKOK PR736 14 25 17 10 MNL BKK 1
 HONGKONG MANILA PR319 13 20 15 35 HKG MNL 1
 MANILA BANGKOK PR732 19 25 21 35 MNL BKK 1
 BANGKOK MANILA PR731 13 30 18 00 BKK MNL 1
 MANILA TOKYO PR424 19 00 00 15 MNL HND 1
 BANGKOK MANILA PR733 22 55 03 15 BKK MNL 1
 MANILA TOKYO PR428 06 45 12 10 MNL HND 1
 TOKYO MANILA PR421 15 05 18 55 HND MNL 1
 MANILA TOKYO PR427 13 10 17 10 MNL HND 1
 TOKYO MANILA PR732 19 10 21 35 HND MNL 1
 BANGKOK TOKYO PG4161 08 05 16 20 BKK NRT 1
 BANGKOK TOKYO PG4153 21 55 06 10 BKK NRT 2
 BANGKOK TOKYO PG4155 09 45 18 00 BKK NRT 1
 TOKYO BANGKOK PG4152 00 35 05 00 NRT BKK 1
 TOKYO BANGKOK PG4160 18 20 23 00 NRT BKK 1
 TOKYO BANGKOK PG4154 11 15 15 40 NRT BKK 1
 BANGKOK TOKYO JL034 21 55 06 10 BKK NRT 1
 BANGKOK TOKYO JL708 08 05 16 20 BKK NRT 2
 TOKYO SEOUL JL034 08 25 10 45 HND GMP 1
 SEOUL BANGKOK JL090 07 55 09 55 ICN HND 1
 TOKYO BANGKOK JL031 11 15 15 40 NRT BKK 1
 TOKYO BANGKOK JL707 18 20 23 00 NRT BKK 1
 BANGKOK SEOUL KE652 23 30 06 55 BKK ICN 1
 SEOUL BANGKOK KE651 18 05 21 45 ICN BKK 1
 BANGKOK SEOUL 7C2202 12 30 20 50 BKK ICN 1
 SEOUL BANGKOK 7C2201 01 00 08 40 ICN BKK 1
 BANGKOK BALI FD396 06 15 11 30 DMK DPS 1
 BALI BANGKOK FD397 12 05 15 40 DPS DMK 1
 MANILA BALI PR537 20 10 23 59 MNL DPS 1
 BALI JAKATAR PG4315 13 30 14 30 DPS CGK 1
 JAKATAR BANGKOK PG4304 09 35 13 10 MNK BKK 1
 MANILA SHANGHAI PR336 10 50 14 40 MNL PVG 1
 SHANGHAI MANILA PR337 16 00 19 50 PVG MNL 1
 MANILA OSAKA PR412 09 05 14 10 MNL KIX 1
 MANILA OSAKA PR408 13 55 19 00 MNL KIX 1
 OSAKA MANILA PR732 19 10 21 35 KIX MNL 1
 OSAKA MANILA PR736 14 25 17 10 KIX MNL 1
 TOKYO OSAKA JL3009 18 25 19 50 NRT KIX 1
 TOKYO OSAKA JL103 07 20 08 25 HND KIX 1
 OSAKA BANGKOK JL727 00 55 04 40 KIX BKK 1
 OSAKA TOKYO JL106 08 30 09 40 ITM HND 1
 OSAKA TOKYO JL3006 14 35 16 00 ITM NRT 1
 */
