/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionVCF_file;
    QAction *actionset_pipeline;
    QAction *actionFastQ_file;
    QAction *actionset_reference_genome;
    QAction *actionSpace_for_Testing;
    QAction *actionpull_all_annotations;
    QAction *actionhide_annotations;
    QAction *actionFilter_by_Frequency;
    QAction *actionDelete_current_annotation;
    QAction *actionDelete_all_annotations;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *annoWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QProgressBar *progressPullingAll;
    QLabel *explanation;
    QMenuBar *menubar;
    QMenu *menuOpen;
    QMenu *menuSettings;
    QMenu *menuAnalysis;
    QMenu *menuData_base;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1013, 376);
        MainWindow->setAutoFillBackground(false);
        actionVCF_file = new QAction(MainWindow);
        actionVCF_file->setObjectName(QString::fromUtf8("actionVCF_file"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/rsc/vcf_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionVCF_file->setIcon(icon);
        actionset_pipeline = new QAction(MainWindow);
        actionset_pipeline->setObjectName(QString::fromUtf8("actionset_pipeline"));
        actionset_pipeline->setCheckable(false);
        actionset_pipeline->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/rsc/pipeline_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/icons/rsc/pipelineSet2_icon.png"), QSize(), QIcon::Normal, QIcon::On);
        actionset_pipeline->setIcon(icon1);
        actionFastQ_file = new QAction(MainWindow);
        actionFastQ_file->setObjectName(QString::fromUtf8("actionFastQ_file"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/rsc/fastq_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFastQ_file->setIcon(icon2);
        actionset_reference_genome = new QAction(MainWindow);
        actionset_reference_genome->setObjectName(QString::fromUtf8("actionset_reference_genome"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/rsc/dna2_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionset_reference_genome->setIcon(icon3);
        actionSpace_for_Testing = new QAction(MainWindow);
        actionSpace_for_Testing->setObjectName(QString::fromUtf8("actionSpace_for_Testing"));
        actionSpace_for_Testing->setIcon(icon);
        actionpull_all_annotations = new QAction(MainWindow);
        actionpull_all_annotations->setObjectName(QString::fromUtf8("actionpull_all_annotations"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/rsc/pull_all_annotations.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionpull_all_annotations->setIcon(icon4);
        actionhide_annotations = new QAction(MainWindow);
        actionhide_annotations->setObjectName(QString::fromUtf8("actionhide_annotations"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/rsc/icons8-bandit-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionhide_annotations->setIcon(icon5);
        actionFilter_by_Frequency = new QAction(MainWindow);
        actionFilter_by_Frequency->setObjectName(QString::fromUtf8("actionFilter_by_Frequency"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/rsc/Icons8-Ios7-Very-Basic-Filter-Filled.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionFilter_by_Frequency->setIcon(icon6);
        actionDelete_current_annotation = new QAction(MainWindow);
        actionDelete_current_annotation->setObjectName(QString::fromUtf8("actionDelete_current_annotation"));
        actionDelete_current_annotation->setCheckable(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/rsc/Tatice-Just-Bins-Bin-black-full.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_current_annotation->setIcon(icon7);
        actionDelete_all_annotations = new QAction(MainWindow);
        actionDelete_all_annotations->setObjectName(QString::fromUtf8("actionDelete_all_annotations"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/rsc/Tatice-Just-Bins-Bin-red-full.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_all_annotations->setIcon(icon8);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        annoWidget = new QTextEdit(centralwidget);
        annoWidget->setObjectName(QString::fromUtf8("annoWidget"));
        annoWidget->setReadOnly(true);

        gridLayout->addWidget(annoWidget, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout->addWidget(tableWidget);


        gridLayout->addLayout(horizontalLayout, 0, 0, 2, 1);

        progressPullingAll = new QProgressBar(centralwidget);
        progressPullingAll->setObjectName(QString::fromUtf8("progressPullingAll"));
        progressPullingAll->setValue(24);

        gridLayout->addWidget(progressPullingAll, 2, 0, 1, 2);

        explanation = new QLabel(centralwidget);
        explanation->setObjectName(QString::fromUtf8("explanation"));
        QFont font;
        font.setPointSize(6);
        font.setItalic(false);
        font.setKerning(true);
        explanation->setFont(font);
        explanation->setAutoFillBackground(false);

        gridLayout->addWidget(explanation, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1013, 30));
        menuOpen = new QMenu(menubar);
        menuOpen->setObjectName(QString::fromUtf8("menuOpen"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuAnalysis = new QMenu(menubar);
        menuAnalysis->setObjectName(QString::fromUtf8("menuAnalysis"));
        menuData_base = new QMenu(menubar);
        menuData_base->setObjectName(QString::fromUtf8("menuData_base"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOpen->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuAnalysis->menuAction());
        menubar->addAction(menuData_base->menuAction());
        menuOpen->addAction(actionFastQ_file);
        menuOpen->addAction(actionVCF_file);
        menuSettings->addAction(actionset_pipeline);
        menuSettings->addAction(actionset_reference_genome);
        menuAnalysis->addAction(actionSpace_for_Testing);
        menuAnalysis->addAction(actionpull_all_annotations);
        menuAnalysis->addAction(actionhide_annotations);
        menuAnalysis->addSeparator();
        menuAnalysis->addAction(actionFilter_by_Frequency);
        menuData_base->addAction(actionDelete_current_annotation);
        menuData_base->addAction(actionDelete_all_annotations);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionVCF_file->setText(QApplication::translate("MainWindow", "VCF file", nullptr));
        actionset_pipeline->setText(QApplication::translate("MainWindow", "set pipeline", nullptr));
        actionFastQ_file->setText(QApplication::translate("MainWindow", "FastQ file", nullptr));
        actionset_reference_genome->setText(QApplication::translate("MainWindow", "set reference genome", nullptr));
        actionSpace_for_Testing->setText(QApplication::translate("MainWindow", "Space for Testing", nullptr));
        actionpull_all_annotations->setText(QApplication::translate("MainWindow", "pull all annotations", nullptr));
#ifndef QT_NO_TOOLTIP
        actionpull_all_annotations->setToolTip(QApplication::translate("MainWindow", "pull annotations for every line in current VCF", nullptr));
#endif // QT_NO_TOOLTIP
        actionhide_annotations->setText(QApplication::translate("MainWindow", "hide annotations", nullptr));
        actionFilter_by_Frequency->setText(QApplication::translate("MainWindow", "Filter by Frequency...", nullptr));
        actionDelete_current_annotation->setText(QApplication::translate("MainWindow", "Delete current annotation", nullptr));
        actionDelete_all_annotations->setText(QApplication::translate("MainWindow", "Delete all annotations", nullptr));
        explanation->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:6pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:11pt;\">Impact of the most severe consequence: </span><span style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:600; color:#ff0000;\">HIGH </span><span style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:600; color:#ffff7f;\">MODERATE</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:600; color:#ffff00;\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:600; color:#00eb00;\">LOW</span><span style=\" font-family:'M"
                        "S Shell Dlg 2'; font-size:14pt; font-weight:600; color:#aaff00;\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-size:14pt; font-weight:600; color:#00efef;\">MODIFIER</span></p></body></html>", nullptr));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Open", nullptr));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        menuAnalysis->setTitle(QApplication::translate("MainWindow", "Analysis", nullptr));
        menuData_base->setTitle(QApplication::translate("MainWindow", "Data base", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
