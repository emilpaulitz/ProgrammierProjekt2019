#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vcftable.h"
#include "vcfline.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <string>
#include <QTableWidget>
#include <QProcess>

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
    // create table object
    this->tableObj = VCFtable();
    tableObj.parse(fileName);
    int NUM_LINES = tableObj.getLines().size();
    int NUM_COLS = tableObj.getLine(0).getSize();
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

void MainWindow::on_actionset_pipeline_triggered()
{
    // open path to pipeline.sh
    pipelinePath = QFileDialog::getOpenFileName(this, "set pipeline script", QDir::homePath(), tr("shell scrpts (*sh)"));
    // indicate, that pipelinePath is set -> change icon
    if (pipelinePath != "")
    {
        ui->actionset_pipeline->setIcon(QIcon(":/icons/rsc/pipelineSet2_icon.png"));
    }
}

void MainWindow::on_actionset_reference_genome_triggered()
{
    refGenPath = QFileDialog::getOpenFileName(this, "set reference genome", QDir::homePath(), tr("FastA files (*.fasta, *.fa)"));
}

void MainWindow::on_actionFastQ_file_triggered()
{
    // check if pipelinePath is set
    if (pipelinePath == "")
    {
        QMessageBox::warning(this, tr("Error"), tr("NGS pipeline not set: Settings->set pipeline"));
    }
    // check if reference genome is set
    else if (refGenPath == "")
    {
        QMessageBox::warning(this, tr("Error"), tr("reference genome not set: Settings->set reference genome"));
    }
    else
    {
        //open FastQ files (read 1, read 2)
        QString read1 = "", read2 = "";
        read1 = QFileDialog::getOpenFileName(this, "open READ 1 FastQ file", QDir::homePath()); //tr("FastQ files (*.fastq, *.fq)")
        read2 = QFileDialog::getOpenFileName(this, "open READ 2 FastQ file", QDir::homePath());
        // check if everything is set
        if (read1 == "" || read2 == "")
        {
            QMessageBox::warning(this, tr("Error"), tr("need forward and backward READS"));
        }
        // start pipeline
        QMessageBox::information(this, tr("Caution"), tr("starting pipeline, this may take a while"));
        QString command = pipelinePath + " " + read1 + " " + read2 + " " + refGenPath;
        QProcess::execute(command);
        if (QProcess::ExitStatus()==EXIT_SUCCESS){
            on_actionVCF_file_triggered();
        }
        if(QProcess::ExitStatus()==EXIT_FAILURE){
            QMessageBox::warning(this, tr("Error"), tr("pipeline could not be executed"));
        }

        // TODO: find and display vcf result
    }
}

void MainWindow::on_actionpull_annotations_triggered()
{
    QMessageBox::information(this, tr("Caution"), tr("this is a test"));
}

void MainWindow::on_actionpull_all_annotations_triggered()
{
    int i = 0;
    for (VCFline line : this->tableObj.getLines()) {
        ++i;
    }
    QMessageBox::information(this, tr("Caution"), tr("Number of lines: " + i)); //.append(std::to_string(i))));
}

