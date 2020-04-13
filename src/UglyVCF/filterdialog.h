#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include "impactfilter.h"

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr);
    ~FilterDialog();

    enum Region {
        afr,eas,gnomad_eas,gnomad_nfe,gnomad_fin,sas,gnomad,amr,gnomad_sas,
        aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth,LASTREGION
    };

    // order has to be highest impact to lowest impact!
    enum Impact {
        HIGH=0, MODERATE=1, LOW=2, MODIFER=3, LASTIMPACT=4
    };

    Impact static stringToImpact (QString str);
    QString static regionToString(Region region);

    double getFreq();
    double getFreq(FilterDialog::Impact impact);
    FilterDialog::Region getRegion();
    bool hideUnknown();
    bool isReset();
    void resetFilter();
    bool isFilterByImpact();
    void windowOpened();


private slots:
    void on_resetButton_clicked();

    void on_severityButton_clicked();

private:
    Ui::FilterDialog *ui;
    impactFilter * impact = nullptr;
    bool filterByImpact = false;
    bool reset = false;
};

#endif // FILTERDIALOG_H
