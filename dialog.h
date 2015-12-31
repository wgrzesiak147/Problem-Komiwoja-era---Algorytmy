#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTime>
#include <QFileDialog>
#include <QFile>
#include <QElapsedTimer>
#include <QThread>
#include "adjacencymatrix.h"
#include "adjacencymatrixloader.h"
#include "ialgorithm.h"
#include "antscolony.h"
#include "geneticalgorithm.h"
#include "annealingalgorithm.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    enum algorithmType{BRUTE_FORCE = 1, GENETIC = 2, ANTS_COLONY = 3, SIMULATED_ANNEALING = 4};
    ~Dialog();

public slots:
    void stringToList(QString listElement);
    void onAlgorithmStarted();
    void onAlgorithmFinished();

private slots:
    void on_pushButton_clicked();

    void on_matrixLoadButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::Dialog *ui;
    QFileDialog fileDialog;
    AdjacencyMatrix * adjacencyMatrix = NULL;
    QTime clock;
    algorithmType aType;
    Route::costType cType = Route::WITHOUT_TIME;
    QElapsedTimer timer;
    qint64 elapsedTime = 0;
    QString enumAlgorithmTypeToString(algorithmType type);
    QString enumCostTypeToString(Route::costType type);

};

#endif // DIALOG_H
