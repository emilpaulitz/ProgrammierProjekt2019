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
#include <QStringList>

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
    connect(annotationService, &AnnotationService::queueFinished, this, &MainWindow::updateAnnoProgress);

    // set up annotationService, connecting internal signals and slots
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

    //creates table heading
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

/**
 * @brief MainWindow::on_actionVCF_file_triggered opens dialog window to select the vcf file and print it and tells user
 * if invalid chromosome number notations were found
 */
void MainWindow::on_actionVCF_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Vcf file", QDir::homePath(), tr("VCF files (*.vcf)"));
    if (fileName != "") parseVCF(fileName);
    // if an invalid chr1, chr2 ... notation were found, but they will not be printed out
    if(VCFtable::invalidChrNum == true){
        QMessageBox::information(this,tr("Warning"),tr("invalid chromosome number were found"));
}
}

/**
 * @brief MainWindow::on_actionset_pipeline_triggered opens file explorer dialog to set the path to the pipeline
 */
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

/**
 * @brief MainWindow::on_actionset_reference_genome_triggered opens file explorer dialog to set the path
 * to the reference genome
 */
void MainWindow::on_actionset_reference_genome_triggered()
{
    refGenPath = QFileDialog::getOpenFileName(this, "set reference genome", QDir::homePath(),
                                              tr("FastA files (*.fasta *.fa)"));
}

// TODO make user able to abort -> button
// NOTE QFiledialog::getOpenFileName works, but results in error message (seems to be an Unix-Qt issue)
/**
 * @brief MainWindow::on_actionFastQ_file_triggered Open file explorer dialog to let the user enter necessary inputs
 * and execute the pipeline
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
        read1 = QFileDialog::getOpenFileName(this, "open READ 1 FastQ file", QDir::homePath(),
                                             tr("FASTQ files (*.fastq *.fq *.fastq.gz *fq.gz)"));
        read2 = QFileDialog::getOpenFileName(this, "open READ 2 FastQ file", QDir::homePath(),
                                             tr("FASTQ files (*.fastq *.fq *.fastq.gz *fq.gz)"));
        // check if everything is set
        if (read1 == "" || read2 == "")
        {
            QMessageBox::warning(this, tr("Error"), tr("need forward and backward READS"));
        }
        else
        {
            // make process and formulate command
            QMessageBox::information(this, tr("Caution"), tr("Starting pipeline, this may take a while!"));

            int lastSlash = pipelinePath.lastIndexOf('/');
            this->pipelineWD = pipelinePath.left(lastSlash);

            QStringList args;
            args << read1 << read2 << refGenPath;

            // make process and fill parameters 'program' and 'arguments'
            this->process = new QProcess(this);
            this->process->setWorkingDirectory(pipelineWD);
            this->process->setProgram(pipelinePath);
            this->process->setArguments(args);

            // connect to finshing handler to be independent from duration of pipeline
            connect(this->process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                    this, &MainWindow::handlePipelineFinished);
            // connect to show stdout on statusbar
            connect(this->process, &QProcess::readyReadStandardOutput, this, &MainWindow::handle_pipeline_working);

            this->process->start();
        }
    }
}

/**
 * @brief MainWindow::handlePipelineFinished depending on the outcome of the pipeline execution:
 * opens the created VCF file or shows a warning. TRIGGERED by: this->process's "finished" signal
 * @param status ExitStatus of the Process
 */
void MainWindow::handlePipelineFinished(int, QProcess::ExitStatus status){
    qDebug() << __FUNCTION__;
    // automatically open new vcf
    if (status==EXIT_SUCCESS && this->process->workingDirectory() != "")
    {
            parseVCF(this->process->workingDirectory() + "/cache/final.vcf");
    }
    else if(status==EXIT_FAILURE)
    {
        QMessageBox::warning(this, tr("Error"), tr("Pipeline terminated with an error!"));
    }
    this->process->deleteLater();
}

/**
 * @brief MainWindow::handle_pipeline_working shows the pipeline outputs to the user.
 * TRIGGERED when this->process has new output
 */
void MainWindow::handle_pipeline_working()
{
    qDebug() << __FUNCTION__;
    this->ui->statusbar->showMessage(this->process->readAllStandardOutput());
}

/**
 * @brief MainWindow::on_actionpull_all_annotations_triggered starts the process of pulling all annotations if
 * an VCF file is open
 */
void MainWindow::on_actionpull_all_annotations_triggered()
{
    if (this->tableObj.getLines().isEmpty()){
        QMessageBox::information(this, tr("Error"),
                                 tr("Please open an VCF file to pull its annotations!"));
    } else {
        this->showAnnoProgress();
        annotationService->pullAnnotations(tableObj);
    }
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
    filter->windowOpened();
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
            // If there is no annotation, show line (in case of new file) and continue
            if(line.getAnno().isEmpty()){
                missingAnno = true;
                ui->tableWidget->showRow(line.getIndex());
                continue;
            }

            // handle case of unknown frequencies
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
 * @brief MainWindow::updateAnnoWidget Shows either waiting text or annotation of this->cellClicked (!), the parameter
 * specifies row of which the annotation got updated.
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
    QBrush design;

    switch (mostSevereImpact) {
        case FilterDialog::HIGH:
            design = QBrush(Qt::red, Qt::SolidPattern);
            break;
        case FilterDialog::MODERATE:
            design = QBrush(Qt::yellow, Qt::Dense4Pattern);
            break;
        case FilterDialog::LOW:
            design = QBrush(Qt::green, Qt::Dense4Pattern);
            break;
        case FilterDialog::MODIFER:
            design = QBrush(Qt::cyan, Qt::Dense4Pattern);
            break;
        default:
            design = QBrush(Qt::transparent, Qt::Dense4Pattern);
            break;
    }

    // color entire row
    for (int col = 0; col < tableObj.getLine(index).getSize(); col++)
    {
        ui->tableWidget->item(index, col)->setBackground(design);
    }
}

/**
 * @brief MainWindow::on_actionhide_annotations_triggered hide annotations and legend
 */
void MainWindow::on_actionhide_annotations_triggered()
{
    ui->annoWidget->hide();
    ui->explanation->hide();
}

/**
 * @brief MainWindow::pop_no_connection shows a warning that there is no internet connection
 */
void MainWindow::pop_no_connection()
{
    QMessageBox::warning(this, tr("No Connectioin"), tr("No connection available, check your internet settings!"));
}

/**
 * @brief MainWindow::on_actionDelete_all_annotations_triggered deletes all the entries in the data base
 */
void MainWindow::on_actionDelete_all_annotations_triggered(){
   databank::purgeDB();
}

/**
 * @brief MainWindow::on_actionDelete_current_annotation_triggered deletes the entry in the data base corresponding
 * to the row clicked
 */
void MainWindow::on_actionDelete_current_annotation_triggered()
{
    if (0 <= cellClicked && cellClicked < tableObj.getNumLines()){
        databank::deleterow(tableObj.getLine(cellClicked).getHgvsNotation());
    } else {
        QMessageBox::warning(this, tr("Delete current Row"), tr("Please select a line!"));
    }
}

