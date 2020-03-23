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
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QTextEdit *annoWidget;
    QProgressBar *progressPullingAll;
    QMenuBar *menubar;
    QMenu *menuOpen;
    QMenu *menuSettings;
    QMenu *menuAnalysis;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(554, 303);
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
        actionFilter_by_Frequency = new QAction(MainWindow);
        actionFilter_by_Frequency->setObjectName(QString::fromUtf8("actionFilter_by_Frequency"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        horizontalLayout->addWidget(tableWidget);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        annoWidget = new QTextEdit(centralwidget);
        annoWidget->setObjectName(QString::fromUtf8("annoWidget"));
        annoWidget->setReadOnly(true);

        gridLayout->addWidget(annoWidget, 0, 1, 1, 1);

        progressPullingAll = new QProgressBar(centralwidget);
        progressPullingAll->setObjectName(QString::fromUtf8("progressPullingAll"));
        progressPullingAll->setValue(24);

        gridLayout->addWidget(progressPullingAll, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 554, 21));
        menuOpen = new QMenu(menubar);
        menuOpen->setObjectName(QString::fromUtf8("menuOpen"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuAnalysis = new QMenu(menubar);
        menuAnalysis->setObjectName(QString::fromUtf8("menuAnalysis"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOpen->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuAnalysis->menuAction());
        menuOpen->addAction(actionFastQ_file);
        menuOpen->addAction(actionVCF_file);
        menuSettings->addAction(actionset_pipeline);
        menuSettings->addAction(actionset_reference_genome);
        menuAnalysis->addAction(actionSpace_for_Testing);
        menuAnalysis->addAction(actionpull_all_annotations);
        menuAnalysis->addAction(actionhide_annotations);
        menuAnalysis->addSeparator();
        menuAnalysis->addAction(actionFilter_by_Frequency);

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
        menuOpen->setTitle(QApplication::translate("MainWindow", "Open", nullptr));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        menuAnalysis->setTitle(QApplication::translate("MainWindow", "Analysis", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
