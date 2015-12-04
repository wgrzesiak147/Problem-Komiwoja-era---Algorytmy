#include "dialog.h"
#include <QApplication>
#include <QDebug>
#include "adjacencymatrix.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    qDebug() << "***Test code KW";

    int i =10;
    QString name = "siema tu Wojtek";
    QString name2 = "TROLOLO";

    //Test macierzy
    qDebug() << "Test macierzy";
    AdjacencyMatrix * matrix = new AdjacencyMatrix(2);
    qDebug() << "addEdge:" << matrix->addEdge(0,1,10,20);
    qDebug() << "addEdge:" << matrix->addEdge(1,0,10,20);

    qDebug() << "getDistance:" << matrix->getDistance(0,1);
    qDebug() << "getTime:" << matrix->getTime(0,1);
    qDebug() << "isFull:" << matrix->isFull();

    //Test macierzy
    return a.exec();
}
