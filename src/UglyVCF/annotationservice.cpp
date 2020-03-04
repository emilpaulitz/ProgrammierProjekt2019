#include "annotationservice.h"
#include "Transcriptcons.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <mainwindow.h>

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
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &AnnotationService::set_annotation);
    connect(this, &AnnotationService::annotation_set, this, &AnnotationService::handle_queue);
}

// To be called when the job to pull every annotation has been enqueued
// pullingAllAnnos should never be set to false -> enough reason to make this a new function?
void AnnotationService::setPullingAllAnnosTrue(){
    this->pullingAllAnnos = true;
}

// Returns true if the job to pull all annotations has been enqueued (maybe finished)
bool AnnotationService::isPullingAllAnnos() const{
    return this->pullingAllAnnos;
}

//
/**
 * @brief AnnotationService::makeVEPrequest Builds correct URL and sends a request if connected with the internet
 * @param manager referenece to QNetworkAccessManager of this AnnotationService object
 * @param line reference to the VCFline to which the annotation should be pulled
 */
void AnnotationService::makeVEPrequest(QNetworkAccessManager &manager, VCFline &line)
{
    qDebug() << __FUNCTION__;
    // get annotations
    //QNetworkAccessManager *manager = new QNetworkAccessManager();
    QString URL = "http://grch37.rest.ensembl.org/vep/homo_sapiens/hgvs/";
    QString notation = line.getHgvsNotation();
    QString optionJson = "content-type=application/json";
    QNetworkRequest *request = new QNetworkRequest(QUrl(URL + notation + optionJson));
    // check connectivity
    if (manager.networkAccessible())
    {
        manager.get(*request);
    } else {

        // emit signal to MainWindow to warn the user
        emit no_connection();
    }
}

/**
 * @brief AnnotationService::pullAnnotations get annotations for the whole table and write to Anno field of
 * VCFlines
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

    setPullingAllAnnosTrue();

    // start queue
    handle_queue();
}

/**
 * @brief AnnotationService::makeSingleRequest enqueues a single annotation pulling job
 * @param row int specifying the row of the line to which the annoation should be pulled
 */
void AnnotationService::makeSingleRequest(int row)
{
    qDebug() << __FUNCTION__;
    queue.enqueue(row);
    handle_queue();
}

// SLOTS

/**
 * @brief AnnotationService::set_annotation recieved reply is set as annotation onto the line in
 * this->currentIndex. TRIGGERED by: "finished"-signal from this->manager
 * @param reply The QNetorkReply recieved from VEP service
 */
void AnnotationService::set_annotation(QNetworkReply *reply)
{
    int index = this->currentIndex;
    qDebug() << __FUNCTION__ << index;
    QByteArray data = reply->readAll();

    // parse into transcriptcon object
    QJsonDocument jsondoc = QJsonDocument::fromJson(data);
    QList<Transcriptcons> tlist = Transcriptcons::parse_totranscrictionlist(jsondoc);

    // print into pretty string
    QString str = Transcriptcons::printtranscons(tlist);

    annoTableObj->getLine(index).setAnno(str);
    reply->deleteLater();

    // trigger handle_queue()
    emit annotation_set(index);
}

/**
 * @brief AnnotationService::handleQueue works through Queue, calls makeVEPrequest for every queue element
 * TRIGGRED by: "annotation_set"-signal from this
 */
void AnnotationService::handle_queue()
{
    if (!queue.isEmpty())
    {
        this->currentIndex = queue.dequeue();
        makeVEPrequest(*this->manager, annoTableObj->getLine(this->currentIndex));
    }
}

int AnnotationService::getQueueSize() const {
    return this->getQueue().size();
}
