#include "antscolony.h"

AntsColony::AntsColony()
{

}

Route * AntsColony::calculateRoute(AdjacencyMatrix *adjacencyMatrix,  unsigned int startNode)
{


    Route * startRoute = new Route(adjacencyMatrix->getSize(),adjacencyMatrix);
    startRoute->makeRandomRoute(startNode);

    int bestSol = startRoute->getCost(costType);
    int feromon = 10;

    Route * sol = new Route(startRoute);
    while(feromon < 1000)
    {

        Route * nextRoute = new Route(adjacencyMatrix->getSize(),adjacencyMatrix);
        nextRoute->makeRandomRoute(startNode);
        int nextRouteSol = nextRoute->getCost(costType);
        if(nextRouteSol > bestSol)
        {
            startRoute = new Route(nextRoute);
            bestSol = nextRouteSol;
            feromon = 0;
        }
        feromon+=10;

    }

    return startRoute;
}

