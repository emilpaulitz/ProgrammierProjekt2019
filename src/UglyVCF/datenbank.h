#ifndef DATABANK_H
#define DATABANK_H

#include <QSqlDatabase>
#include <Annotation.h>

class databank
{
public:
    databank();
};
static void connect();

static void createTable();

static bool searchDatabank(QString hgvs);

bool addRow(Annotation anno);

QString preparefreq(Frequencies freq,QString hgvs);

QString preparetranscons(QList<Transcriptcons> transcons,QString hgvs);

#endif // DATABANK_H
