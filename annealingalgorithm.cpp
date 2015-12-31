#include "annealingalgorithm.h"

AnnealingAlgorithm::AnnealingAlgorithm()
{

}


Route * AnnealingAlgorithm::calculateRoute(AdjacencyMatrix *adjacencyMatrix,  unsigned int startNode)
{
        double t =1000; //temperatura początkowa
        double p =1; //współczynnik
        int n = adjacencyMatrix->getSize(); //liczba miast

        int worseSol = 0; // licznik znalezionych gorszych rozwiazan (odrzuconych)

        // jesli algorytm 15%n razy odrzuci rozwiazanie, przerywamy dzialanie
        int worseAcceptable = 0.15 * n; // akceptowalna liczba gorszych rozwiazan w danym kroku


        //ROZWIAZANIE POCZATKOWE"

        Route * sol = new Route(adjacencyMatrix->getSize(),adjacencyMatrix);
        sol->makeRandomRoute(startNode);


        Route * bestSol = new Route(sol);			// wylosowane rozwiązanie jest automatycznie najlepszym, ponieważ jest to jedyne rozwiązanie
        Route * _sol = new Route(sol);				//_sol - rozwiązanie sąsiednie

        int costSol, cost_Sol, costBestSol;
        costSol =   sol->getCost(Route::WITHOUT_TIME);
        costBestSol = costSol;

        ////////////// algorytm wyżarzania
        //double temp = costSol;
        double temp = t;
        //for (int i = 0; i != L; i++)
        while (!(worseSol > worseAcceptable))
        {
            _sol = adjacentSolution(*sol);		// rozwiązanie sąsiednie
            cost_Sol = _sol->getCost(Route::WITHOUT_TIME);

            //  sprawdzenie czy nowe rozwiązanie jest lepsze od najlepszego
            if (cost_Sol < costBestSol)
            {
                bestSol = _sol;
                costBestSol = cost_Sol;
            }
            double delta = cost_Sol - costSol;
            if (delta < 0)
            {
                sol = _sol;
                costSol = cost_Sol;

                worseSol = 0;
            }
            else
            {
                worseSol++;
                double x = (rand() % 10000) / 10000.0;	// losowa liczba z zakresu <0, 1)


                if (x < (exp((-delta) / temp)))
                {
                    sol = _sol;
                    costSol = cost_Sol;

                }

            }
            temp *= p; // zmniejszamy temperature wg zadanego wspolczynnika

            // przerywamy dzialanie algorytmu, jesli 15%n razy znaleziono gorsze rozwiazanie
        }

        return bestSol;
}


Route * AnnealingAlgorithm::adjacentSolution(Route &sol)
{
    Route * rout;
    return rout;

}
