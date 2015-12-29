#include "ialgorithm.h"

IAlgorithm::IAlgorithm(QObject *parent) : QObject(parent)
{

}

void IAlgorithm::setCostType(Route::costType type)
{
    costType = type;
}

