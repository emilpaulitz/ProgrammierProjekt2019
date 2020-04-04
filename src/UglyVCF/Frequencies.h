#ifndef FREQUENCIES_H
#define FREQUENCIES_H
#include <QJsonDocument>
#include "filterdialog.h"

class Frequencies
{

private:
double FreqByRegions[(int) FilterDialog::LASTREGION];

public:
    Frequencies();


    Frequencies(double afr, double eas,double gnomad_eas,double gnomad_nfe,double gnomad_fin, double sas, double gonmad,
                double amr, double gnomad_sas, double aa, double gnomad_afr, double eur, double ea, double gnomad_asj,
                double gnomad_amr, double gnomad_oth);

    double getFreq(FilterDialog::Region region);
    void setFreq(FilterDialog::Region region, double value);

    bool isRegUnknown(FilterDialog::Region region);

   static Frequencies parse_Frequencies(QJsonDocument doc);

   static QString print_Frequencies(Frequencies freq);
};


#endif // FREQUENCIES_H
