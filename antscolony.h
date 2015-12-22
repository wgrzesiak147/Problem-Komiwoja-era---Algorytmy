#ifndef ANTSCOLONY_H
#define ANTSCOLONY_H

#include "ialgorithm.h"

class AntsColony : public IAlgorithm
{
public:
    AntsColony();
    Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int size);
};

#endif // ANTSCOLONY_H
