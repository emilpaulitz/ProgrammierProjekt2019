#ifndef TRANSCRIPTCONS_H
#define TRANSCRIPTCONS_H
#include <QString>
#include <QList>
#include <QJsonDocument>

class Transcriptcons

{
private:
QString transcript_id,impact, variant_allele,gene_symbole,gene_symbol_source,gene_id
    ,hgnc_id,strand,biotype,distance;

QList<QString> consequence_terms;

public:
    Transcriptcons();

    Transcriptcons(QString transcript_id,QString impact,QString variant_allele,QString gene_symbole,QString gene_symbol_source,
                    QString gene_id,QString hgnc_id,QString strand,QString biotype,QString distance,QList<QString> consequence_terms);



    QString getTranscript_id() const;
    void setTranscript_id(const QString &value);

    QString getImpact() const;
    void setImpact(const QString &value);

    QString getVariant_allele() const;
    void setVariant_allele(const QString &value);

    QString getGene_symbole() const;
    void setGene_symbole(const QString &value);

    QString getGene_symbol_source() const;
    void setGene_symbol_source(const QString &value);

    QString getGene_id() const;
    void setGene_id(const QString &value);

    QString getHgnc_id() const;
    void setHgnc_id(const QString &value);

    QString getStrand() const;
    void setStrand(const QString &value);

    QString getBiotype() const;
    void setBiotype(const QString &value);

    QString getDistance() const;
    void setDistance(const QString &value);

    QList<QString> getConsequence_terms() const;
    void setConsequence_terms(const QList<QString> &value);

    static QList<Transcriptcons> parse_TranscriptconsList(QJsonDocument doc);

    static QString print_Transcriptcons(Transcriptcons trans);

    static QString print_Transcriptcons(QList<Transcriptcons> trans);
};

#endif // TRANSCRIPTCONS_H
