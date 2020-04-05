#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filterdialog.h"
#include "ui_filterdialog.h"
#include "vcftable.h"
#include "vcfline.h"
#include "Transcriptcons.h"
#include "annotationservice.h"
#include "Frequencies.h"
#include "Annotation.h"
#include "databank.h"

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
    ui->explanation->hide();
    ui->annoWidget->hide();
    ui->progressPullingAll->hide();
    openAnnoService();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete annotationService;
}

/**
 * @brief MainWindow::openAnnoService creates a new annotationService object and connects all the
 *  necessary functions
 */
void MainWindow::openAnnoService(){
    annotationService = new AnnotationService();

    // connect signals from annotationservice with corresponding slots from this class
    connect(annotationService, &AnnotationService::no_connection, this, &MainWindow::pop_no_connection);
    connect(annotationService, &AnnotationService::annotation_set, this, &MainWindow::updateAnnoWidget);
    connect(annotationService, &AnnotationService::annotation_set, this, &MainWindow::update_row);
    connect(annotationService, &AnnotationService::annotation_set, this, &MainWindow::updateAnnoProgress);

    // set up annotationService connecting internal signals and slots
    annotationService->setupAnnoService(&tableObj);
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

    // create new annotationservice
    openAnnoService();
    ui->tableWidget->show();
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

// TODO: check if this works -> does not :(
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
    databank::purgeDB();
    /*std::string fdsa = "f sdaf ";
    fdsa + "fdsa f" + "fdsafds ";
    QString i = "fdsaf a";
    std::string msg = i.toStdString();
    QMessageBox::information(this, tr("Caution"), tr(&msg[0]));*/
}


void MainWindow::on_actionpull_all_annotations_triggered()
{
    this->showAnnoProgress();
    annotationService->pullAnnotations(tableObj);
}

/**
 * @brief MainWindow::on_tableWidget_cellClicked updates this->cellClicked, makes VEP request
 * if appropriate and updates annotation widget
 * @param row row the user clicked on
 */
void MainWindow::on_tableWidget_cellClicked(int row, int)
{
    qDebug() << "cell clicked: " << row;
    bool clickedAgain = (cellClicked == row);
    this->cellClicked = row;

    // Pull annotation  fresh after a double click
    // Enqueue job unless annotation already known nor every anno is being pulled anyway
    if ((tableObj.getLine(cellClicked).getAnno().isEmpty()
                && !annotationService->isPullingAllAnnos())||clickedAgain)  {
        annotationService->makeSingleRequest(row);
    }

    this->updateAnnoWidget(row);
    ui->annoWidget->show();
    ui->explanation->show();
}

/**
 * @brief MainWindow::on_tableWidget_cellDoubleClicked call cellClicked function with clickedAgain being true
 * @param row
 */
void MainWindow::on_tableWidget_cellDoubleClicked(int row, int)
{
    this->cellClicked = row;
    on_tableWidget_cellClicked(row,0);
}

void MainWindow::on_actionFilter_by_Frequency_triggered() {

    // check if an VCF file is opened
    if (this->tableObj.getLines().isEmpty()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Please open an VCF file and pull its annotations first!"));
        return;
    }

    // Open filter dialog

    if (!this->filter){
        this->filter = new FilterDialog(this);
    }
    filter->openWindow();
    if (filter->exec()){

        // retrieve values set by user
        bool filterByImpact = filter->isFilterByImpact();
        double maxFreq = filter->getFreq();
        FilterDialog::Region region = filter->getRegion();
        bool hideUnknown = filter->hideUnknown();
        if(!filter->isReset()){
           qDebug() << "Filter set: " << QString::number(maxFreq) << ", " << FilterDialog::regionToString(region);
        }

        // Iterate through the lines to determine which to hide
        bool missingAnno = false;
        double actualFreq = -1;
        for (VCFline line : this->tableObj.getLines()){
            // show line (in case of new file) and continue if there is no annotation
            if(line.getAnno().isEmpty()){
                missingAnno = true;
                ui->tableWidget->showRow(line.getIndex());
                continue;
            }

            // catch case of unknown frequencies
            if(line.getAnno().getFrequencies().isRegUnknown(region)) {
                if(hideUnknown || filter->getFreq(line.getAnno().getConsequenceClass()) == -1){
                    ui->tableWidget->hideRow(line.getIndex());
                } else {
                    ui->tableWidget->showRow(line.getIndex());
                }
                continue;
            }

            // handle case of filtering by impact
            if(filterByImpact) {
                maxFreq = filter->getFreq(line.getAnno().getConsequenceClass());
            }

            actualFreq = line.getAnno().getFrequencies().getFreq(region);

            // show or hide line depending on frequency
            if(actualFreq > maxFreq){
                ui->tableWidget->hideRow(line.getIndex());
            } else {
                ui->tableWidget->showRow(line.getIndex());
            }
        }

        // show a warning if not every line has an annotation
        if (missingAnno){
            QMessageBox::warning(this, tr("Missing Annotations"),
                                 tr("Filtering complete. Please note that there has been "
                                    "at least one line for which no annotation is given. "
                                    "Those lines are still shown."));
        }
    }
}

