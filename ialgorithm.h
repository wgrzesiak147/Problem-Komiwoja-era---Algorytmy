#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <QObject>
#include <QMap>
#include "adjacencymatrix.h"
#include "route.h"

class IAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit IAlgorithm(QObject *parent = 0);
    virtual Route * calculateRoute(AdjacencyMatrix * adjacencyMatrix, unsigned int size) = 0;

signals:
    void started();
    void finished();

public slots:
};

#endif // IALGORITHM_H
