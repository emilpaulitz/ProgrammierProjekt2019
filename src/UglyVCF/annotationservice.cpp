#include "annotationservice.h"
#include <transcriptcons.h>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>

#include <string>






AnnotationService::AnnotationService()
{

}

//gets a JsonDoc and retuns a list of transcritioncons
QList<transcriptcons> parse_totranscrictionlist(QJsonDocument doc){

QList<transcriptcons> tlist;

QJsonArray jarray = doc.array();
QJsonObject jobject = jarray[0].toObject();
QString key = "transcript_consequences";
QJsonArray transarray = jobject.value(key).toArray();
int listlength = transarray.size();

//fill the qlist with all aviable trans...cons objects
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



    transcriptcons inlist = transcriptcons(trans,imp,var,gene,genesy,geneid,hgnc,strand,bio,dist,consequence_terms);

    tlist << inlist;
}

return tlist;
}

