#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "ialgorithm.h"



class GeneticAlgorithm : public IAlgorithm
{
public:
    GeneticAlgorithm();
    Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int size);
    Route * crossbreedRoutes(Route * firstRoute,Route * secondRoute);
    Route * makeMutation(Route * route);

};

#endif // GENETICALGORITHM_H
