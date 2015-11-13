#include "dialog.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    qDebug() << "***Test code KW";

    int i =10;
    QString name = "siema tu Wojtek";
    QString name2 = "TROLOLO";
    return a.exec();
}
