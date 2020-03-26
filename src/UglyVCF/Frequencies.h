#ifndef FREQUENCIES_H
#define FREQUENCIES_H
#include <QJsonDocument>
#include "filterdialog.h"




class Frequencies
{

private:
double FreqByRegions[(int) FilterDialog::LASTENUM];
QString noted;

// afr,eas,gnomad_eas,gnomad_nfe,gnomad_fin,sas,gnomad,amr,gnomad_sas,
//aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth;

public:
    Frequencies();

    Frequencies(QString note);

    Frequencies(double afr, double eas,double gnomad_eas,double gnomad_nfe,double gnomad_fin, double sas, double gonmad,
                double amr, double gnomad_sas, double aa, double gnomad_afr, double eur, double ea, double gnomad_asj,
                double gnomad_amr, double gnomad_oth);

    double getFreq(FilterDialog::Region region);
    void setFreq(FilterDialog::Region region, double value);

    bool isUnknown();

/*

    double getAfr() const;
    void setAfr(double value);

    double getEas() const;
    void setEas(double value);

    double getGnomad_eas() const;
    void setGnomad_eas(double value);

    double getGnomad_nfe() const;
    void setGnomad_nfe(double value);

    double getGnomad_fin() const;
    void setGnomad_fin(double value);

    double getSas() const;
    void setSas(double value);

    double getGnomad() const;
    void setGnomad(double value);

    double getAmr() const;
    void setAmr(double value);

    double getGnomad_sas() const;
    void setGnomad_sas(double value);

    double getAa() const;
    void setAa(double value);

    double getGnomad_afr() const;
    void setGnomad_afr(double value);

    double getEur() const;
    void setEur(double value);

    double getEa() const;
    void setEa(double value);

    double getGnomad_asj() const;
    void setGnomad_asj(double value);

    double getGnomad_amr() const;
    void setGnomad_amr(double value);

    double getGnomad_oth() const;
    void setGnomad_oth(double value);*/

   static Frequencies pars_frequencies(QJsonDocument doc);

   static QString print_frequencies(Frequencies freq);
};


#endif // FREQUENCIES_H
