#include "Annotation.h"
#include "Transcriptcons.h"
#include "Frequencies.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QJsonArray>
#include <string>




QString Annotation::getMost_severe_consequence() const
{
    return most_severe_consequence;
}

void Annotation::setMost_severe_consequence(const QString &value)
{
    most_severe_consequence = value;
}


Frequencies Annotation::getFrequencies() const
{
    return frequencies;
}

void Annotation::setFrequencies(const Frequencies &value)
{
    frequencies = value;
}

QList<Transcriptcons> Annotation::getTranscriptcons() const
{
    return transcriptcons;
}

void Annotation::setTranscriptcons(const QList<Transcriptcons> &value)
{
    transcriptcons = value;
}

QString Annotation::getId() const
{
    return id;
}

void Annotation::setId(const QString &value)
{
    id = value;
}

Annotation::Annotation()
{

}

Annotation::Annotation(Frequencies frequencies, QList<Transcriptcons> transcriptcons, QString id, QString most_severe_consequence)
{
    this->frequencies = frequencies;
    this->transcriptcons = transcriptcons;
    this->id = id;
    this->most_severe_consequence = most_severe_consequence;
}

QString pars_most_severe_consequence(QJsonDocument doc){
    QString key = "most_severe_consequence";
    QJsonArray jarray = doc.array();
    QJsonObject jobject = jarray[0].toObject();

    QString restring = jobject.value(key).toString();

    return restring;

}

QString pars_id(QJsonDocument doc){

    QString key = "id";
    QJsonArray jarray = doc.array();
    QJsonObject jobject = jarray[0].toObject();

    QString restring = jobject.value(key).toString();

    return restring;
}

Annotation Annotation::pars_Annotation(QJsonDocument doc){

    QString id = pars_id(doc);
    QString most_severe_consequence = pars_most_severe_consequence(doc);
    QList<Transcriptcons> transcriptcons =  Transcriptcons::parse_totranscrictionlist(doc);
    Frequencies frequencies = Frequencies::pars_frequencies(doc);
    Annotation reAnno = Annotation(frequencies,transcriptcons,id,most_severe_consequence);

    return reAnno;
}

QString Annotation::print_Annotation(Annotation anno){
    QString printcons = Transcriptcons::printtranscons(anno.getTranscriptcons());
    QString printfrequencies = Frequencies::print_frequencies(anno.getFrequencies());
    QString id = anno.getId();
    QString most_severe_consequence = anno.getMost_severe_consequence();

    QString restring = "ANONTATION RESULTS: \n"
                       "ID: "+id+ " \n\n"+
                       "Most severe consecquences: "+most_severe_consequence+" \n\n"+
                       "Frequnecies: "+printfrequencies+" \n\n"+
                       "Transcription consequences: \n"+printcons;


    return restring;

}

