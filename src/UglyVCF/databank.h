#ifndef DATABANK_H
#define DATABANK_H

#include <QSqlDatabase>
#include <Annotation.h>

class databank
{
public:
    databank();

    static void connect();

    static void createTable();

    static bool searchDatabank(QString hgvs);

    static bool addRow(Annotation anno);

    static QString preparefreq(Frequencies freq,QString hgvs);

    static QString preparetranscons(QList<Transcriptcons> transcons,QString hgvs);

    static Annotation & retrieveAnno(QString hgvs);
};

#endif // DATABANK_H
