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
    ui->listWidget->scrollToBottom();
}

void Dialog::onAlgorithmStarted()
{
    timer.start();
}

void Dialog::onAlgorithmFinished()
{
    elapsedTime = timer.elapsed();
}

void Dialog::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(true);
    ui->groupBox->setDisabled(true);
    ui->groupBox_2->setDisabled(true);
    ui->spinBox->setDisabled(true);
    ui->spinBox_2->setDisabled(true);
    IAlgorithm * algorithm;
    Route * resultRoute;
    QString textToList;
    //QThread algorithmThread;

    if(ui->antsColony->isChecked())
    {
        aType = ANTS_COLONY;
    }

    if(ui->bruteForce->isChecked())
    {
        aType = BRUTE_FORCE;
    }

    if(ui->genetic->isChecked())
    {
        aType = GENETIC;
        algorithm = new GeneticAlgorithm();
    }

    if(ui->simulatedAnnealing->isChecked())
    {
        aType = SIMULATED_ANNEALING;
        algorithm = new AnnealingAlgorithm;
    }

    if(ui->withoutTime->isChecked())
    {
        cType = Route::WITHOUT_TIME;
    }

    if(ui->withTime->isChecked())
    {
        cType = Route::WITH_TIME;
    }

    connect(algorithm,SIGNAL(started()),this,SLOT(onAlgorithmStarted()));
    connect(algorithm,SIGNAL(finished()),this,SLOT(onAlgorithmFinished()));

    double totalTime = 0;
    double totalCost = 0;

    for(int x = 0; x < ui->spinBox_2->value(); x++)
    {
        textToList.append("Cost calculation type: ");
        textToList.append(enumCostTypeToString(cType));
        stringToList(textToList);
        textToList.clear();

        algorithm->setCostType(cType);


        switch(aType)
        {
        case ANTS_COLONY:
            break;

        case BRUTE_FORCE:
            break;

        case GENETIC:
            resultRoute = algorithm->calculateRoute(adjacencyMatrix,ui->spinBox->value());

            break;

        case SIMULATED_ANNEALING:
            //InitializeAnnealingParameters();

            resultRoute = algorithm->calculateRoute(adjacencyMatrix,ui->spinBox->value());
           break;
        }

        textToList.append(resultRoute->printRouteToString());
        textToList.append("Cost: ");
        textToList.append(QString::number(resultRoute->getCost(cType)));
        totalCost = totalCost + static_cast<double>(resultRoute->getCost(cType));
        stringToList(textToList);
        textToList.clear();


        textToList.append("Algorithm: \"");
        textToList.append(enumAlgorithmTypeToString(aType));
        textToList.append("\" finished. Time: ");
        textToList.append(QString::number(elapsedTime));
        totalTime = totalTime + static_cast<double>(elapsedTime);
        textToList.append("ms.");
        stringToList(textToList);
        textToList.clear();
        delete(resultRoute);
    }


    //<< "Algorithm: " << aType << " finished. Time: " << elapsedTime << "ms.";
    //algorithmThread.exit();
    ui->pushButton->setEnabled(true);
    ui->groupBox->setEnabled(true);
    ui->groupBox_2->setEnabled(true);
    ui->spinBox->setEnabled(true);
    ui->spinBox_2->setEnabled(true);
    ui->averageCost->setText(QString::number(totalCost/static_cast<double>(ui->spinBox_2->value())));
    ui->averageTime->setText(QString::number(totalTime/static_cast<double>(ui->spinBox_2->value())));

    algorithm->deleteLater();

}
void Dialog::initializeAnnealingParameters()
{
     AnnealingAlgorithm::AnnealingParameter  = ui->AnnealingSpinBox->value();
     AnnealingAlgorithm::Temperature  = ui->TemperatureSpinBox->value();

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
            if(adjacencyMatrix != NULL)
            {
                delete(adjacencyMatrix);
            }
            else
            {
                adjacencyMatrix = loader.getAdjacencyMatrixFromFile(&file);
            }
            if(adjacencyMatrix != NULL)
            {
                ui->spinBox->setMinimum(0);
                ui->spinBox->setMaximum(adjacencyMatrix->getSize()-1);
                ui->pushButton->setEnabled(true);
            }
            else
            {
                ui->pushButton->setEnabled(false);
            }
        }
    }
}

void Dialog::on_clearButton_clicked()
{
    ui->listWidget->clear();
}

QString Dialog::enumAlgorithmTypeToString(algorithmType type)
{
    switch(type)
    {
    case ANTS_COLONY:
        return QString("Ant colony");
        break;

    case BRUTE_FORCE:
        return QString("Brute force");
        break;

    case GENETIC:
        return QString("Genetic");
        break;

    case SIMULATED_ANNEALING:
        return QString("Simulated annealing");
        break;
    }
}

QString Dialog::enumCostTypeToString(Route::costType type)
{
    switch(type)
    {
    case Route::WITH_TIME:
        return QString("With time slots");
        break;

    case Route::WITHOUT_TIME:
        return QString("Without time slots");
        break;
    }

}

