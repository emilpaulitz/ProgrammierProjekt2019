#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vcftable.h"
#include "vcfline.h"
#include "transcriptcons.h"
#include "annotationservice.h"
#include <annotationservice.cpp>
#include <transcriptcons.cpp>

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
}

MainWindow::~MainWindow()
{
    delete ui;
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
    VCFline currLine;
    for (int i = 0; i < NUM_LINES; i++)
    {
        currLine = tableObj.getLine(i);
        QTableWidgetItem *newItem;
        // fill line
        currLine.setIndex(i);
        for (int k = 0; k < NUM_COLS; k++)
        {
            newItem = new QTableWidgetItem(currLine.getDataField(k));
            ui->tableWidget->setItem(i, k, newItem);
        }
    }
    ui->tableWidget->show();
}

/**
 * @brief MainWindow::makeVEPrequest make a request to VEP with given line, save annotation in line obj
 * @param line the VCFline, you want the mutation to be checked
 */
void MainWindow::makeVEPrequest(VCFline& line)
{
    // TODO check connectivity, prevent programm from crashing
    // get annotations
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QString URL = "http://grch37.rest.ensembl.org/vep/homo_sapiens/hgvs/";
    // hgvs notation: CHR :g. POS REF>ALT (no spaces)
    QString endpoint = line.getChrNum() + ":g." + line.getPos() + line.getRef() + ">" + line.getAlt() + "?"; //"NG_0000" + .10
    QString optionJson = "content-type=application/json";
    QNetworkRequest *request = new QNetworkRequest(QUrl(URL + endpoint + optionJson));
    // check connectivity
    if (QNetworkAccessManager::NetworkAccessibility networkAccess = manager->networkAccessible())
    {
        // make request
        manager->get(*request);
        connect(manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply *reply)
        {
            QByteArray data = reply->readAll();

            //unwichtig
            QString str = QString::fromLatin1(data);


            QJsonDocument jsmin = QJsonDocument::fromJson(data);
            QJsonArray jarray = jsmin.array();
            QString key = "transcript_consequences";
            QJsonObject jobject = jarray[0].toObject();
            QJsonDocument secjson = QJsonDocument::fromJson(data);
            QString strJson(secjson.toJson(QJsonDocument::Indented));
            //qWarning() << strJson;
            //qWarning() << "Jarray is :" << jobject.value(key).toString();


            //unwichtig


            QList<transcriptcons> toshow = parse_totranscrictionlist(jsmin);
           // qWarning() << printtranscons(toshow);

            // show annotations
            line.setAnno(printtranscons(toshow));
           // qDebug() << "makeVEPrequest: " + str;
        });
    } else {
        QMessageBox::information(this, tr("no connection to network"),
                                 tr("unable to connect to network, see internet settings."));
    }
}

void MainWindow::on_actionVCF_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Vcf file", QDir::homePath(), tr("VCF files (*.vcf)"));
    if (fileName != "") parseVCF(fileName);
}

void MainWindow::on_actionset_pipeline_triggered()
{
    // open path to pipeline.sh
    pipelinePath = QFileDialog::getOpenFileName(this, "set pipeline script", QDir::homePath(), tr("shell scripts (*sh)"));
    // indicate, that pipelinePath is set -> change icon
    if (pipelinePath != "")
    {
        ui->actionset_pipeline->setIcon(QIcon(":/icons/rsc/pipelineSet2_icon.png"));
    }
}

void MainWindow::on_actionset_reference_genome_triggered()
{
    refGenPath = QFileDialog::getOpenFileName(this, "set reference genome", QDir::homePath(), tr("FastA files (*.fasta *.fa)"));
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
            QMessageBox::information(this, tr("Caution"), tr("starting pipeline, this may take a while"));
            QString command = pipelinePath + " " + read1 + " " + read2 + " " + refGenPath;
            int lastSlash = pipelinePath.lastIndexOf('/');
            QString wdPipeline = pipelinePath;
            wdPipeline.chop(wdPipeline.length() - lastSlash);
            QProcess *process = new QProcess(this);
            process->setWorkingDirectory(wdPipeline);

            // start pipeline
            QProcess::execute(command);
            if (QProcess::ExitStatus()==EXIT_SUCCESS){
                //automatically open new vcf
                parseVCF(wdPipeline + "/cache/final.vcf");
            }
            if(QProcess::ExitStatus()==EXIT_FAILURE){
                QMessageBox::warning(this, tr("Error"), tr("pipeline could not be executed"));
            }
        }
    }
}

//TODO: what do we need this method for?
void MainWindow::on_actionpull_annotations_triggered()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://grch37.rest.ensembl.org/lookup/symbol/homo_sapiens/BRCA2?")));
    connect(manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply *reply)
    {
        QByteArray data = reply->readAll();
        QString str = QString::fromLatin1(data);
        ui->annoWidget->setText(str);
        ui->annoWidget->show();
    });
}

//TODO: what do we need this method for?
void MainWindow::on_actionpull_all_annotations_triggered()
{
    int i = 0;
    for (VCFline line : this->tableObj.getLines()) {
        // TODO: pull annotation for lines
        ++i;
    }
    std::string msg = "Number of lines: " + std::to_string(i);
    QMessageBox::information(this, tr("Caution"), tr(&msg[0]));
}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    // method, when makeVEPrequest works
    // TODO: find a different way to access clicked lineObj (sorting may mess up the order, so row is not equal to i in getLine(i) )

    VCFline &line = this->tableObj.getLine(row);
    makeVEPrequest(line);
    qDebug() << "cell_clicked: " << line.getAnno();
    ui->annoWidget->setText(line.getAnno());
    ui->annoWidget->show();
/*
    // get annotations
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QString URL = "http://grch37.rest.ensembl.org/vep/homo_sapiens/hgvs/";
    VCFline &line = this->tableObj.getLine(row);
    // hgvs notation: NG_0000 CHR .10:g.POS REF>ALT (no spaces)
    QString endpoint = line.getChrNum() + ":g." + line.getPos() + line.getRef() + ">" + line.getAlt() + "?"; //"NG_0000" + .10
    QString headerParameter = "content-type=application/json";
    QNetworkRequest *request = new QNetworkRequest(QUrl(URL + endpoint));
    // check connectivity
    if (QNetworkAccessManager::NetworkAccessibility networkAccess = manager->networkAccessible())
    {
        // make request
        manager->get(*request);
        connect(manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply *reply)
        {
            QByteArray data = reply->readAll();
            QString str = QString::fromLatin1(data);
            // show annotations
            line.setAnno(str);
            ui->annoWidget->setText(line.getAnno());
            ui->annoWidget->show();
            qDebug() << "In Funktion: \n" + str;
        });
    } else {
        QMessageBox::information(this, tr("no connection to network"),
                                 tr("unable to connect to network, see internet settings."));
    }
*/
}

void MainWindow::on_actionhide_annotations_triggered()
{
    ui->annoWidget->hide();
}
