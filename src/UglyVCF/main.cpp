#include "mainwindow.h"
#include "vcftable.h"

#include <QApplication>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.centralWidget();
    w.showNormal();
    w.setWindowIcon(QIcon(":/icons/rsc/uglyVCF_icon6.ico"));
    //w.resize(800,800);
    //w.showFullScreen();
    return a.exec();
}
