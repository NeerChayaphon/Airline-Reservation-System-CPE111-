Team Valid
 *  [Chayaphon Bunyakan (Neer) 62070503412]
 *  [Pirada Amornprapawat (Pear) 62070503437]
 *  [Siriphorn Jarisu (Noolek) 62070503448]

This program is use to
 *  1. Create a network that can be link to city (airline map)
 *  2. Link all the flight to the edge if the network
 *  3. Link flight with each other. The flight that link with another flight have to has less transit time
 *  For example A->B (10:00 - 11:00) the flight that can be transit are B->C (13:00 - 14:00) and B->C (14:00 - 15:00)
 *  The program will choose the first one first the the second one to use in the shortest path algorithm
 *  4.Find the itinerary using dijkstra's shortest path algorithm, It will loop the find the best 20 itinerary. Start checking from the itinerary that have the lest transit time after get the result check other itinerary.


The thing that are working are
1.it can build network using buildNetwork.c and flightNetwork.c by reading from text file

2.(flightNetwork.c) it can read flight information and add it to the edge by modifying the addEdge function and findFlight function

3.(flightNetwork.c) it can link the flight together and the flight that link will have short transit time mean that not any flight can link with any flight
By using 
- linkFlight function
- matchFlight functnon
- findFlightConnection function

4.(flightNetwork.c) it can also find the shortest way and shortest time to transit from flight to flight and use the

- findShortestTransitTime function	
- flightBeforeTransit function	
- flightAfterTransit function	


The thing that aren't working are

1.Find the itinerary using dijkstra's shortest path algorithm 
- For 0 transit it sometime error and loop to infinity.
- For 1 transit it sometime can find only the itinerary that have the shortest path. For example is the result of the first loop of dijkstra's shortest path is shortest itinerary that have the path but the second result doesn't have to same path as the first one due to the transit time. I don't know how to it yet but it should work like that. After one loop the transition between that two flight have to be remove to find another itinerary. If the program print all the flight in the path mean that there are no transition of the flight in the first edge if the path. The program will try to printf the flight in another path but if the consider only the path. The shortest path is the same but there are no transition of flight in that path to print and it will error.
- For more that one transit it have to same problem as 1 transit and the weight are wrong because I can't add the transit time after 1 transit to the weight.

I think this flight finding way is bad. There are lot of bug that I don't know how to fix it. Can you guide me on how to fix or rewrite it. If I should use this way or find another way.

Thank you