/**
 * @brief MainWindow::updateAnnoWidget Shows either waiting text or annotation of this->cellClicked (!), the parameter specifies row of which the annotation got updated.
 * TRIGGERED by: AnnotationService::annotation_set
 */
void MainWindow::updateAnnoWidget(int rowUpdated){
    qDebug() << __FUNCTION__ << "on line " << cellClicked;

    // Dont update if another cell than the one displayed was updated
    if (rowUpdated != cellClicked){
        return;
    }

    if (this->tableObj.getLine(cellClicked).getAnno().isEmpty()){

        ui->annoWidget->setText("The VEP Request has been enqueued, please stand by. "
                                "Doubleclick or click again to make this line a priority.");
    } else {

        ui->annoWidget->setText(this->tableObj.getLine(cellClicked).getAnno().print_Annotation());
    }
}

/**
 * @brief MainWindow::showAnnoProgress Open a progress bar showing progress of pulling all annotations
 */
void MainWindow::showAnnoProgress() {
    ui->progressPullingAll->setMinimum(0);
    ui->progressPullingAll->setMaximum(this->tableObj.getNumLines());
    ui->progressPullingAll->setValue(0);
    this->updateAnnoProgress();
    ui->progressPullingAll->show();
}

/**
 * @brief MainWindow::updateAnnoProgress Updates progress bar or hides it if all annotations are pulled
 * TRIGGERED by: AnnotationService::annotation_set
 */
void MainWindow::updateAnnoProgress() {
    if (this->annotationService->isPullingAllAnnos()) {
        ui->progressPullingAll->setValue(this->tableObj.getNumLines() - annotationService->getQueueSize());
    } else {
        ui->progressPullingAll->hide();
    }
}

/**
 * @brief MainWindow::update_row Updates Color of the row based on severity type.
 * TRIGGERED by: AnnotationService::annotation_set
 * @param index row to be updated
 */
void MainWindow::update_row(int index)
{
    FilterDialog::Impact mostSevereImpact = tableObj.getLine(index).getAnno().getConsequenceClass();
    QColor color;

    switch (mostSevereImpact) {
        case FilterDialog::HIGH:
            color = Qt::red;
            break;
        case FilterDialog::MODERATE:
            color = Qt::yellow;
            break;
        case FilterDialog::LOW:
            color = Qt::green;
            break;
        case FilterDialog::MODIFER:
            color = Qt::cyan;
            break;
        default:
            color = Qt::transparent;
            break;
    }

    // color entire row
    for (int col = 0; col < tableObj.getLine(index).getSize(); col++)
    {
        ui->tableWidget->item(index, col)->setBackground(QBrush(color, Qt::Dense4Pattern));
    }
}

// Hides anotationwidget
void MainWindow::on_actionhide_annotations_triggered()
{
    ui->annoWidget->hide();
    ui->explanation->hide();
}

// Shows a warning that there is no internet connection
void MainWindow::pop_no_connection()
{
    QMessageBox::warning(this, tr("No Connectioin"), tr("No connection available, check your internet settings!"));
}

void MainWindow::on_actionDelete_all_annotations_triggered(){
   databank::purgeDB();
}
