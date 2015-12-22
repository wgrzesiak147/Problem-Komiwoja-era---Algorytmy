#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <QObject>
#include <QPair>
#include <QDebug>
#include <QVector>

class AdjacencyMatrix : public QObject
{
    Q_OBJECT
public:
    //explicit AdjacencyMatrix(QObject *parent = 0);
    AdjacencyMatrix(unsigned int size,QObject *parent = 0);
    ~AdjacencyMatrix();
    bool addEdge(unsigned int startNode, unsigned int destinationNode, unsigned int distance, unsigned int time);
    bool deleteEdge(unsigned int startNode, unsigned int destinationNode);
    bool setTimeSlot(unsigned int nodeNumber, unsigned int startTime, unsigned int endTime);
    unsigned int getDistance(unsigned int startNode, unsigned int destinationNode);
    unsigned int getTime(unsigned int startNode, unsigned int destinationNode);
    unsigned int getStartTime(unsigned int nodeNumber);
    unsigned int getEndTime(unsigned int nodeNumber);
    unsigned int getSize();
    bool isFull();


signals:

public slots:

private:
    QPair<unsigned int,unsigned int> ** matrix;
    unsigned int matrixSize = 0;
    QVector<QPair<unsigned int,unsigned int> > timeSlots;
};

#endif // ADJACENCYMATRIX_H
