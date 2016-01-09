#include "bruteforcealgorithm.h"

BruteForceAlgorithm::BruteForceAlgorithm()
{

}
Route * BruteForceAlgorithm::calculateRoute(AdjacencyMatrix *adjacencyMatrix,  unsigned int startNode)
{
        emit started();

        Route * sol = new Route(adjacencyMatrix->getSize(),adjacencyMatrix);

        sol->makeRandomRoute(startNode);

        bestRoute = new Route(sol);

        bestRoute->printRoute();

        bestSolution = sol->getCost(costType);

        sol->route.removeAt(0);

        permutations(sol,0);

        emit finished();

        bestRoute->printRoute();
        return bestRoute;
}

Route * BruteForceAlgorithm::permutations(Route*  T, int ix)
{
    if( ix < T->route.size()-1 )
      {
        for(int i = ix; i < T->route.size(); i++)
        {
          swap(T->route[ix], T->route[i]);
          permutations(T, ix+1);
          swap(T->route[ix], T->route[i]);
        }
      }
      else
    {
        T->route.insert(0,T->currentStartNode);
        int currentSolution = T->getCost(costType);
        if( currentSolution < bestSolution)
        {
             bestRoute = new Route(T);
             bestSolution = currentSolution;
        }
        T->route.removeAt(0);
        return T;
    }

}


