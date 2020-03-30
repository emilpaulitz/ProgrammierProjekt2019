#ifndef ANNOTATION_H
#define ANNOTATION_H
#include <QString>
#include <QList>
#include <Frequencies.h>
#include <Transcriptcons.h>
#include "filterdialog.h"


class Annotation
{
private:
    QString most_severe_consequence,id;
    Frequencies frequencies;
    QList<Transcriptcons> transcriptcons;

public:

    Annotation();

    Annotation(QJsonDocument &doc);

    Annotation(Frequencies frequencies,QList<Transcriptcons> transcriptcons,QString id,QString most_severe_consequence);

    FilterDialog::Impact getConsequenceClass();
    QString getMost_severe_consequence() const;
    void setMost_severe_consequence(const QString &value);

    Frequencies getFrequencies() const;
    void setFrequencies(const Frequencies &value);

    QList<Transcriptcons> getTranscriptcons() const;
    void setTranscriptcons(const QList<Transcriptcons> &value);

    QString getId() const;
    void setId(const QString &value);

    static Annotation pars_Annotation(QJsonDocument &doc);

    bool isEmpty();

    QString print_Annotation();
};

#endif // ANNOTATION_H
