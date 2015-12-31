#ifndef ANNEALINGALGORITHM_H
#define ANNEALINGALGORITHM_H

#include "ialgorithm.h"

class AnnealingAlgorithm  : public IAlgorithm
{
public:
   AnnealingAlgorithm();
   Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int startNode);
private:
   Route * makeMutation(Route * route);
   //Route * adjacentSolution(Route *sol);
};

#endif // ANNEALINGALGORITHM_H
