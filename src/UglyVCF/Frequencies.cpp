#include "Frequencies.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>
#include <string>
#include <QList>

#include <QDebug>
#include <QThread>


Frequencies::Frequencies()
{

}

Frequencies::Frequencies(double afr, double eas, double gnomad_eas, double gnomad_nfe, double gnomad_fin,
                         double sas, double gnomad, double amr, double gnomad_sas, double aa, double gnomad_afr,
                         double eur, double ea, double gnomad_asj, double gnomad_amr, double gnomad_oth)
{
    this->afr = afr;
    this->eas = eas;
    this->sas = sas;
    this->amr = amr;
    this->aa = aa;
    this->eur = eur;
    this->ea = ea;
    this->gnomad_eas = gnomad_eas;
    this->gnomad_nfe = gnomad_nfe;
    this->gnomad_fin = gnomad_fin;
    this->gnomad_asj = gnomad_asj;
    this->gnomad_amr = gnomad_amr;
    this->gnomad_oth = gnomad_oth;
    this->gnomad_sas = gnomad_sas;
    this->gnomad_afr = gnomad_afr;
    this->gnomad = gnomad;
}

 Frequencies Frequencies::pars_frequencies(QJsonDocument doc){

  QString key1 = "colocated_variants";
  QString key2 = "frequencies";
  qWarning() << "is doc empty?" << doc.isEmpty();

  //declare the array
  QJsonArray jarray = doc.array();
  qWarning() << "is array empty? " << jarray.isEmpty();

  //go into first (0) compartment of array,and create objet jobcet
  QJsonObject jobject = jarray[0].toObject();
  qWarning() << "is jobject empty? " << jobject.isEmpty();

  //take the array value of key colocated_variants of jobject
  QJsonArray jarrayco = jobject.value(key1).toArray();
  qWarning() << "is jarrayco empty? " << jarray.isEmpty();

  //go into first(0) compartment of array
  int index = 0;
  QJsonObject jobjectfre = jarrayco[index].toObject();
  bool freqex = false;


  //go through all colocated_variant array object till we find one with frequencies,set jobjectfre to this object
  while(not freqex){
      qDebug() << "Test " + QString::fromStdString(std::to_string(index));
      QJsonObject freqob = jobjectfre.value(key2).toObject();
      if (freqob.isEmpty()){
          // Grund des BUGs: Schleife terminiert nicht, index wird absurd hoch -> jarrayco.size() benutzen?

         //set to new array pos
         jobjectfre = jarrayco[index].toObject();
         index++;
      } else{
          freqex = true;
      }
  }


 qWarning() << "is jobjectfre empty?" << jobjectfre.isEmpty();

  //search for key the last char of the value to key: allele_string

  QString key3 = jobjectfre.value("allele_string").toString();
  QString key4 = QString(key3[key3.size()-1]);

  //get value to key frquencies
  QJsonObject jfreq = jobjectfre.value(key2).toObject();

  //get objects to value of the last char of key3
  QJsonObject jAllele = jfreq.value(key4).toObject();

  index = 3;
  while(jAllele.isEmpty()){
      key4 =   QString(key3[key3.size()-index]);
      jAllele = jfreq.value(key4).toObject();
      index = index+2;
  }


  double afr,eas,gnomad_eas,gnomad_nfe,gnomad_fin,sas,gnomad,amr,gnomad_sas,
  aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth;

  //retriev all the value sto the freq keys
  afr = jAllele.value("afr").toDouble();
  eas = jAllele.value("eas").toDouble();
  sas = jAllele.value("sas").toDouble();
  amr = jAllele.value("amr").toDouble();
  aa = jAllele.value("aa").toDouble();
  eur = jAllele.value("eur").toDouble();
  ea = jAllele.value("ea").toDouble();
  gnomad = jAllele.value("gnomad").toDouble();
  gnomad_afr = jAllele.value("gnomad_afr").toDouble();
  gnomad_eas = jAllele.value("gnomad_eas").toDouble();
  gnomad_nfe = jAllele.value("gnomad_nfe").toDouble();
  gnomad_fin = jAllele.value("gnomad_fin").toDouble();
  gnomad_asj = jAllele.value("gnomad_asj").toDouble();
  gnomad_amr = jAllele.value("gnomad_amr").toDouble();
  gnomad_oth = jAllele.value("gnomad_oth").toDouble();
  gnomad_sas = jAllele.value("gnomad_sas").toDouble();

  //create freq. ob to return with given values
  Frequencies freq = Frequencies(afr,eas,gnomad_eas,gnomad_nfe,gnomad_fin,sas,gnomad,amr,gnomad_sas,
                                 aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth);

  return freq;
}

