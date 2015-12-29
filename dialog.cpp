#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::stringToList(QString listElement)
{
    QString string;
    string.append(clock.currentTime().toString("hh:mm:ss"));
    string.append(": ");
    string.append(listElement);


    ui->listWidget->addItem(string);
}

void Dialog::on_pushButton_clicked()
{

}

void Dialog::on_matrixLoadButton_clicked()
{
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter(tr("Matrix files (*.mtx)"));
    fileDialog.show();

    QStringList fileNames;
    if (fileDialog.exec())
    {
        fileNames = fileDialog.selectedFiles();
        if(!fileNames.isEmpty())
        {
            AdjacencyMatrixLoader loader;
            connect(&loader,SIGNAL(errorString(QString)),this,SLOT(stringToList(QString)));
            QFile  file(fileNames.at(0));
            adjacencyMatrix = loader.getAdjacencyMatrixFromFile(&file);

        }
    }
}

void Dialog::on_clearButton_clicked()
{

}
