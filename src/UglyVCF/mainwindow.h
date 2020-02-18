#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "vcftable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void makeVEPrequest(VCFline& line);

    QString pipelinePath;
    QString refGenPath;

private slots:

    void on_actionVCF_file_triggered();

    void on_actionset_pipeline_triggered();

    void on_actionFastQ_file_triggered();

    void on_actionset_reference_genome_triggered();

    void on_actionpull_annotations_triggered();

    void on_actionpull_all_annotations_triggered();

    void on_tableWidget_cellClicked(int row, int column);

    void on_actionhide_annotations_triggered();

private:

    void parseVCF(QString filename);

    Ui::MainWindow *ui;

    VCFtable tableObj;

};
#endif // MAINWINDOW_H
