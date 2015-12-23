#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{

}

Route * GeneticAlgorithm::calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int size)
{

}

Route *GeneticAlgorithm::crossbreedRoutes(Route *firstRoute, Route *secondRoute)
{
    Route * result = new Route(firstRoute->getSize(),firstRoute->getAdjacencyMatrix());
    unsigned int firstPosition = qrand() % firstRoute->getSize();
    unsigned int secondPosition = qrand() % firstRoute->getSize();

    if(firstPosition > secondPosition)
    {
        unsigned int tempValue = firstPosition;
        firstPosition = secondPosition;
        secondPosition = tempValue;
    }
    if(firstPosition == secondPosition)
    {
        if(firstPosition != 0)
        {
            firstPosition = firstPosition - 1;
        }
        if(secondPosition != (result->getSize() - 1))
        {
            secondPosition = secondPosition + 1;
        }
        for(unsigned int i = firstPosition; i<=secondPosition; i++)
        {
            result->insertNode(i,firstRoute->at(i));
        }

    }
    result->insertNode(0,firstRoute->at(0));

}

