#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <QObject>
#include <QPair>
#include <QDebug>

class AdjacencyMatrix : public QObject
{
    Q_OBJECT
public:
    //explicit AdjacencyMatrix(QObject *parent = 0);
    AdjacencyMatrix(unsigned int size,QObject *parent = 0);
    ~AdjacencyMatrix();
    bool addEdge(unsigned int startNode, unsigned int destinationNode, unsigned int distance, unsigned int time);
    bool deleteEdge(unsigned int startNode, unsigned int destinationNode);
    unsigned int getDistance(unsigned int startNode, unsigned int destinationNode);
    unsigned int getTime(unsigned int startNode, unsigned int destinationNode);
    unsigned int getSize();
    bool isFull();


signals:

public slots:

private:
    QPair<unsigned int,unsigned int> ** matrix;
    unsigned int matrixSize = 0;
};

#endif // ADJACENCYMATRIX_H
