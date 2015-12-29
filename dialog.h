#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTime>
#include <QFileDialog>
#include <QFile>
#include "adjacencymatrix.h"
#include "adjacencymatrixloader.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void stringToList(QString listElement);

private slots:
    void on_pushButton_clicked();

    void on_matrixLoadButton_clicked();

    void on_clearButton_clicked();

private:
    Ui::Dialog *ui;
    QFileDialog fileDialog;
    AdjacencyMatrix * adjacencyMatrix = NULL;
    QTime clock;

};

#endif // DIALOG_H
