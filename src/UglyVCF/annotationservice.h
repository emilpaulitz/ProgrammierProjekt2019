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

public:
    AnnotationService();

    void setupAnnoService(VCFtable* table);
    // status methods
    bool isPullingAllAnnos() const;
    int getQueueSize() const;

    // 'core' annotation methods
    void pullAnnotations(VCFtable &table);
    void makeSingleRequest(int row);

private:
    void makeVEPrequest(QNetworkAccessManager &manager, VCFline &line);

    QQueue<int> getQueue() const;
    void startQueue();

    void setAnnoFromDB(int row, QString& hgvs);

    // needed because of inheritance of QObject to use Signals & Slots
    AnnotationService(AnnotationService& rhs) = delete;

private slots:
    void setAnnoFromVEP(QNetworkReply *reply);
    void handle_queue();

signals:
    void queueFinished();
    void annotation_set(int index);
    void no_connection();
};

#endif // ANNOTATIONSERVICE_H
