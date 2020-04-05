
#include "Frequencies.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>
#include <string>
#include <QList>

#include <QDebug>
#include <QThread>


Frequencies::Frequencies(){

}
//Objekt with Enum, keeps frequencies
Frequencies::Frequencies(double afr, double eas, double gnomad_eas, double gnomad_nfe, double gnomad_fin,
                         double sas, double gnomad, double amr, double gnomad_sas, double aa, double gnomad_afr,
                         double eur, double ea, double gnomad_asj, double gnomad_amr, double gnomad_oth)
{
    this->freqByRegions[FilterDialog::afr] = afr;
    this->freqByRegions[FilterDialog::eas] = eas;
    this->freqByRegions[FilterDialog::gnomad_eas] = gnomad_eas;
    this->freqByRegions[FilterDialog::gnomad_nfe] = gnomad_nfe;
    this->freqByRegions[FilterDialog::gnomad_fin] = gnomad_fin;
    this->freqByRegions[FilterDialog::sas] = sas;
    this->freqByRegions[FilterDialog::gnomad] = gnomad;
    this->freqByRegions[FilterDialog::amr] = amr;
    this->freqByRegions[FilterDialog::gnomad_sas] = gnomad_sas;
    this->freqByRegions[FilterDialog::aa] = aa;
    this->freqByRegions[FilterDialog::gnomad_afr] = gnomad_afr;
    this->freqByRegions[FilterDialog::eur] = eur;
    this->freqByRegions[FilterDialog::ea] = ea;
    this->freqByRegions[FilterDialog::gnomad_asj] = gnomad_asj;
    this->freqByRegions[FilterDialog::gnomad_amr] = gnomad_amr;
    this->freqByRegions[FilterDialog::gnomad_oth] = gnomad_oth;
}





/**
  * @brief Frequencies::parse_Frequencies, parases a QJason Doc to a Frequenciesy object
  * @param QJsonDocument doc
  * @returnFrequencies Object
  */
Frequencies Frequencies::parse_Frequencies(QJsonDocument doc){





  QString key1 = "colocated_variants";
  QString key2 = "frequencies";
  qWarning() << "is doc empty?" << doc.isEmpty();

  //declare the array
  QJsonArray jarray = doc.array();
  qWarning() << "is array empty? " << jarray.isEmpty();

    //go into first (0) compartment of array,and create objet jobcet
  QJsonObject jobject = jarray[0].toObject();
  qWarning() << "is jobject empty? " << jobject.isEmpty();
  qWarning() << "list of key in jobject" << jobject.keys();

  /**Key Liste <- ("allele_string", "assembly_name", "end", "id", "input",
         "most_severe_consequence", "seq_region_name",
         "start", "strand", "transcript_consequences")
         key1 fehlt -> keine freqcies -> crash weiter unten
    **/

  //take the array value of key colocated_variants of jobject
  QJsonArray jarrayco = jobject.value(key1).toArray();
  qWarning() << "is jarrayco empty? " << jarrayco.isEmpty(); //<- ist empty im bug

  //go into first(0) compartment of array
  int index = 0;
  QJsonObject jobjectfre;


  //go through all colocated_variant array object till we find one with frequencies,set jobjectfre to this object

  for(int a = 0; a <jarrayco.size(); a++){
    jobjectfre = jarrayco[a].toObject();
    QJsonObject freqob = jobjectfre.value(key2).toObject();

    if (not freqob.isEmpty()){
        break;
    }
  }

  qWarning() << "is jobjectfre empty?" << jobjectfre.isEmpty();

  //search for key the last char of the value to key: allele_string

  QString key3 = "-,A,C,G,T,U";
  QString key4 = QString(key3[key3.size()-1]);

  //get value to key frquencies
  QJsonObject jfreq = jobjectfre.value(key2).toObject();

  //get objects to value of the last char of key3
  QJsonObject jAllele = jfreq.value(key4).toObject();

  //Key 4
  index = 3;
  while(jAllele.isEmpty() and key3.size()-index != -2){
      key4 =   QString(key3[key3.size()-index]);
      jAllele = jfreq.value(key4).toObject();
      index = index+2;
  }


  double afr,eas,gnomad_eas,gnomad_nfe,gnomad_fin,sas,gnomad,amr,gnomad_sas,
  aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth;

  //retrieve all the values to the freq keys
  afr = jAllele.value("afr").toDouble(-1);
  eas = jAllele.value("eas").toDouble(-1);
  sas = jAllele.value("sas").toDouble(-1);
  amr = jAllele.value("amr").toDouble(-1);
  aa = jAllele.value("aa").toDouble(-1);
  eur = jAllele.value("eur").toDouble(-1);
  ea = jAllele.value("ea").toDouble(-1);
  gnomad = jAllele.value("gnomad").toDouble(-1);
  gnomad_afr = jAllele.value("gnomad_afr").toDouble(-1);
  gnomad_eas = jAllele.value("gnomad_eas").toDouble(-1);
  gnomad_nfe = jAllele.value("gnomad_nfe").toDouble(-1);
  gnomad_fin = jAllele.value("gnomad_fin").toDouble(-1);
  gnomad_asj = jAllele.value("gnomad_asj").toDouble(-1);
  gnomad_amr = jAllele.value("gnomad_amr").toDouble(-1);
  gnomad_oth = jAllele.value("gnomad_oth").toDouble(-1);
  gnomad_sas = jAllele.value("gnomad_sas").toDouble(-1);

  //create freq. ob to return with given values
  Frequencies freq = Frequencies(afr,eas,gnomad_eas,gnomad_nfe,gnomad_fin,sas,gnomad,amr,gnomad_sas,
                                 aa,gnomad_afr,eur,ea,gnomad_asj,gnomad_amr,gnomad_oth);

  return freq;
}


//returns a String containing all the regions and their frequency
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 8d8a9dbb4ac9d29ddf7b292173a1a00d689b1fed
=======

>>>>>>> 8d8a9dbb4ac9d29ddf7b292173a1a00d689b1fed
/**
  * @brief Frequencies::print_Frequencies, creates a readable QString out of a Frequencies object
  * @param Frequencies freq
  * @return QString
  */

 QString Frequencies::print_Frequencies(Frequencies freq){

    QString restring;
    QString region;
    QString value;

    for (int i = 0; i < FilterDialog::LASTREGION; i++) {

        FilterDialog::Region reg = (FilterDialog::Region) i;
        region = FilterDialog::regionToString(reg) + ": ";
                if(freq.getFreq(reg) == -1){
           value= "frequency unknown";
    }
                else{
                value= QString::number(freq.getFreq(reg));
    }

                restring+= region + value;

                // Add comma if not the last entry
        if (i + 1 != FilterDialog::LASTREGION) {
            restring += ", ";
        }

        restring +=  + "\n";
    }
    return restring;
}

 /**
 * @brief Frequencies::getFreq, getter Enum Region specific
 * @param FilterDialog::Region region
 * @return double
 */
double Frequencies::getFreq(FilterDialog::Region region){
    return this->freqByRegions[(int) region];
}
/**
 * @brief Frequencies::setFreq, setter Enum region specific
 * @param FilterDialog::Region region
 * @param double value
 */
void Frequencies::setFreq(FilterDialog::Region region, double value){
    this->freqByRegions[(int) region] = value;
}

/**
 * @brief Frequencies::isRegUnknown, check if region is unkown
 * @param FilterDialog::Region region
 * @return bool
 */
bool Frequencies::isRegUnknown(FilterDialog::Region region){
    if (getFreq(region) == -1){
        return true;
    }
    return false;
}
