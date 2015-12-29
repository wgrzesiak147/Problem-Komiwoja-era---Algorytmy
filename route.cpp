#include "route.h"


Route::Route(unsigned int size, AdjacencyMatrix * graph ,QObject *parent): QObject(parent)
{
    numberOfNodes = size;
    for(unsigned int i=0; i<numberOfNodes; i++)
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

/*Route::Route(Route *route, QObject *parent)
{
    if(route != NULL)
    {
        Route(route->getSize(),route->getAdjacencyMatrix(),parent);
        this->clear();
        for(unsigned int i = 0; i < route->getSize(); i++)
        {
            this->insertNode(i,route->at(i));
        }
    }
}*/

unsigned int Route::getCost(Route::costType costType)
{
    unsigned int totalLength = 0;
    unsigned int totalTime = 0;
    unsigned int totalCost = 0;
    unsigned int totalPenalty = 0;
    double penaltyRatio = 1;
    switch(costType)
    {
    case WITHOUT_TIME:
        for(unsigned int i=0; i<numberOfNodes; i++)
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
        totalCost = totalLength;
        return totalCost;

        break;

    case WITH_TIME:
        for(unsigned int i=0; i<numberOfNodes; i++)
        {
            if((totalTime >= graphData->getStartTime(i)) && (totalTime <= graphData->getEndTime(i)))
            {
                //qDebug() << "Node:" << i << "In time slot";
            }
            else
            {
                //qDebug() << "Node:" << i << "Not in time slot";
                if(totalTime < graphData->getStartTime(i))
                {
                    unsigned int penalty = (graphData->getStartTime(i) - totalTime) * penaltyRatio;
                    totalPenalty = totalPenalty + penalty;
                    //qDebug() << "Penalty for node" << i << ":" << penalty;
                }
                else
                {
                    unsigned int penalty = (totalTime - graphData->getEndTime(i)) * penaltyRatio;
                    totalPenalty = totalPenalty + penalty;
                    //qDebug() << "Penalty for node:" << i << "=" << penalty;
                }
            }
            if(i != (numberOfNodes - 1))
            {
                totalTime = totalTime + graphData->getTime(route[i],route[i+1]);
            }
            else
            {
                totalTime = totalTime + graphData->getTime(route[i],route[0]);
            }

        }

        totalLength = this->getCost(Route::WITHOUT_TIME);

        totalCost = totalLength + totalPenalty;
        return totalCost;

        break;

    default:
        return 0;
        break;
    }

}

unsigned int Route::getSize()
{
    return numberOfNodes;
}

AdjacencyMatrix *Route::getAdjacencyMatrix()
{
    return graphData;
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

bool Route::containsNode(unsigned int nodeNumber)
{
    return route.contains(nodeNumber);
}

void Route::printRoute()
{
    qDebug() << "Route: ";
    for(unsigned int i = 0; i < numberOfNodes; i++)
    {
        qDebug() << route.at(i);
    }
}

QString Route::printRouteToString()
{
    QString result;
    result.append("Calculated route: [ ");

    for(unsigned int i = 0; i < numberOfNodes; i++)
    {
        result.append(QString::number(route.at(i)));
        result.append(" ");
    }
    result.append("] ");
    return result;
}

void Route::clear()
{
    for(unsigned int i = 0; i < numberOfNodes; i++)
    {
        route[i]= -1;
    }
}

int Route::at(unsigned int position)
{
    return route.at(position);
}

void Route::makeRandomRoute(unsigned int startNode)
{
    QList<unsigned int> nodeList;
    unsigned int randNode = 0;
    for(unsigned int i=0; i<numberOfNodes; i++)
    {
        if (i!=startNode)
        {
            nodeList.append(i);
        }
    }
    this->insertNode(0,startNode);

    for(unsigned int i=1; i<numberOfNodes; i++)
    {
        int position = qrand() % nodeList.size();
        randNode = nodeList.at(position);
        nodeList.removeAt(position);
        this->insertNode(i,randNode);
    }
}
