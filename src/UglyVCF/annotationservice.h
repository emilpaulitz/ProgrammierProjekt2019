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
    AnnotationService(VCFtable* table);

    // methods
    void makeVEPrequest(QNetworkAccessManager &manager, VCFline &line);
    void makeVEPrequest(QString notation);
    void pullAnnotations(VCFtable &table);

    void makeSingleRequest(int row);


    // needed for inheritance of QObject to use Signals & Slots
    AnnotationService(AnnotationService& rhs) = delete;

    QQueue<int> getQueue() const;
    bool isPullingAllAnnos() const;
    int getQueueSize() const;

public slots:
    void set_annotation(QNetworkReply *reply);
    void handle_queue();

signals:
    void annotation_set(int index);
    void no_connection();
};

#endif // ANNOTATIONSERVICE_H
