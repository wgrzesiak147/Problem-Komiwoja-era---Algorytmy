#include "route.h"


Route::Route(unsigned int size, AdjacencyMatrix * graph ,QObject *parent): QObject(parent)
{
    numberOfNodes = size;
    for(int i=0; i<numberOfNodes; i++)
    {
        route.append(-1);
    }
    if(graph->getSize()== numberOfNodes)
    {
        graphData = graph;
    }
    else
    {
        qDebug() << "Warning!: Route(): The size of graph is different from the size of route";
    }
}

unsigned int Route::getLength(Route::costType costType)
{
    unsigned int totalLength = 0;
    switch(costType)
    {
    case WITHOUT_TIME:
        for(int i=0; i<numberOfNodes; i++)
        {
            if(i!=(numberOfNodes-1))
            {
                totalLength = totalLength + graphData->getDistance(route[i],route[i+1]);
            }
            else
            {
                totalLength = totalLength + graphData->getDistance(route[i],route[0]);
            }
        }
        return totalLength;

        break;

    case WITH_TIME:

        break;

    default:
        return 0;
        break;
    }

}

bool Route::insertNode(unsigned int position, unsigned int numberOfNode)
{
    if(position < numberOfNodes)
    {
        if(route.contains(numberOfNode))
        {
            qDebug() << "Warning!: insertNode(): Route already contains the node number:" << numberOfNode << "Route may be invalid";
            route[position] = numberOfNode;
        }
        else
        {
            route[position] = numberOfNode;
        }
        return true;
    }
    else
    {
        qDebug() << "Warning!: insertNode(): Position out of range";
        return false;
    }
}

void Route::printRoute()
{
    qDebug() << "Route: ";
    for(int i = 0; i < numberOfNodes; i++)
    {
        qDebug() << route.at(i);
    }
}

void Route::clear()
{
    for(int i = 0; i < numberOfNodes; i++)
    {
        route[i]= -1;
    }
}

int Route::at(unsigned int position)
{
    return route.at(position);
}
