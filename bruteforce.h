#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "ialgorithm.h"

class BruteForce : public IAlgorithm
{
public:
    BruteForce();
    Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int startNode);
};

#endif // BRUTEFORCE_H
