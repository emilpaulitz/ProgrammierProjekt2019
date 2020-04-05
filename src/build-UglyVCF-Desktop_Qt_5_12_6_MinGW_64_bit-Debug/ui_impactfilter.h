/********************************************************************************
** Form generated from reading UI file 'impactfilter.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPACTFILTER_H
#define UI_IMPACTFILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_impactFilter
{
public:
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *HIGH_impact;
    QDoubleSpinBox *MODERATE_impact;
    QDoubleSpinBox *LOW_impact;
    QDoubleSpinBox *MODIFIER_impact;
    QLabel *label_region;
    QLabel *region_label;
    QFrame *line;
    QPushButton *resetButton;
    QDoubleSpinBox *unknown_impact;
    QCheckBox *ShowUNKNOWN;
    QCheckBox *ShowMODIFIER;
    QCheckBox *ShowLOW;
    QCheckBox *ShowMODERATE;
    QCheckBox *ShowHIGH;

    void setupUi(QDialog *impactFilter)
    {
        if (impactFilter->objectName().isEmpty())
            impactFilter->setObjectName(QString::fromUtf8("impactFilter"));
        impactFilter->resize(809, 416);
        buttonBox = new QDialogButtonBox(impactFilter);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(290, 370, 491, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        HIGH_impact = new QDoubleSpinBox(impactFilter);
        HIGH_impact->setObjectName(QString::fromUtf8("HIGH_impact"));
        HIGH_impact->setGeometry(QRect(630, 90, 151, 31));
        HIGH_impact->setDecimals(5);
        HIGH_impact->setMaximum(1.000000000000000);
        HIGH_impact->setSingleStep(0.010000000000000);
        MODERATE_impact = new QDoubleSpinBox(impactFilter);
        MODERATE_impact->setObjectName(QString::fromUtf8("MODERATE_impact"));
        MODERATE_impact->setGeometry(QRect(630, 140, 151, 31));
        MODERATE_impact->setDecimals(5);
        MODERATE_impact->setMaximum(1.000000000000000);
        MODERATE_impact->setSingleStep(0.010000000000000);
        LOW_impact = new QDoubleSpinBox(impactFilter);
        LOW_impact->setObjectName(QString::fromUtf8("LOW_impact"));
        LOW_impact->setGeometry(QRect(630, 190, 151, 31));
        LOW_impact->setDecimals(5);
        LOW_impact->setMaximum(1.000000000000000);
        LOW_impact->setSingleStep(0.010000000000000);
        MODIFIER_impact = new QDoubleSpinBox(impactFilter);
        MODIFIER_impact->setObjectName(QString::fromUtf8("MODIFIER_impact"));
        MODIFIER_impact->setGeometry(QRect(630, 240, 151, 31));
        MODIFIER_impact->setDecimals(5);
        MODIFIER_impact->setMaximum(1.000000000000000);
        MODIFIER_impact->setSingleStep(0.010000000000000);
        label_region = new QLabel(impactFilter);
        label_region->setObjectName(QString::fromUtf8("label_region"));
        label_region->setGeometry(QRect(628, 20, 151, 31));
        QFont font;
        font.setPointSize(10);
        label_region->setFont(font);
        region_label = new QLabel(impactFilter);
        region_label->setObjectName(QString::fromUtf8("region_label"));
        region_label->setGeometry(QRect(30, 20, 271, 31));
        region_label->setFont(font);
        line = new QFrame(impactFilter);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 50, 771, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        resetButton = new QPushButton(impactFilter);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(30, 370, 251, 31));
        resetButton->setToolTipDuration(-1);
        unknown_impact = new QDoubleSpinBox(impactFilter);
        unknown_impact->setObjectName(QString::fromUtf8("unknown_impact"));
        unknown_impact->setGeometry(QRect(630, 290, 151, 31));
        unknown_impact->setDecimals(5);
        unknown_impact->setMinimum(0.000000000000000);
        unknown_impact->setMaximum(1.000000000000000);
        unknown_impact->setSingleStep(0.010000000000000);
        ShowUNKNOWN = new QCheckBox(impactFilter);
        ShowUNKNOWN->setObjectName(QString::fromUtf8("ShowUNKNOWN"));
        ShowUNKNOWN->setGeometry(QRect(30, 290, 591, 31));
        ShowUNKNOWN->setChecked(true);
        ShowMODIFIER = new QCheckBox(impactFilter);
        ShowMODIFIER->setObjectName(QString::fromUtf8("ShowMODIFIER"));
        ShowMODIFIER->setGeometry(QRect(30, 240, 591, 31));
        ShowMODIFIER->setChecked(true);
        ShowLOW = new QCheckBox(impactFilter);
        ShowLOW->setObjectName(QString::fromUtf8("ShowLOW"));
        ShowLOW->setGeometry(QRect(30, 190, 591, 31));
        ShowLOW->setChecked(true);
        ShowMODERATE = new QCheckBox(impactFilter);
        ShowMODERATE->setObjectName(QString::fromUtf8("ShowMODERATE"));
        ShowMODERATE->setGeometry(QRect(30, 140, 591, 31));
        ShowMODERATE->setChecked(true);
        ShowHIGH = new QCheckBox(impactFilter);
        ShowHIGH->setObjectName(QString::fromUtf8("ShowHIGH"));
        ShowHIGH->setGeometry(QRect(30, 90, 591, 31));
        ShowHIGH->setChecked(true);

        retranslateUi(impactFilter);
        QObject::connect(buttonBox, SIGNAL(accepted()), impactFilter, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), impactFilter, SLOT(reject()));
        QObject::connect(resetButton, SIGNAL(clicked()), impactFilter, SLOT(accept()));

        QMetaObject::connectSlotsByName(impactFilter);
    } // setupUi

    void retranslateUi(QDialog *impactFilter)
    {
        impactFilter->setWindowTitle(QApplication::translate("impactFilter", "Dialog", nullptr));
        label_region->setText(QApplication::translate("impactFilter", "x", nullptr));
        region_label->setText(QApplication::translate("impactFilter", "Currently looking at region:", nullptr));
#ifndef QT_NO_TOOLTIP
        resetButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        resetButton->setText(QApplication::translate("impactFilter", "Do not filter by impact", nullptr));
        ShowUNKNOWN->setText(QApplication::translate("impactFilter", "Show mutations with unknown impact below following threshold:", nullptr));
        ShowMODIFIER->setText(QApplication::translate("impactFilter", "Show mutations with MODIFIER impact below following threshold:", nullptr));
        ShowLOW->setText(QApplication::translate("impactFilter", "Show mutations with LOW impact below following threshold:", nullptr));
        ShowMODERATE->setText(QApplication::translate("impactFilter", "Show mutations with MODERATE impact below following threshold:", nullptr));
        ShowHIGH->setText(QApplication::translate("impactFilter", "Show mutations with HIGH impact below following threshold:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class impactFilter: public Ui_impactFilter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPACTFILTER_H
