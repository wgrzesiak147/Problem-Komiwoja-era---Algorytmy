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

/*
Route * AnnealingAlgorithm::adjacentSolution(Route* sol)
{
    Route*  _sol = new Route(sol);

        //wyznaczenie losowego rozwiązania sąsiedniego "_sol" poprzez zamianę dwóch losowych wierzchołków
        //Przykład: sol = {2, 1, 3, 0, 2}; // sol.size() = 5;  ale zawsze v[0] = v[4] (pierwsze miasto jest ostatnim miastem)
        //dlatego ostatniego indeksu nie rozważam do losowania - jego wartość zawsze będzie równa v[0]
        int x1, x2, tmp;					//zamienie wierzcholek x1 z wierzcholkiem x2
        x1 = rand() % (_sol->getSize() - 1);
        x2 = rand() % (_sol->getSize() - 1);
        if (x2 == x1)					//aby nie wylosować 2x tego samego wierzcholka
        {
            if (x2 == _sol->getSize() - 2)	// gdy są takie same i są ostatnim miaste, to zamieniamy ostatnie z przedostatnim
                x2--;
            else
                x2++;					//jeśli takie same, ale nie są ostatnim miastem to zamieniamy wylosowany z kolejnym
        }

        //zamiana wylosowanych wierzcholkow
        tmp = _sol->at(x1);
        _sol->insertNode(x1,_sol->at(x2));
        _sol->insertNode(x2,tmp);
        _sol->insertNode(_sol.size() - 1,_sol->at(0));

        return _sol;

}
*/
