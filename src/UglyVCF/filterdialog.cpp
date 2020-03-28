#include "filterdialog.h"
#include "ui_filterdialog.h"

#include "annotationservice.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);
    for (int i = 0; i < FilterDialog::LASTENUM; i++){
        ui->comboBox->addItem(regionToString((Region) i));
    }

}

double FilterDialog::getFreq(){
    if (isReset()){
        return 1;
    }
    return ui->doubleSpinBox->value();
}

FilterDialog::Region FilterDialog::getRegion(){
    if (isReset()){
        return (Region) 0;
    }

    for (int i = 0; i < LASTENUM; i++){
        if(regionToString((Region) i) == ui->comboBox->currentText()){
            return (Region) i;
        }
    }

    qDebug() << "Something went wrong in filterdialog.cpp line 22!"
                " The text chosen in ComboBox could not be converted to a filter::Region enum type!";
    return LASTENUM;
}

bool FilterDialog::hideUnknown(){
    if (isReset()){
        return false;
    }
    return ui->hideBox->isChecked();
}

bool FilterDialog::isReset(){
    return this->reset;
}

QString FilterDialog::regionToString(FilterDialog::Region region) {
    switch (region) {
    case FilterDialog::aa:
        return "aa";
        break;
    case FilterDialog::ea:
        return "ea";
        break;
    case FilterDialog::afr:
        return "afr";
        break;
    case FilterDialog::amr:
        return "amr";
        break;
    case FilterDialog::eas:
        return "eas";
        break;
    case FilterDialog::eur:
        return "eur";
        break;
    case FilterDialog::sas:
        return "sas";
        break;
    case FilterDialog::gnomad:
        return "gnomad";
        break;
    case FilterDialog::gnomad_afr:
        return "gnomad_afr";
        break;
    case FilterDialog::gnomad_amr:
        return "gnomad_amr";
        break;
    case FilterDialog::gnomad_asj:
        return "gnomad_asj";
        break;
    case FilterDialog::gnomad_eas:
        return "gnomad_eas";
        break;
    case FilterDialog::gnomad_fin:
        return "gnomad_fin";
        break;
    case FilterDialog::gnomad_nfe:
        return "gnomad_nfe";
        break;
    case FilterDialog::gnomad_oth:
        return "gnomad_oth";
        break;
    case FilterDialog::gnomad_sas:
        return "gnomad_sas";
        break;
    default:
        return "Error";
        break;
    }
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::on_resetButton_clicked()
{
    qDebug() << "Filter reset";
    this->reset = true;
}

void FilterDialog::on_severityButton_clicked()
{

}
