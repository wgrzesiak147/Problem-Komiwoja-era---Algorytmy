#ifndef ADJACENCYMATRIXLOADER_H
#define ADJACENCYMATRIXLOADER_H

#include <QObject>
#include <QFile>
#include "adjacencymatrix.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

class AdjacencyMatrixLoader : public QObject
{
    Q_OBJECT
public:
    explicit AdjacencyMatrixLoader(QObject *parent = 0);
    AdjacencyMatrix *getAdjacencyMatrixFromFile(QFile * source);

signals:
    void errorString(QString errorString);

public slots:
};

#endif // ADJACENCYMATRIXLOADER_H
