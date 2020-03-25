#include "mainwindow.h"
#include "vcftable.h"
#include "databank.h"


#include <QApplication>

#include <string>
#include <iostream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    databank::connect();
    databank::createTable();

    w.centralWidget();
    w.showMaximized();
    w.setWindowIcon(QIcon(":/icons/rsc/uglyVCF_icon6.ico"));
    //w.resize(800,800);
    //w.showFullScreen();
    return a.exec();

}
