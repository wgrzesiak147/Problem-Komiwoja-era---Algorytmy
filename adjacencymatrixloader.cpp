#include "adjacencymatrixloader.h"

AdjacencyMatrixLoader::AdjacencyMatrixLoader(QObject *parent) : QObject(parent)
{

}

AdjacencyMatrix * AdjacencyMatrixLoader::getAdjacencyMatrixFromFile(QFile *source)
{
    if(source->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        unsigned int size = 0;
        QJsonParseError * error = new QJsonParseError;
        QJsonDocument matrixDocument = QJsonDocument::fromJson(source->readAll(),error);
        if(error->error == QJsonParseError::NoError)
        {
            QJsonObject matrixObject = matrixDocument.object();
            QJsonArray matrix = matrixObject["matrix"].toArray();
            QJsonArray timeSlots = matrixObject["timeSlots"].toArray();
            size = matrixObject["size"].toInt();
            AdjacencyMatrix * adjacencyMatrix = new AdjacencyMatrix(size);

            foreach(const QJsonValue & value, matrix)
            {
                QJsonObject JsObj = value.toObject();
                unsigned int sourceNode = JsObj["sourceNode"].toInt();
                unsigned int destinationNode = JsObj["destinationNode"].toInt();
                unsigned int distance = JsObj["distance"].toInt();
                unsigned int time = JsObj["time"].toInt();
                adjacencyMatrix->addEdge(sourceNode,destinationNode,distance,time);
            }

            foreach(const QJsonValue & value, timeSlots)
            {
                QJsonObject JsObj = value.toObject();
                unsigned int nodeNumber = JsObj["nodeNumber"].toInt();
                unsigned int startTime = JsObj["startTime"].toInt();
                unsigned int endTime = JsObj["endTime"].toInt();
                adjacencyMatrix->setTimeSlot(nodeNumber,startTime,endTime);
            }

            if(adjacencyMatrix->isFull())
            {
                emit errorString(QString::fromUtf8("Matrix loaded"));
                return adjacencyMatrix;
            }
            else
            {
                emit errorString("Adjacency matrix is not full");
                return NULL;
            }

        }
        else
        {
            QString string;
            string.append("JSON Error: ");
            string.append(error->errorString());
            emit errorString(string);
            return NULL;
        }

    }
    else
    {
        emit errorString("Could not open the file");
        return NULL;
    }

}

