#ifndef ANNEALINGALGORITHM_H
#define ANNEALINGALGORITHM_H

#include "ialgorithm.h"

class AnnealingAlgorithm  : public IAlgorithm
{
public:
   static double Temperature;
   static double AnnealingParameter;
   static double EndTemperature;
   AnnealingAlgorithm();
   Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int startNode);
   Route * dupa(AdjacencyMatrix *adjacencyMatrix, unsigned int startNode);
private:
   Route * makeMutation(Route * route);

};

#endif // ANNEALINGALGORITHM_H
