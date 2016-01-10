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

    Route * nextRoute = new Route(adjacencyMatrix->getSize(),adjacencyMatrix);
    nextRoute->makeRandomRoute(startNode);

    Route * sol = new Route(startRoute);
    while(feromon < 10000)
    {

        int nextRouteSol = nextRoute->getCost(costType);
        if(nextRouteSol < bestSol)
        {
            startRoute = new Route(nextRoute);
            bestSol = nextRouteSol;
            feromon = 0;
        }
        feromon+=10;
        makeMutation(nextRoute);

    }

    return startRoute;
}

Route * AntsColony::makeMutation(Route *route)
{
    Route * result = new Route(route->getSize(),route->getAdjacencyMatrix());
    for(unsigned int i = 0; i < route->getSize(); i++)
    {
        result->insertNode(i,route->at(i));
    }
    unsigned int firstPosition = 0;
    unsigned int secondPosition = 0;
    unsigned int tempNodeNumber = 0;
    unsigned int tempNodeNumber2 = 0;

    do
    {
        firstPosition = qrand() % route->getSize();
        secondPosition = qrand() % route->getSize();
    }
    while(!((firstPosition != 0) && (secondPosition != 0)));

    if(firstPosition > secondPosition)
    {
        unsigned int tempValue = firstPosition;
        firstPosition = secondPosition;
        secondPosition = tempValue;
    }

    if(firstPosition == secondPosition)
    {
        if(firstPosition > 1)
        {
            firstPosition = firstPosition - 1;
        }
        if(secondPosition != (result->getSize() - 1))
        {
            secondPosition = secondPosition + 1;
        }
    }

    tempNodeNumber = route->at(firstPosition);
    tempNodeNumber2 = route->at(secondPosition);

    result->insertNode(firstPosition,-1);
    result->insertNode(secondPosition,-2);

    result->insertNode(firstPosition,tempNodeNumber2);
    result->insertNode(secondPosition,tempNodeNumber);

    return result;
}

