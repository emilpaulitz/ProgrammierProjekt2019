#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vcftable.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <string>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionVCF_file_triggered()
{
    std::string fileName = QFileDialog::getOpenFileName(this, "Open Vcf file", QDir::homePath()).toStdString();
    VCFtable tableObj = VCFtable();
    tableObj.parse(fileName);
    // create table
    //QTableWidget *tableWidget = new QTableWidget();
    int NUM_LINES = tableObj.getLines().size();
    int NUM_COLS = tableObj.getLine(0).getSize(); //TODO somehow returns wrong size
    ui->tableWidget->setRowCount(NUM_LINES);
    ui->tableWidget->setColumnCount(NUM_COLS);

    QStringList headerLabels = {"CHROM", "POS", "ID", "REF", "ALT", "QUAL", "FILTER", "INFO", "FORMAT", "SAMPLE", "ANNO"};
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);

    // fill table
    VCFline currLine;
    for (int i = 0; i < NUM_LINES; i++)
    {
        currLine = tableObj.getLine(i);
        QTableWidgetItem *newItem;
        for (int k = 0; k < NUM_COLS; k++)
        {
            newItem = new QTableWidgetItem(currLine.getDataField(k));
            ui->tableWidget->setItem(i, k, newItem);
        }
    }
    ui->tableWidget->show();
}
