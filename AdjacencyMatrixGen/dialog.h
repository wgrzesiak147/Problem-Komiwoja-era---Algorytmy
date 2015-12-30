#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
