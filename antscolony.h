#ifndef ANTSCOLONY_H
#define ANTSCOLONY_H

#include "ialgorithm.h"

//Algorytm nie działa tak jak powinien, kod do poprawki

class AntsColony : public IAlgorithm
{
public:
    AntsColony();
    Route * calculateRoute(AdjacencyMatrix *adjacencyMatrix, unsigned int startNode);
private:
    Route * makeMutation(Route * route);
};

#endif // ANTSCOLONY_H
