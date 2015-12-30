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

void Dialog::on_pushButton_clicked()
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::AnyFile);
    //fileDialog.setNameFilter(tr("Matrix files (*.mtx)"));
    fileDialog.show();

    QStringList fileNames;
    if (fileDialog.exec())
    {
        fileNames = fileDialog.selectedFiles();
        if(!fileNames.isEmpty())
        {
            QFile  file(fileNames.at(0));
            if(file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                unsigned int size = ui->spinBox->value();
                unsigned int maxDistance = 50;
                QJsonDocument matrixDocument;
                QJsonObject finalObject;
                QJsonArray matrixArray;
                QJsonArray timeSlotsArray;

                finalObject["size"] = static_cast<int>(size);

                for(int i = 0; i < size; i++)
                {
                    for(int j = 0; j < size; j++)
                    {
                        if(i != j)
                        {
                            QJsonObject objectOfMatrix;
                            int distance = qrand() % maxDistance + 1;
                            int time = 0;
                            do
                            {
                                time = distance + (qrand() % distance/5);
                                time = time - (qrand() % distance/5);
                            }
                            while(time <= 0);


                            objectOfMatrix["sourceNode"] = i;
                            objectOfMatrix["destinationNode"] = j;
                            objectOfMatrix["distance"] = static_cast<int>(distance);
                            objectOfMatrix["time"] = time;
                            matrixArray.append(objectOfMatrix);
                            //objectOfMatrix[]
                        }
                    }
                }
                finalObject["matrix"] = matrixArray;

                for(int m = 0; m < size; m++)
                {
                    QJsonObject timeSlotObject;
                    timeSlotObject["nodeNumber"] = m;
                    timeSlotObject["startTime"] = 0;
                    timeSlotObject["endTime"] = 0;
                    timeSlotsArray.append(timeSlotObject);

                }
                finalObject["timeSlots"] = timeSlotsArray;

                matrixDocument.setObject(finalObject);
                //qDebug() << matrixDocument.toJson();
                file.write(matrixDocument.toJson());
            }
        }


    }
}
