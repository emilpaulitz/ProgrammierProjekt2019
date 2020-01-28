#ifndef VCFLINE_H
#define VCFLINE_H


#include <string>
#include <QString>

class VCFline
{
private:
    QString dataFields[10];

    QString header, chr, pos, id, ref, alt, qual, filter, info, format, anno;

    //int size = -1;

public:
    VCFline();

    QString getDataField(int i);
    int getDataFieldsSize();

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
    QString getAnno() const;
    void setAnno(const QString &value);

    int getSize() const;
    void setSize(int value);


};

#endif // VCFLINE_H
