/********************************************************************************
** Form generated from reading UI file 'filterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERDIALOG_H
#define UI_FILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FilterDialog
{
public:
    QDialogButtonBox *buttonBox;
    QFrame *frame_2;
    QComboBox *comboBox;
    QLabel *label_2;
    QFrame *frame;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label;
    QPushButton *resetButton;
    QCheckBox *hideBox;
    QPushButton *severityButton;

    void setupUi(QDialog *FilterDialog)
    {
        if (FilterDialog->objectName().isEmpty())
            FilterDialog->setObjectName(QString::fromUtf8("FilterDialog"));
        FilterDialog->resize(441, 392);
        FilterDialog->setStyleSheet(QString::fromUtf8(""));
        buttonBox = new QDialogButtonBox(FilterDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(160, 340, 231, 31));
        buttonBox->setStyleSheet(QString::fromUtf8("background-color: rgb(225, 225, 225);"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        frame_2 = new QFrame(FilterDialog);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(50, 140, 341, 81));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(225, 225, 225);\n"
"border-color: rgb(255, 0, 0);"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        comboBox = new QComboBox(frame_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 40, 321, 31));
        comboBox->setInsertPolicy(QComboBox::InsertAtBottom);
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 321, 20));
        frame = new QFrame(FilterDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(50, 40, 341, 81));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(225,225,225);"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        frame->setMidLineWidth(0);
        doubleSpinBox = new QDoubleSpinBox(frame);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(10, 40, 321, 31));
        doubleSpinBox->setDecimals(5);
        doubleSpinBox->setMaximum(1.000000000000000);
        doubleSpinBox->setSingleStep(0.010000000000000);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 321, 21));
        resetButton = new QPushButton(FilterDialog);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(50, 340, 101, 31));
        resetButton->setToolTipDuration(-1);
        hideBox = new QCheckBox(FilterDialog);
        hideBox->setObjectName(QString::fromUtf8("hideBox"));
        hideBox->setGeometry(QRect(50, 290, 341, 20));
        hideBox->setChecked(false);
        severityButton = new QPushButton(FilterDialog);
        severityButton->setObjectName(QString::fromUtf8("severityButton"));
        severityButton->setGeometry(QRect(50, 240, 171, 31));

        retranslateUi(FilterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FilterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FilterDialog, SLOT(reject()));
        QObject::connect(resetButton, SIGNAL(clicked()), FilterDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(FilterDialog);
    } // setupUi

    void retranslateUi(QDialog *FilterDialog)
    {
        FilterDialog->setWindowTitle(QApplication::translate("FilterDialog", "Dialog", nullptr));
        label_2->setText(QApplication::translate("FilterDialog", "Select Region:", nullptr));
        label->setText(QApplication::translate("FilterDialog", "Enter frequency threshold:", nullptr));
#ifndef QT_NO_TOOLTIP
        resetButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        resetButton->setText(QApplication::translate("FilterDialog", "Reset all", nullptr));
        hideBox->setText(QApplication::translate("FilterDialog", "Hide entries with unknown frequencies", nullptr));
        severityButton->setText(QApplication::translate("FilterDialog", "Filter by Impact >>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterDialog: public Ui_FilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERDIALOG_H
