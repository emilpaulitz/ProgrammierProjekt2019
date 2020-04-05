#ifndef ANNOTATIONSERVICE_H
#define ANNOTATIONSERVICE_H

#include "vcfline.h"
#include "vcftable.h"

#include <QString>
#include <QObject>
#include <QNetworkReply>
#include <QQueue>

class AnnotationService : public QObject
{
    Q_OBJECT

private :
    // Queue of line indices (for tableObj)
    QQueue<int> queue;
    VCFtable * annoTableObj;
    QNetworkAccessManager * manager;

    int currentIndex;
    bool pullingAllAnnos = false;
    void setPullingAllAnnos(bool b);

public:
    AnnotationService();

    // methods
    void setupAnnoService(VCFtable* table);
    void makeVEPrequest(QNetworkAccessManager &manager, VCFline &line);
    void makeVEPrequest(QString notation);
    void pullAnnotations(VCFtable &table);

    void makeSingleRequest(int row);
    void setAnnoFromDB(int row, QString& hgvs);

    // needed for inheritance of QObject to use Signals & Slots
    AnnotationService(AnnotationService& rhs) = delete;

    QQueue<int> getQueue() const;
    bool isPullingAllAnnos() const;
    int getQueueSize() const;
    void startQueue();

private slots:
    void setAnnoFromVEP(QNetworkReply *reply);
    void handle_queue();

signals:
    void queueFinished();
    void annotation_set(int index);
    void no_connection();
};

#endif // ANNOTATIONSERVICE_H
