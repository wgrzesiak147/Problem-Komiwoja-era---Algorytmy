#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "ialgorithm.h"



class GeneticAlgorithm : public IAlgorithm
{
public:
    GeneticAlgorithm();
    Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int startNode);

private:
    Route * crossbreedRoutes(Route * firstRoute,Route * secondRoute);
    Route * makeMutation(Route * route);
    //bool routeLessThan(Route *route1, Route *route2);

};

#endif // GENETICALGORITHM_H
