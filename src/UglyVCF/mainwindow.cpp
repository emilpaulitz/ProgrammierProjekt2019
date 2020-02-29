#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vcftable.h"
#include "vcfline.h"
#include "Transcriptcons.h"
#include "annotationservice.h"
#include "Frequencies.h"
#include "Annotation.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <string>
#include <QTableWidget>
#include <QProcess>

#include <QString>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>

#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->annoWidget->hide();
    ui->progressPullingAll->hide();
    annotationService = new AnnotationService(&tableObj);
    // connect signals from annotationservice with corresponding slots from this class
    connect(annotationService, &AnnotationService::no_connection, this, &MainWindow::pop_no_connection);
    connect(annotationService, &AnnotationService::annotation_set,this, &MainWindow::openAnnoWidget);
    connect(annotationService, &AnnotationService::annotation_set,this, &MainWindow::updateAnnoProgress);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete annotationService;
}

/**
 * @brief MainWindow::parseVCF parses a vcf file and shows it as table
 * @param filename path of vcf file
 */
void MainWindow::parseVCF(QString filename)
{
    // create table object
    this->tableObj = VCFtable();
    tableObj.parse(filename.toStdString());
    int NUM_LINES = tableObj.getLines().size();
    int NUM_COLS = tableObj.getLine(0).getSize();
    ui->tableWidget->setRowCount(NUM_LINES);
    ui->tableWidget->setColumnCount(NUM_COLS);

    QStringList headerLabels = {"CHROM", "POS", "ID", "REF", "ALT", "QUAL", "FILTER", "INFO", "FORMAT", "SAMPLE", "ANNO"};
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);

    // fill table
    VCFline *currLine;
    for (int i = 0; i < NUM_LINES; i++)
    {
        currLine = &tableObj.getLine(i);
        QTableWidgetItem *newItem;
        // fill line
        currLine->setIndex(i);
        for (int k = 0; k < NUM_COLS; k++)
        {
            newItem = new QTableWidgetItem(currLine->getDataField(k));
            ui->tableWidget->setItem(i, k, newItem);
            // set line index (from VCFtable) to cell (hidden, dataRole: UserRole)
            newItem->setData(Qt::UserRole, i);
        }
    }
    ui->tableWidget->show();
}

/**
 * @brief MainWindow::getObjIndex translates QTableWidget row to VCFtable index of VCFline visualised in certain row.
 * -> you can use tableObj.getLine(getObjIndex(qTableRow))
 * @param qTableRow the row of an QTableItem (cell)
 * @return the index of that row in tableObj
 */
int MainWindow::getObjIndex(int qTableRow)
{
    return ui->tableWidget->item(qTableRow, 0)->data(Qt::UserRole).toInt();
}


void MainWindow::on_actionVCF_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Vcf file", QDir::homePath(), tr("VCF files (*.vcf)"));
    if (fileName != "") parseVCF(fileName);
}

void MainWindow::on_actionset_pipeline_triggered()
{
    // user sets path to pipeline.sh
    pipelinePath = QFileDialog::getOpenFileName(this, "set pipeline script", QDir::homePath(), tr("shell scripts (*sh)"));
    // indicate that pipelinePath is set and change icon
    if (pipelinePath != "")
    {
        ui->actionset_pipeline->setIcon(QIcon(":/icons/rsc/pipelineSet2_icon.png"));
    }
}

void MainWindow::on_actionset_reference_genome_triggered()
{
    refGenPath = QFileDialog::getOpenFileName(this, "set reference genome", QDir::homePath(), tr("FastA files (*.fasta *.fa)"));
}

// TODO: check if this works
/**
 * @brief MainWindow::on_actionFastQ_file_triggered Read necessary inputs and execute the pipeline
 */
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
        read1 = QFileDialog::getOpenFileName(this, "open READ 1 FastQ file", QDir::homePath(), tr("FASTQ files (*.fastq *.fq *.fastq.gz *fq.gz)"));
        read2 = QFileDialog::getOpenFileName(this, "open READ 2 FastQ file", QDir::homePath(), tr("FASTQ files (*.fastq *.fq *.fastq.gz *fq.gz)"));
        // check if everything is set
        if (read1 == "" || read2 == "")
        {
            QMessageBox::warning(this, tr("Error"), tr("need forward and backward READS"));
        }
        else
        {
            // make process and formulate command
            QMessageBox::information(this, tr("Caution"), tr("Starting pipeline, this may take a while!"));
            QString command = pipelinePath + " " + read1 + " " + read2 + " " + refGenPath;
            int lastSlash = pipelinePath.lastIndexOf('/');
            pipelineWD = pipelinePath.left(lastSlash);
            this->process = new QProcess(this);
            this->process->setWorkingDirectory(pipelineWD);

            // connect to finshing handler to be independent from duration of pipeline
            connect(this->process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                    this, &MainWindow::handlePipelineFinished);
            this->process->execute(command);

            // So war es vorher, falls das oben nicht funktioniert:
            // QProcess::execute(command);
            /*if (QProcess::ExitStatus()==EXIT_SUCCESS){
                //automatically open new vcf
                parseVCF(wdPipeline + "/cache/final.vcf");
            }
            if(QProcess::ExitStatus()==EXIT_FAILURE){
                QMessageBox::warning(this, tr("Error"), tr("pipeline could not be executed"));
            }*/
        }
    }
}

