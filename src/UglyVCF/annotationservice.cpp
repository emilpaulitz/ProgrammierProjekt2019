#include "annotationservice.h"
#include "Transcriptcons.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <mainwindow.h>
#include <databank.h>

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

/**
 * @brief AnnotationService::setupAnnoService similarly to a constructor, setting the object up for work.
 * Out sourced to be able to control the order of connects
 * @param table
 */
void AnnotationService::setupAnnoService(VCFtable *table){
    annoTableObj = table;
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &AnnotationService::setAnnoFromVEP);
}

/**
 * @brief AnnotationService::isPullingAllAnnos Returns true if the Queue has been filled and is being handled.
 * @return
 */
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
    // get annotations
    QString URL = "http://grch37.rest.ensembl.org/vep/homo_sapiens/hgvs/";
    QString notation = line.getHgvsNotation();
    QString optionJson = "content-type=application/json";

    QNetworkRequest *request = new QNetworkRequest(QUrl(URL + notation +" ?" + optionJson));

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
    if(!isPullingAllAnnos()){
        // add lines to queue
        for (int index = 0; index < table.getLines().size(); index++)
        {
            //check database, pull available entries first
            if (databank::searchDatabank(table.getLine(index).getHgvsNotation()))
            {
                queue.prepend(index);
            } else {
                queue.enqueue(index);
            }
        }

        startQueue();
    }
}

/**
 * @brief AnnotationService::makeSingleRequest enqueues a single annotation pulling job
 * @param row int specifying the row of the line to which the annoation should be pulled
 */
void AnnotationService::makeSingleRequest(int row)
{
    queue.prepend(row);
    startQueue();
}

// SLOTS

/**
 * @brief AnnotationService::setAnnoFromVEP recieved reply is set as annotation onto the line in
 * this->currentIndex. TRIGGERED by: "finished"-signal from this->manager
 * @param reply The QNetorkReply recieved from VEP service
 */
void AnnotationService::setAnnoFromVEP(QNetworkReply *reply)
{
    int index = this->currentIndex;
    QByteArray data = reply->readAll();

    // parse into annotation object
    QJsonDocument jsondoc = QJsonDocument::fromJson(data);
    Annotation* anno = new Annotation(jsondoc);

    databank::addRow(*anno);

    annoTableObj->getLine(index).setAnno(*anno);
    reply->deleteLater();

    emit annotation_set(index);
    handle_queue();
}

/**
 * @brief AnnotationService::setAnnoFromDB retrieves entry with given hgvs from db and sets
 * it as the annotation for the given row.
 * @param row row of the table object the annotation should be set for
 * @param hgvs hgvs notation of the Annotation to be retrieved
 */
void AnnotationService::setAnnoFromDB(int row, QString & hgvs){
    Annotation & currAnno = databank::retrieveAnno(hgvs);
    annoTableObj->getLine(row).setAnno(currAnno);
    emit annotation_set(row);
}

/**
 * @brief AnnotationService::startQueue starts handling of the queue if it is not already running
 */
void AnnotationService::startQueue() {
    if (!isPullingAllAnnos()){
        this->pullingAllAnnos = true;
        handle_queue();
    }
}

/**
 * @brief AnnotationService::handleQueue DO NOT CALL! Instead call startQueue()!
 * ONLY called by start_queue or setAnnofromVEP
 * works through the queue and starts either VEP requests or DB pulls.
 */
void AnnotationService::handle_queue()
{
    // work through the necessary db pulls until the queue is empty or an VEP request is to be made.
    // When that finishes, it will call the function again
    while (!queue.isEmpty()) {

        this->currentIndex = queue.dequeue();
        QString currHGVS = annoTableObj->getLine(currentIndex).getHgvsNotation();

        if (databank::searchDatabank(currHGVS)) {
            setAnnoFromDB(currentIndex, currHGVS);
        } else {
            makeVEPrequest(*this->manager, annoTableObj->getLine(this->currentIndex));
            return;
        }
    }

    // pulling is finished
    this->pullingAllAnnos = false;
    emit queueFinished();
}

int AnnotationService::getQueueSize() const {
    return this->getQueue().size();
}
