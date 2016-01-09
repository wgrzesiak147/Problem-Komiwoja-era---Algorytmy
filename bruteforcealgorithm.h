#ifndef BRUTEFORCEALGORITHM_H
#define BRUTEFORCEALGORITHM_H

#include "ialgorithm.h"

using namespace std;
class BruteForceAlgorithm : public IAlgorithm
{
public:
    int bestSolution;
    Route * bestRoute;
    BruteForceAlgorithm();
    Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int startNode);
private :
    //QVector<int> permutacje (QVector<int> T, int ix);
    Route * permutations (Route * T, int ix);
};

#endif // BRUTEFORCEALGORITHM_H
