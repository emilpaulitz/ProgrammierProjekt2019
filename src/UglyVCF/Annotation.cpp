#include "Annotation.h"
#include "Transcriptcons.h"
#include "Frequencies.h"
#include "annotationservice.h"

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

Annotation::Annotation(QJsonDocument &doc){
    Annotation anno = parse_Annotation(doc);
    this->frequencies = anno.getFrequencies();
    this->transcriptcons = anno.getTranscriptcons();
    this->id = anno.getId();
    this->most_severe_consequence = anno.getMost_severe_consequence();
}

Annotation::Annotation(Frequencies frequencies, QList<Transcriptcons> transcriptcons, QString id, QString most_severe_consequence)
{
    this->frequencies = frequencies;
    this->transcriptcons = transcriptcons;
    this->id = id;
    this->most_severe_consequence = most_severe_consequence;
}

/**
 * @brief Annotation::getConsequenceClass
 * @return the highest impact a transcriptcons of this annotation
 */
FilterDialog::Impact Annotation::getConsequenceClass(){

    FilterDialog::Impact mostSevereImpact = FilterDialog::LASTIMPACT;

    // goes through all transcriptcons to compare their impact
    for (Transcriptcons transcript:this->getTranscriptcons())
    {
        if ((int) FilterDialog::stringToImpact(transcript.getImpact()) < (int) mostSevereImpact)
        {
            mostSevereImpact = FilterDialog::stringToImpact(transcript.getImpact());
        }
    }
    return mostSevereImpact;
}

/**
  returns the most servere consequence of this annotation
 * @brief pars_most_severe_consequence
 * @param doc
 * @return string
 */
QString parse_most_severe_consequence(QJsonDocument &doc){
    QString key = "most_severe_consequence";
    QJsonArray jarray = doc.array();
    QJsonObject jobject = jarray[0].toObject();

    QString restring = jobject.value(key).toString();

    return restring;
}

/**
  returns the id of this annotation
 * @brief parse_id
 * @param doc
 * @return
 */
QString parse_id(QJsonDocument &doc){

    QString key = "id";
    QJsonArray jarray = doc.array();
    QJsonObject jobject = jarray[0].toObject();

    QString restring = jobject.value(key).toString();

    return restring;
}

/**
  creates the annotation object out of a given QJson Document
 * @brief Annotation::parse_Annotation
 * @param doc
 * @return
 */
Annotation Annotation::parse_Annotation(QJsonDocument &doc){

    QString id = parse_id(doc);
    QString most_severe_consequence = parse_most_severe_consequence(doc);
    QList<Transcriptcons> transcriptcons =  Transcriptcons::parse_TranscriptconsList(doc);
    Frequencies frequencies = Frequencies::parse_Frequencies(doc);
    Annotation reAnno = Annotation(frequencies,transcriptcons,id,most_severe_consequence);

    return reAnno;
}

/**
  checks whether annotation is empty
 * @brief Annotation::isEmpty
 * @return
 */
bool Annotation::isEmpty(){
    return this->id.isEmpty();
}

/**
  creates a string out of the annotation in a nice format
 * @brief Annotation::print_Annotation
 * @return
 */
QString Annotation::print_Annotation(){
    QString printcons = Transcriptcons::print_allTranscriptcons(this->getTranscriptcons());
    QString printfrequencies = Frequencies::print_Frequencies(this->getFrequencies());
    QString id = this->getId();
    QString most_severe_consequence = this->getMost_severe_consequence();

    QString restring = "ANNOTATION RESULTS: \n"
                       "ID: "+id+ " \n\n"+
                       "Most severe consequences: "+most_severe_consequence+" \n\n"+
                       "Frequencies: "+printfrequencies+" \n\n"+
                       "Transcription consequences: \n"+printcons;

    return restring;

}


