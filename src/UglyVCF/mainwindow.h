#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString pipelinePath;
    QString refGenPath;

private slots:

    void parseVCF(QString filename);

    void on_actionVCF_file_triggered();

    void on_actionset_pipeline_triggered();

    void on_actionFastQ_file_triggered();

    void on_actionset_reference_genome_triggered();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
