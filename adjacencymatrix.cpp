#include "adjacencymatrix.h"

AdjacencyMatrix::AdjacencyMatrix(unsigned int size, QObject *parent) : QObject(parent)
{
    matrix = new QPair<unsigned int,unsigned int> * [size];
    matrixSize = size;

    for(int i = 0; i<size; i++)
    {
        matrix[i] = new QPair<unsigned int,unsigned int> [size];
    }

    for(int m = 0; m<size; m++)
    {
        for(int n = 0; n<size; n++)
        {
            matrix[m][n].first = 0;
            matrix[m][n].second = 0;
        }
    }
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    for(int i = 0; i<matrixSize; i++)
    {
        delete(matrix[i]);
    }
}

bool AdjacencyMatrix::addEdge(unsigned int startNode, unsigned int destinationNode, unsigned int distance, unsigned int time)
{
    if((startNode<matrixSize)&&(destinationNode<matrixSize)&&(distance)&&(time))
    {

        matrix[startNode][destinationNode].first = distance;
        matrix[startNode][destinationNode].second = time;
        return true;
    }
    else
    {
        return false;
    }
}

bool AdjacencyMatrix::deleteEdge(unsigned int startNode, unsigned int destinationNode)
{
    if((startNode<matrixSize)&&(destinationNode<matrixSize))
    {

        matrix[startNode][destinationNode].first = 0;
        matrix[startNode][destinationNode].second = 0;
        return true;
    }
    else
    {
        return false;
    }
}

unsigned int AdjacencyMatrix::getDistance(unsigned int startNode, unsigned int destinationNode)
{
    if((startNode<matrixSize)&&(destinationNode<matrixSize))
    {
        return matrix[startNode][destinationNode].first;
    }
    else
    {
        return 0;
    }
}

unsigned int AdjacencyMatrix::getTime(unsigned int startNode, unsigned int destinationNode)
{
    if((startNode<matrixSize)&&(destinationNode<matrixSize))
    {
        return matrix[startNode][destinationNode].second;
    }
    else
    {
        return 0;
    }
}

unsigned int AdjacencyMatrix::getSize()
{
    return matrixSize;
}

bool AdjacencyMatrix::isFull()
{
    bool isFull = false;

    for(int m = 0; m<matrixSize; m++)
    {
        for(int n = 0; n<matrixSize; n++)
        {
            if(m!=n)
            {
                if((matrix[m][n].first == 0)||(matrix[m][n].second == 0))
                {
                    return false;
                }
            }
        }
    }
    return true;

}


