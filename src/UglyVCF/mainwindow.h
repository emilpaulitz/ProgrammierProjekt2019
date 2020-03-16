#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "annotationservice.h"
#include "vcftable.h"

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    void parseVCF(QString filename);

    Ui::MainWindow *ui;

    AnnotationService * annotationService;

    VCFtable tableObj;

    QProcess * process;

    QString pipelineWD;

    // gives the row of the cell currently clicked on
    int cellClicked;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getObjIndex(int qTableRow);

    int getWidgetRow(int ObjIndex); //TODO: implement

    //TODO: maybe make these private?
    QString pipelinePath;
    QString refGenPath;

private slots:

    void on_actionVCF_file_triggered();

    void on_actionset_pipeline_triggered();

    void on_actionFastQ_file_triggered();

    void handlePipelineFinished(int, QProcess::ExitStatus status);

    void on_actionset_reference_genome_triggered();

    void on_actionSpace_for_Testing_triggered();

    void on_actionpull_all_annotations_triggered();

    void on_tableWidget_cellClicked(int row, int);

    void on_actionhide_annotations_triggered();

    void pop_no_connection();

    void updateAnnoWidget(int rowUpdated);

    void showAnnoProgress();

    void updateAnnoProgress();

    void update_row(int index);

};
#endif // MAINWINDOW_H
