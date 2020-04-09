#ifndef VCFLINE_H
#define VCFLINE_H

#include <QString>
#include <QObject>
#include <Annotation.h>

class VCFline
{
private:
    QString dataFields[10];
    QString header, chr, pos, id, ref, alt, qual, filter, info, format, sample;
    Annotation anno;
    int size = 10;
    int index;

public:
    //constructor
    VCFline();

    // getter & setter
    QString getDataField(int i);
    int getSize();

    QString getHeader() const;
    void setHeader(const QString &value);
    QString getChr() const;
    void setChr(const QString &value);
    QString getPos() const;
    void setPos(QString value);
    QString getId() const;
    void setId(const QString &value);
    QString getRef() const;
    void setRef(const QString &value);
    QString getAlt() const;
    void setAlt(const QString &value);
    QString getQual() const;
    void setQual(QString value);
    QString getFilter() const;
    void setFilter(const QString &value);
    QString getInfo() const;
    void setInfo(const QString &value);
    QString getFormat() const;
    void setFormat(const QString &value);
    Annotation getAnno() const;
    Annotation & getAnno();
    void setAnno(const Annotation &value);
    QString getSample() const;
    void setSample(const QString &value);

    int getSize() const;
    void setSize(int value);
    int getIndex() const;
    void setIndex(const int value);

    // methods
    QString getChrNum();
    QString getHgvsNotation();
};

#endif // VCFLINE_H
