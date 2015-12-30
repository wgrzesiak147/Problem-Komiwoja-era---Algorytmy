#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{

}

bool routeLessThanWithTime(Route *route1, Route *route2)
{
    return route1->getCost(Route::WITH_TIME) < route2->getCost(Route::WITH_TIME);
}

bool routeLessThanWithoutTime(Route *route1, Route *route2)
{
    return route1->getCost(Route::WITHOUT_TIME) < route2->getCost(Route::WITHOUT_TIME);
}

Route * GeneticAlgorithm::calculateRoute(AdjacencyMatrix *adjacencyMatrix,  unsigned int startNode)
{
    emit started();
    QList<Route*> routeListToNextRound;
    QList<Route*> routeList;
    QList<Route*> routeListToDoOperations;
    Route * currentBestRoute= NULL;
    unsigned int populationSizeRatio = 10;
    unsigned int populationSize = adjacencyMatrix->getSize() * populationSizeRatio;
    unsigned int roundsWithoutBetterRoute = 0;
    //int numberOfRoutesToNextRound
    for(unsigned int i = 0; i < populationSize; i++)
    {
        Route * tempRoute = new Route(adjacencyMatrix->getSize(),adjacencyMatrix);
        tempRoute->makeRandomRoute(startNode);
        routeListToNextRound.append(tempRoute);
    }

    do
    {
        int routeListToNextRoundSize = routeListToNextRound.size();
        for(int j = 0; j < routeListToNextRoundSize; j++)
        {
            routeList.append(routeListToNextRound.at(0));
            routeListToNextRound.removeFirst();
        }

        if(costType == Route::WITH_TIME)qSort(routeList.begin(),routeList.end(),routeLessThanWithTime);
        if(costType == Route::WITHOUT_TIME)qSort(routeList.begin(),routeList.end(),routeLessThanWithoutTime);

        if (currentBestRoute == NULL)
        {
            //currentBestRoute = new Route(*routeList.at(0));
            Route * tempRoute = new Route(routeList.at(0));

            //*tempRoute = *routeList.at(0);
            currentBestRoute = tempRoute;
        }
        else
        {
            if(routeList.at(0)->getCost(costType) < currentBestRoute->getCost(costType))
            {
                delete(currentBestRoute);
                Route * tempRoute = new Route(routeList.at(0));
                //Route * tempRoute = new Route(routeList.at(0)->getSize(),routeList.at(0)->getAdjacencyMatrix());
                //*tempRoute = *routeList.at(0);
                //currentBestRoute = new Route(*routeList.at(0));
                currentBestRoute = tempRoute;
                roundsWithoutBetterRoute = 0;
            }
            else
            {
                roundsWithoutBetterRoute++;
            }
        }

        int routeListSize = routeList.size();
        for(int k = 0; k < routeListSize/10 ; k++)
        {
              routeListToDoOperations.append(routeList.at(0));
              routeList.removeFirst();
        }

        qDeleteAll(routeList);
        routeList.clear();

        for(int l = 0; l < 10; l++)
        {
            routeListToNextRound.append(crossbreedRoutes(routeListToDoOperations.at(0),routeListToDoOperations.at(1)));
        }

        for(int l = 0; l < populationSize/2; l++)
        {
            routeListToNextRound.append(crossbreedRoutes(routeListToDoOperations.at(qrand() % routeListToDoOperations.size()),routeListToDoOperations.at(qrand() % routeListToDoOperations.size())));
        }
        for(int m = 0; m < populationSize/2; m++)
        {
            routeListToNextRound.append(makeMutation(routeListToNextRound.at(qrand() % routeListToNextRound.size())));
        }
        routeListToNextRound.append(new Route(currentBestRoute));
        qDeleteAll(routeListToDoOperations);
        routeListToDoOperations.clear();
    }
    while(roundsWithoutBetterRoute < 10);

    qDeleteAll(routeListToNextRound);
    routeListToNextRound.clear();
    //qDeleteAll(routeListToDoOperations);
    //routeListToDoOperations.clear();
    emit finished();
    return currentBestRoute;

}

Route *GeneticAlgorithm::crossbreedRoutes(Route *firstRoute, Route *secondRoute)
{
    Route * result = new Route(firstRoute->getSize(),firstRoute->getAdjacencyMatrix());
    //QMap<unsigned int,unsigned int> nodeMap;
    QList<unsigned int> unusedNodes;

    unsigned int firstPosition = 0;
    unsigned int secondPosition = 0;

    do
    {
        firstPosition = qrand() % firstRoute->getSize();
        secondPosition = qrand() % firstRoute->getSize();
    }
    while(!((firstPosition != 0) && (secondPosition != 0)));

    for(unsigned int m = 0; m < firstRoute->getSize(); m++)
    {
        unusedNodes.append(m);
    }

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
        if(secondPosition < (result->getSize() - 1))
        {
            secondPosition = secondPosition + 1;
        }

    }
    result->insertNode(0,firstRoute->at(0));
    unusedNodes.removeOne(firstRoute->at(0));

    for(unsigned int i = firstPosition; i<=secondPosition; i++)
    {
        result->insertNode(i,firstRoute->at(i));
        unusedNodes.removeOne(firstRoute->at(i));
    }
    for(unsigned int j = 1; j < firstPosition; j++)
    {
        if(!result->containsNode(secondRoute->at(j)))
        {
            result->insertNode(j,secondRoute->at(j));
            unusedNodes.removeOne(secondRoute->at(j));
        }
    }
    for(unsigned int k = secondPosition + 1; k < firstRoute->getSize(); k++)
    {
        if(!result->containsNode(secondRoute->at(k)))
        {
            result->insertNode(k,secondRoute->at(k));
            unusedNodes.removeOne(secondRoute->at(k));
        }
    }
    for(unsigned int n = 1; n < firstRoute->getSize(); n++)
    {
        if(result->at(n) == -1)
        {
            if(unusedNodes.size() != 0)
            {
                unsigned int randomNodePosition = qrand() % unusedNodes.size();
                result->insertNode(n,unusedNodes.at(randomNodePosition));
                unusedNodes.removeAt(randomNodePosition);
            }
            else
            {
                qDebug() << "Watch here";
            }
        }


    }
    //qDebug() << "First position:" << firstPosition << "Second position" << secondPosition;
    return result;

}

Route *GeneticAlgorithm::makeMutation(Route *route)
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


