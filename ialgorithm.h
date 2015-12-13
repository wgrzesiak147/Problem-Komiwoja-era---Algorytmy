#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <QObject>
#include <vector>

using namespace std;
class IAlgorithm : QObject
{
public:
    IAlgorithm();

   // Vector<int> IAlgorithm::calculateRoute(QPair** adjencyMatrix,int size,Vector<QPair>)=0;
    virtual vector<int> calculateRoute(QPair<unsigned int,unsigned int> ** adjencyMatrix,int size,vector<QPair<int,int>>)=0;
    vector<int> randomSolution(int);
    int cost(vector<int>& sol,QPair<unsigned int,unsigned int> ** adjencyMatrix,int size);

};

#endif // IALGORITHM_H
