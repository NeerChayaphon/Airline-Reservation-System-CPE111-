/* Created by chayaphon bunyakan (Neer) 62070503412
 Team valid */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "networkBuilder.h"
#include "abstractNetwork.h"
#include "flightNetwork.h"
#include "flightFinder.h"

typedef struct
{
    char departure[32];
    char arrival[32];
    int departureDay;
    int passenger;

} DATA_T;

int main(int argc, const char *argv[])
{
    char input[32];
    DATA_T inputData;
    int pathCheck = 0;
    char bookMore[32];

    while (1)
    {
        pathCheck = 0;
        readNetworkDefinition("networkInput.txt", 0);

        while (pathCheck != 1)
        {
            printf("From: ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%s", inputData.departure);

            printf("To: ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%s", inputData.arrival);

            pathCheck = checkReachableFlight(inputData.departure, inputData.arrival);
            if (pathCheck != 1)
            {
                printf("Error location are not reachable\n");
            }
        }

        printf("Departure Date [1-30 of the month]: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &inputData.departureDay);

        printf("Passengers: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &inputData.passenger);

        findFlightInPath(inputData.departure, inputData.arrival,inputData.departureDay);
        
        while (1)
        {
            printf("Do you want to book more ? (Y/N) :");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%s",bookMore);
            
            if (strcmp(bookMore,"Y") == 0)
            {
                break;
            }
            else if (strcmp(bookMore,"N") == 0)
            {
                exit(0);
            }
            else
            {
                printf("Enter only (Y/N)\n");
            }
            
        }
    }
}
