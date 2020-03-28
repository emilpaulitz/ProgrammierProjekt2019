#include "impactfilter.h"
#include "ui_impactfilter.h"

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
