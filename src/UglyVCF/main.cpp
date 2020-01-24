#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.centralWidget();
    w.showNormal();
    //w.resize(800,800);
    //w.showFullScreen();
    return a.exec();
}