//retrieves a freq object and returns as string containing the freq
 QString Frequencies::print_frequencies(Frequencies freq){

    QString afr,eas,gnomad_eas,gnomad_nfe,gnomad_fin,sas,gnomad,amr,gnomad_sas,
    aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth,restring;

    //get all freq from class
    char mode = 'f';
    int presicion = 4;

    afr = QString::number(freq.getAfr(),mode,presicion);
    eas = QString::number(freq.getEas(),mode,presicion);
    sas = QString::number(freq.getSas(),mode,presicion);
    amr = QString::number(freq.getAa(),mode,presicion);
    aa = QString::number(freq.getAa(),mode,presicion);
    eur = QString::number(freq.getEur(),mode,presicion);
    ea = QString::number(freq.getEa(),mode,presicion);
    gnomad = QString::number(freq.getGnomad(),mode,presicion);
    gnomad_afr = QString::number(freq.getGnomad_afr(),mode,presicion);
    gnomad_eas = QString::number(freq.getGnomad_eas(),mode,presicion);
    gnomad_nfe = QString::number(freq.getGnomad_nfe(),mode,presicion);
    gnomad_fin = QString::number(freq.getGnomad_fin(),mode,presicion);
    gnomad_asj = QString::number(freq.getGnomad_asj(),mode,presicion);
    gnomad_amr = QString::number(freq.getGnomad_amr(),mode,presicion);
    gnomad_oth = QString::number(freq.getGnomad_oth(),mode,presicion);
    gnomad_sas = QString::number(freq.getGnomad_sas(),mode,presicion);

    //craete return string
    restring = restring+"AFR:"+afr+",EAS: "+eas+",SAS: "+sas+",AMR: "+amr+",AA: "+aa+",EUR:"+eur+",EA: "+ea
            +",GNOMAD: "+gnomad+",GNOMAD_AFR: ,"+gnomad_afr+"GNOMAD_EAS: "+gnomad_eas
            +",GNOMAD_NFE: "+gnomad_nfe+",GNOMAD_FIN: "+gnomad_fin+",GNOOMAD_ASJ: "+gnomad_asj
            +",GNOMAD_AMR: "+gnomad_amr+",GNOMAD_OTH: "+gnomad_oth+",GNOMAD_SAS: "+gnomad_sas;


    return restring;
}


double Frequencies::getAfr() const
{
    return afr;
}

void Frequencies::setAfr(double value)
{
    afr = value;
}

double Frequencies::getEas() const
{
    return eas;
}

void Frequencies::setEas(double value)
{
    eas = value;
}

double Frequencies::getGnomad_eas() const
{
    return gnomad_eas;
}

void Frequencies::setGnomad_eas(double value)
{
    gnomad_eas = value;
}

double Frequencies::getGnomad_nfe() const
{
    return gnomad_nfe;
}

void Frequencies::setGnomad_nfe(double value)
{
    gnomad_nfe = value;
}

double Frequencies::getGnomad_fin() const
{
    return gnomad_fin;
}

void Frequencies::setGnomad_fin(double value)
{
    gnomad_fin = value;
}

double Frequencies::getSas() const
{
    return sas;
}

void Frequencies::setSas(double value)
{
    sas = value;
}

double Frequencies::getGnomad() const
{
    return gnomad;
}

void Frequencies::setGnomad(double value)
{
    gnomad = value;
}

double Frequencies::getAmr() const
{
    return amr;
}

void Frequencies::setAmr(double value)
{
    amr = value;
}

double Frequencies::getGnomad_sas() const
{
    return gnomad_sas;
}

void Frequencies::setGnomad_sas(double value)
{
    gnomad_sas = value;
}

double Frequencies::getAa() const
{
    return aa;
}

void Frequencies::setAa(double value)
{
    aa = value;
}

double Frequencies::getGnomad_afr() const
{
    return gnomad_afr;
}

void Frequencies::setGnomad_afr(double value)
{
    gnomad_afr = value;
}

double Frequencies::getEur() const
{
    return eur;
}

void Frequencies::setEur(double value)
{
    eur = value;
}

double Frequencies::getEa() const
{
    return ea;
}

void Frequencies::setEa(double value)
{
    ea = value;
}

double Frequencies::getGnomad_asj() const
{
    return gnomad_asj;
}

void Frequencies::setGnomad_asj(double value)
{
    gnomad_asj = value;
}

double Frequencies::getGnomad_amr() const
{
    return gnomad_amr;
}

void Frequencies::setGnomad_amr(double value)
{
    gnomad_amr = value;
}

double Frequencies::getGnomad_oth() const
{
    return gnomad_oth;
}

void Frequencies::setGnomad_oth(double value)
{
    gnomad_oth = value;
}



