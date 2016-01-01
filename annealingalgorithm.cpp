#include "annealingalgorithm.h"

AnnealingAlgorithm::AnnealingAlgorithm()
{

}
double AnnealingAlgorithm::Temperature = 1000;
double AnnealingAlgorithm::AnnealingParameter = 1;

Route * AnnealingAlgorithm::calculateRoute(AdjacencyMatrix *adjacencyMatrix,  unsigned int startNode)
{
        double t =Temperature; //temperatura początkowa
        double p =AnnealingParameter; //współczynnik
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

        while (!(worseSol > worseAcceptable))
        {
            _sol = makeMutation(sol);		// rozwiązanie sąsiednie
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

Route *AnnealingAlgorithm::makeMutation(Route *route)
{
    Route * result = new Route(route->getSize(),route->getAdjacencyMatrix());
    for(unsigned int i = 0; i < route->getSize(); i++)
    {
        result->insertNode(i,route->at(i));
    }
    unsigned int firstPosition = 0;
    unsigned int secondPosition = 0;
    unsigned int tempNodeNumber = 0;
    unsigned int tempNodeNumber2 = 0;

    do
    {
        firstPosition = qrand() % route->getSize();
        secondPosition = qrand() % route->getSize();
    }
    while(!((firstPosition != 0) && (secondPosition != 0)));

    if(firstPosition > secondPosition)
    {
        unsigned int tempValue = firstPosition;
        firstPosition = secondPosition;
        secondPosition = tempValue;
    }

    if(firstPosition == secondPosition)
    {
        if(firstPosition > 1)
        {
            firstPosition = firstPosition - 1;
        }
        if(secondPosition != (result->getSize() - 1))
        {
            secondPosition = secondPosition + 1;
        }
    }

    tempNodeNumber = route->at(firstPosition);
    tempNodeNumber2 = route->at(secondPosition);

    result->insertNode(firstPosition,-1);
    result->insertNode(secondPosition,-2);

    result->insertNode(firstPosition,tempNodeNumber2);
    result->insertNode(secondPosition,tempNodeNumber);

    return result;
}


