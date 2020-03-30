#include "impactfilter.h"
#include "ui_impactfilter.h"
#include "filterdialog.h"
#include "annotationservice.h"

impactFilter::impactFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::impactFilter)
{
    ui->setupUi(this);
}

impactFilter::~impactFilter()
{
    delete ui;
}

/**
 * @brief impactFilter::open opens the impact filter dialog, showing the specified region
 * @param region
 */
void impactFilter::openWindow(QString region) {
    ui->label_region->setText(region);
    this->filterByImpact = true;
}

double impactFilter::getHigh(){
    if (!ui->ShowHIGH->isChecked()) {
        return -1;
    }
    return ui->HIGH_impact->value();
}

double impactFilter::getModerate(){
    if (!ui->ShowMODERATE->isChecked()) {
        return -1;
    }
    return ui->MODERATE_impact->value();
}

double impactFilter::getLow(){
    if (!ui->ShowLOW->isChecked()) {
        return -1;
    }
    return ui->LOW_impact->value();
}

double impactFilter::getModifier(){
    qDebug() << "boxChecked=" << ui->ShowMODIFIER;
    if (!ui->ShowMODIFIER->isChecked()) {
        return -1;
    }
    return ui->MODIFIER_impact->value();
}

double impactFilter::getUnknown(){
    if (!ui->ShowUNKNOWN->isChecked()) {
        return -1;
    }
    return ui->unknown_impact->value();
}

bool impactFilter::isFilterByImpact(){
    return this->filterByImpact;
}

void impactFilter::on_resetButton_clicked(){
    filterByImpact = false;
}
