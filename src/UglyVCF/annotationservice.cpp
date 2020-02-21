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

//TODO: find a way that manager does not need to be initialized every time (z.B. makeVEPrequest(manager, &line)
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
    ///manager->deleteLater();
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


void AnnotationService::makeSingleRequest(int row)
{
    qDebug() << __FUNCTION__;
    queue.enqueue(row);
    handle_queue();
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
