#ifndef ROUTE_H
#define ROUTE_H

#include <QObject>
#include <QVector>
#include "adjacencymatrix.h"
class Route : public QObject
{
    Q_OBJECT
public:
    enum costType{WITHOUT_TIME = 1, WITH_TIME = 2};
    //explicit Route(unsigned int size,QObject *parent = 0);
    Route(unsigned int size, AdjacencyMatrix * graph ,QObject *parent = 0);
    //unsigned int getTime();
    unsigned int getLength(Route::costType costType = WITHOUT_TIME);
    bool insertNode(unsigned int position, unsigned int numberOfNode);
    void printRoute();
    void clear();
    int at(unsigned int position);




signals:

public slots:

private:
    QVector<int> route;
    unsigned int numberOfNodes = 0;
    AdjacencyMatrix * graphData = NULL;
};

#endif // ROUTE_H
