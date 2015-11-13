#include "dialog.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    qDebug() << "***Test code KW";

    return a.exec();
}
