#include "Transcriptcons.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QJsonArray>
#include <string>
#include <QList>



QString Transcriptcons::getTranscript_id() const
{
    return transcript_id;
}

void Transcriptcons::setTranscript_id(const QString &value)
{
    transcript_id = value;
}

QString Transcriptcons::getImpact() const
{
    return impact;
}

void Transcriptcons::setImpact(const QString &value)
{
    impact = value;
}

QString Transcriptcons::getVariant_allele() const
{
    return variant_allele;
}

void Transcriptcons::setVariant_allele(const QString &value)
{
    variant_allele = value;
}

QString Transcriptcons::getGene_symbole() const
{
    return gene_symbole;
}

void Transcriptcons::setGene_symbole(const QString &value)
{
    gene_symbole = value;
}

QString Transcriptcons::getGene_symbol_source() const
{
    return gene_symbol_source;
}

void Transcriptcons::setGene_symbol_source(const QString &value)
{
    gene_symbol_source = value;
}

QString Transcriptcons::getGene_id() const
{
    return gene_id;
}

void Transcriptcons::setGene_id(const QString &value)
{
    gene_id = value;
}

QString Transcriptcons::getHgnc_id() const
{
    return hgnc_id;
}

void Transcriptcons::setHgnc_id(const QString &value)
{
    hgnc_id = value;
}

QString Transcriptcons::getStrand() const
{
    return strand;
}

void Transcriptcons::setStrand(const QString &value)
{
    strand = value;
}

QString Transcriptcons::getBiotype() const
{
    return biotype;
}

void Transcriptcons::setBiotype(const QString &value)
{
    biotype = value;
}

QString Transcriptcons::getDistance() const
{
    return distance;
}

void Transcriptcons::setDistance(const QString &value)
{
    distance = value;
}

QList<QString> Transcriptcons::getConsequence_terms() const
{
    return consequence_terms;
}

void Transcriptcons::setConsequence_terms(const QList<QString> &value)
{
    consequence_terms = value;
}

Transcriptcons::Transcriptcons()
{

}
//constructor mit input
Transcriptcons::Transcriptcons(QString transcript_id,QString impact,QString variant_allele,QString gene_symbole,QString gene_symbol_source,
                               QString gene_id,QString hgnc_id,QString strand,QString biotype,QString distance,QList<QString> consequence_terms){
this->transcript_id = transcript_id;
this->impact = impact;
this->variant_allele = variant_allele;
this->gene_symbole = gene_symbole;
this->gene_symbol_source = gene_symbol_source;
this->gene_id = gene_id;
this->hgnc_id = hgnc_id;
this->strand = strand;
this->biotype = biotype;
this->distance = distance;
this->consequence_terms = consequence_terms;}






//gets a JsonDoc and retuns a list of transcritioncons
QList<Transcriptcons> Transcriptcons::parse_totranscrictionlist(QJsonDocument doc){

QList<Transcriptcons> tlist;

QJsonArray jarray = doc.array();
QJsonObject jobject = jarray[0].toObject();
QString key = "transcript_consequences";
QJsonArray transarray = jobject.value(key).toArray();
int listlength = transarray.size();

//fill the qlist with all available trans...cons objects
for(int i = 0; i < listlength; i++){
    QJsonObject ob = transarray[i].toObject();
    QJsonArray ja = ob.value("consequence_terms").toArray();
    QList<QString> consequence_terms;


    for(int o = 0; o < ja.size(); o++){
        consequence_terms << ja[o].toString();
    }

    //creates a trans..cons object to be included in the qlist inlist
    QString trans = ob.value("transcript_id").toString();
    QString imp = ob.value("impact").toString();
    QString var = ob.value("variant_allele").toString();
    QString gene = ob.value("gene_symbol").toString();
    QString genesy = ob.value("gene_symbol_source").toString();
    QString geneid = ob.value("gene_id").toString();
    QString hgnc = QString::number(ob.value("hgnc_id").toInt());
    QString strand = QString::number(ob.value("strand").toInt());
    QString bio = ob.value("biotype").toString();
    QString dist = QString::number(ob.value("distance").toInt());



    Transcriptcons inlist = Transcriptcons(trans,imp,var,gene,genesy,geneid,hgnc,strand,bio,dist,consequence_terms);

    tlist << inlist;
}

return tlist;
}

QString Transcriptcons::printtranscons(Transcriptcons trans){
    QString re = "TRANSCRIPT_ID: ";
    QString li;
    QList<QString> qli = trans.getConsequence_terms();
   for(int i =0; i < qli.size(); i++){
        li = li +","+qli.at(i);  }

    re = re + trans.getTranscript_id() +",\n IMPACT: " + trans.getImpact()+",\n VARIANT_ALLELE: " + trans.getVariant_allele()
       +",\n GENE_SYMBOLE: " + trans.getGene_symbole()+",\n GENE_SYMBOLE_SOURCE: "+ trans.getGene_symbol_source()
       +",\n GENE_ID: "+ trans.getGene_id()+",\n HGNC: " + trans.getHgnc_id()+",\n STRAND: "
       + trans.getStrand()+",\n BIOTYPE: " + trans.getBiotype()+",\n DISTANCE: " + trans.getDistance()+",[" + li + "] \n";
    return re;
}

QString Transcriptcons::printtranscons(QList<Transcriptcons> trans){
    QString re;

    for(int i = 0; i < trans.size(); i++){
        re = re + printtranscons(trans.at(i))+ " \n ";
    }
    return re;
}



