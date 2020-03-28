#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>

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
        aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth,LASTENUM
    };

    QString static regionToString(Region region);

    double getFreq();
    FilterDialog::Region getRegion();
    bool hideUnknown();
    bool isReset();


private slots:
    void on_resetButton_clicked();

    void on_severityButton_clicked();

private:
    Ui::FilterDialog *ui;
    bool reset =false;
};

#endif // FILTERDIALOG_H
