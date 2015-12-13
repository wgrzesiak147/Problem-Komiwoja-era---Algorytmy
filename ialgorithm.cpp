#include "ialgorithm.h"
#include <vector>
#include <time.h>
using namespace std;

IAlgorithm::IAlgorithm()
{

}


// generuje losowe rozwiazanie dla zadanej liczby miast
vector<int> IAlgorithm::randomSolution(int number)
{
    //losowanie początkowego rozwiązania 'sol'
    vector<int> v;
    vector<int> sol;					//wektor rozwiązania z numerami kolejnych wierzchołków
    for (int i = 0; i != number; i++)
        v.push_back(i);

    srand(time(NULL));
    for (int i = 0; i != number; i++)
    {
        int x = rand() % v.size();
        sol.push_back(v[x]);
        v.erase(v.begin() + x);
    }
    sol.push_back(sol[0]);				//ostatnim wierzchołek musi być równy pierwszemu (komiwojażer wraca do początkowego miasta)

    return sol;
}

// zwraca koszt drogi dla zadanego wektora rozwiazania
int IAlgorithm::cost(vector<int>& sol,QPair<unsigned int,unsigned int> ** adjencyMatrix,int size)
{
    int cost = 0;
   // for (int i = 0; i != sol.size() - 1; i++)
      //  cost += adjencyMatrix[sol[i]][sol[i + 1]];//trzeba sie tu jeszcze dostać do wartości i ją jakoś wyliczyć
    return cost;
}

