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
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(set_annotation(QNetworkReply*)));
}

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
    connect(this, &AnnotationService::annotation_set, this, &AnnotationService::handle_queue);
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
    int index = currentIndex;
    qDebug() << __FUNCTION__ << index;
    QByteArray data = reply->readAll();
    QString str = QString::fromLatin1(data);
    annoTableObj->getLine(index).setAnno(str);
    reply->deleteLater();

    // trigger handle_queue()
    emit annotation_set(index);
}

/**
 * @brief AnnotationService::handleQueue works through Queue, calls makeVEPrequest for every queue element
 */
void AnnotationService::handle_queue()
{
    if (!queue.isEmpty())
    {
        currentIndex = queue.dequeue();
        makeVEPrequest(*this->manager, annoTableObj->getLine(currentIndex));
    }
}
