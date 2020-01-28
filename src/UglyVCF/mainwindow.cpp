#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>

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
    QString fileName = QFileDialog::getOpenFileName(this, "Open Vcf file", QDir::homePath());
    QFile VCFfile(fileName);

    if (!VCFfile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"warning","file not open");

    }
    QTextStream in(&VCFfile);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    VCFfile.close();
}
