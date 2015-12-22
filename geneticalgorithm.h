#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "ialgorithm.h"


class GeneticAlgorithm : public IAlgorithm
{
public:
    GeneticAlgorithm();
    Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int size);

};

#endif // GENETICALGORITHM_H
