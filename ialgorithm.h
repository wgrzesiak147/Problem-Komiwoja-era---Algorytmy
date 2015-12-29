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
    virtual Route * calculateRoute(AdjacencyMatrix * adjacencyMatrix, unsigned int startNode) = 0;
    void setCostType(Route::costType type);

signals:
    void started();
    void finished();

public slots:

protected:
    Route::costType costType = Route::WITHOUT_TIME;
};

#endif // IALGORITHM_H
