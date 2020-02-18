#include "transcriptcons.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <string>

transcriptcons::transcriptcons()
{

}
//constructor mit input
transcriptcons::transcriptcons(QString transcript_id,QString impact,QString variant_allele,QString gene_symbole,QString gene_symbol_source,
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


QString transcriptcons::getTranscript_id() const
{
    return transcript_id;
}

void transcriptcons::setTranscript_id(const QString &value)
{
    transcript_id = value;
}

QString transcriptcons::getImpact() const
{
    return impact;
}

void transcriptcons::setImpact(const QString &value)
{
    impact = value;
}

QString transcriptcons::getVariant_allele() const
{
    return variant_allele;
}

void transcriptcons::setVariant_allele(const QString &value)
{
    variant_allele = value;
}

QString transcriptcons::getGene_symbol_source() const
{
    return gene_symbol_source;
}

void transcriptcons::setGene_symbol_source(const QString &value)
{
    gene_symbol_source = value;
}

QString transcriptcons::getGene_id() const
{
    return gene_id;
}

void transcriptcons::setGene_id(const QString &value)
{
    gene_id = value;
}

QString transcriptcons::getHgnc_id() const
{
    return hgnc_id;
}

void transcriptcons::setHgnc_id(const QString &value)
{
    hgnc_id = value;
}

QString transcriptcons::getGene_symbole() const
{
    return gene_symbole;
}

void transcriptcons::setGene_symbole(const QString &value)
{
    gene_symbole = value;
}

QString transcriptcons::getStrand() const
{
    return strand;
}

void transcriptcons::setStrand(const QString &value)
{
    strand = value;
}

QString transcriptcons::getBiotype() const
{
    return biotype;
}

void transcriptcons::setBiotype(const QString &value)
{
    biotype= value;
}

QString transcriptcons::getDistance() const
{
    return distance;
}

void transcriptcons::setDistance(const QString &value)
{
    distance= value;
}

QList<QString> transcriptcons::getConsequence_terms() const
{
    return consequence_terms;
}

void transcriptcons::setConsequence_terms(const QList<QString> &value)
{
    consequence_terms = value;
}


QString printtranscons(transcriptcons trans){
    QString re;
    QString li;
    QList<QString> qli = trans.getConsequence_terms();
   for(int i =0; i < qli.size(); i++){
        li = li +","+qli.at(i);  }

    re = re + trans.getTranscript_id() +"," + trans.getImpact()+"," + trans.getVariant_allele()+"," + trans.getGene_symbole()+","
       + trans.getGene_symbol_source()+","+ trans.getGene_id()+"," + trans.getHgnc_id()+","
       + trans.getStrand()+"," + trans.getBiotype()+"," + trans.getDistance()+",[" + li + "]";
    return re;
}

QString printtranscons(QList<transcriptcons> trans){
    QString re;

    for(int i = 0; i < trans.size(); i++){
        re = re + printtranscons(trans.at(i))+ " \n ";
    }
    return re;
}



