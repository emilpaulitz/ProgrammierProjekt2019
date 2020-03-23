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

Frequencies::Frequencies(double afr, double eas, double gnomad_eas, double gnomad_nfe, double gnomad_fin,
                         double sas, double gnomad, double amr, double gnomad_sas, double aa, double gnomad_afr,
                         double eur, double ea, double gnomad_asj, double gnomad_amr, double gnomad_oth)
{
    this->FreqByRegions[FilterDialog::afr] = afr;
    this->FreqByRegions[FilterDialog::eas] = eas;
    this->FreqByRegions[FilterDialog::gnomad_eas] = gnomad_eas;
    this->FreqByRegions[FilterDialog::gnomad_nfe] = gnomad_nfe;
    this->FreqByRegions[FilterDialog::gnomad_fin] = gnomad_fin;
    this->FreqByRegions[FilterDialog::sas] = sas;
    this->FreqByRegions[FilterDialog::gnomad] = gnomad;
    this->FreqByRegions[FilterDialog::amr] = amr;
    this->FreqByRegions[FilterDialog::gnomad_sas] = gnomad_sas;
    this->FreqByRegions[FilterDialog::aa] = aa;
    this->FreqByRegions[FilterDialog::gnomad_afr] = gnomad_afr;
    this->FreqByRegions[FilterDialog::eur] = eur;
    this->FreqByRegions[FilterDialog::ea] = ea;
    this->FreqByRegions[FilterDialog::gnomad_asj] = gnomad_asj;
    this->FreqByRegions[FilterDialog::gnomad_amr] = gnomad_amr;
    this->FreqByRegions[FilterDialog::gnomad_oth] = gnomad_oth;
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
  qWarning() << "list of key in jobject" << jobject.keys();

  /**Key Liste <- ("allele_string", "assembly_name", "end", "id", "input",
         "most_severe_consequence", "seq_region_name",
         "start", "strand", "transcript_consequences")
         key1 fehlt -> keine freqcies -> craah weiter unten
    **/

  //take the array value of key colocated_variants of jobject
  QJsonArray jarrayco = jobject.value(key1).toArray();
  qWarning() << "is jarrayco empty? " << jarrayco.isEmpty(); //<- ist empty im bug

  //go into first(0) compartment of array
  int index = 0;
  QJsonObject jobjectfre; // = jarrayco[index].toObject();
  // bool freqex = false;


  //go through all colocated_variant array object till we find one with frequencies,set jobjectfre to this object
 /** while(not freqex){
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
  **/
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

//returns a String containing all the regions and their frequency
 QString Frequencies::print_frequencies(Frequencies freq){

    QString restring;

    for (int i = 0; i < FilterDialog::LASTENUM; i++) {

        FilterDialog::Region reg = (FilterDialog::Region) i;
        restring += FilterDialog::regionToString(reg) + ": " + QString::number(freq.getFreq(reg));

        // Add comma if not the last entry
        if (i + 1 != FilterDialog::LASTENUM) {
            restring += ", ";
        }
    }
    return restring;
}

double Frequencies::getFreq(FilterDialog::Region region){
    return this->FreqByRegions[(int) region];
}

void Frequencies::setFreq(FilterDialog::Region region, double value){
    this->FreqByRegions[(int) region] = value;
}
