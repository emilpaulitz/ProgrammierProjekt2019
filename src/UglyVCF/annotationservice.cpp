#include "annotationservice.h"
#include "transcriptcons.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QList>

#include <string>
#include <QMessageBox>





QQueue<int> AnnotationService::getQueue() const
{
    return queue;
}

AnnotationService::AnnotationService()
{
}

AnnotationService::AnnotationService(VCFtable *table)
{
    annoTableObj = table;
}

void AnnotationService::makeVEPrequest(VCFline &line)
{
    qDebug() << __FUNCTION__;
    // get annotations
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QString URL = "http://grch37.rest.ensembl.org/vep/homo_sapiens/hgvs/";
    QString notation = line.getHgvsNotation();
    QString optionJson = "content-type=application/json";
    QNetworkRequest *request = new QNetworkRequest(QUrl(URL + notation + optionJson));
    // check connectivity
    if (manager->networkAccessible())
    {
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(set_annotation(QNetworkReply*)));
        // make request
        manager->get(*request);
    } else {
        // TODO: pop warning: no internet
        emit no_connection();
    }
    //manager->deleteLater();
}


/**
 * @brief AnnotationService::pullAnnotations get annotations for the whole table and write to VCFlines
 * @param table reference to the VCFtable Object
 */
void AnnotationService::pullAnnotations(VCFtable &table)
{
    // add lines to queue
    for (int index = 0; index < table.getLines().size(); index++)
    {
        //TODO: check database, only add necessary lines
        queue.enqueue(index);
    }
    // make requests
    connect(this, SIGNAL(annotation_set()), this, SLOT(handle_queue()));
    handle_queue();
}

/*
void AnnotationService::handleQueue()
{
    qDebug() << __FUNCTION__;

    handle_next_item();
}
*/

void AnnotationService::makeSingleRequest(int row)
{
    qDebug() << __FUNCTION__;
    queue.enqueue(row);
    handle_queue();
}

//gets a JsonDoc and retuns a list of transcritioncons
QList<transcriptcons> parse_totranscrictionlist(QJsonDocument doc)
{
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

// SLOTS
void AnnotationService::set_annotation(QNetworkReply *reply)
{
    qDebug() << __FUNCTION__ << currentIndex;
    QByteArray data = reply->readAll();
    QString str = QString::fromLatin1(data);
    // get line
    annoTableObj->getLine(currentIndex).setAnno(str);
    reply->deleteLater();
    emit annotation_set();
}

/**
 * @brief AnnotationService::handleQueue works through Queue, calls makeVEPrequest for every queue element
 */
void AnnotationService::handle_queue()
{
    if (!queue.isEmpty())
    {
        currentIndex = queue.dequeue();
        makeVEPrequest(annoTableObj->getLine(currentIndex));
    }
}
