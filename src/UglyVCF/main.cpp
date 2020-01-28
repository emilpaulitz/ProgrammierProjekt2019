#include "mainwindow.h"
#include "vcftable.h"

#include <QApplication>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.resize(400,400);
    return a.exec();
}