/**
 * @brief MainWindow::handlePipelineFinished depending on the outcome of the pipeline execution:
 * opens the created VCF file or shows a warning. TRIGGERED by: this->process's "finished" signal
 * @param status ExitStatus of the Process
 */
void MainWindow::handlePipelineFinished(int, QProcess::ExitStatus status){
    // automatically open new vcf
    if (status==EXIT_SUCCESS){
        parseVCF(this->pipelineWD + "/cache/final.vcf");
    } else if(status==EXIT_FAILURE){
        QMessageBox::warning(this, tr("Error"), tr("Pipeline terminated with an error!"));
    }
}

// TODO delete
// Platz wo man automatische Tests implementieren kann
void MainWindow::on_actionSpace_for_Testing_triggered()
{
    QString i = "ABCDEFGHIJ";
    i.chop(1);
    std::string msg = i.toStdString();
    QMessageBox::information(this, tr("Caution"), tr(&msg[0]));
}


void MainWindow::on_actionpull_all_annotations_triggered()
{
    annotationService->pullAnnotations(tableObj);
    this->showAnnoProgress();
}

/**
 * @brief MainWindow::on_tableWidget_cellClicked updates this->cellClicked, makes VEP request
 * if appropriate and updates annotation widget
 * @param row row the user clicked on
 */
void MainWindow::on_tableWidget_cellClicked(int row, int)
{
    qDebug() << "cell_clicked: " << row;
    this->cellClicked = row;

    // TODO incorporate pulling from database instead from temporary memory!
    // Enqueue job unless every anno is being pulled anyway or annotation already known
    if (!annotationService->isPullingAllAnnos() && this->tableObj.getLine(cellClicked).getAnno().isEmpty()) {
        annotationService->makeSingleRequest(row);
    }

    this->openAnnoWidget();
}

/**
 * @brief MainWindow::openAnnoWidget Shows either waiting text or annotation of this->cellClicked
 * TRIGGERED by: AnnotationService::annotation_set
 */
void MainWindow::openAnnoWidget(){
    qDebug() << __FUNCTION__ << "on line " << cellClicked;

    if (this->tableObj.getLine(cellClicked).getAnno().isEmpty()){

        ui->annoWidget->setText("Making a VEP Request, please stand by...");
    } else {

        ui->annoWidget->setText(this->tableObj.getLine(cellClicked).getAnno());
    }

    ui->annoWidget->show();
}

/**
 * @brief MainWindow::showAnnoProgress Open a progress bar showing progress of pulling all annotations
 */
void MainWindow::showAnnoProgress() {
    ui->progressPullingAll->setMinimum(0);
    ui->progressPullingAll->setMaximum(this->tableObj.getNumLines());
    this->updateAnnoProgress();
    ui->progressPullingAll->show();
}

/**
 * @brief MainWindow::updateAnnoProgress Updates progress bar or hides it if all annotations are pulled
 * TRIGGERED by: AnnotationService::annotation_set
 */
void MainWindow::updateAnnoProgress() {
    if (this->annotationService->isPullingAllAnnos()) {
        if (annotationService->getQueue().isEmpty()) {
            ui->progressPullingAll->hide();
        } else {
        ui->progressPullingAll->setValue(this->tableObj.getNumLines() - annotationService->getQueueSize());
        }
    }
}

// Hides anotationwidget
void MainWindow::on_actionhide_annotations_triggered()
{
    ui->annoWidget->hide();
}

// Shows a warning that there is no internet connection
void MainWindow::pop_no_connection()
{
    QMessageBox::warning(this, tr("No Connectioin"), tr("No connection available, check your internet settings!"));
}
