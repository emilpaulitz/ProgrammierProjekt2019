#ifndef VCFLINE_H
#define VCFLINE_H


#include <string>
#include <QString>

class VCFline
{
private:
    QString header;
    QString chr;
    int pos = 0;
    QString id;
    QString ref;
    QString alt;
    int qual = 0;
    QString filter;
    QString info;
    QString format;
    QString anno;

    //const int size = 10;

public:
    VCFline();

    QString getHeader() const;
    void setHeader(const QString &value);
    QString getChr() const;
    void setChr(const QString &value);
    int getPos() const;
    void setPos(int value);
    QString getId() const;
    void setId(const QString &value);
    QString getRef() const;
    void setRef(const QString &value);
    QString getAlt() const;
    void setAlt(const QString &value);
    int getQual() const;
    void setQual(int value);
    QString getFilter() const;
    void setFilter(const QString &value);
    QString getInfo() const;
    void setInfo(const QString &value);
    QString getFormat() const;
    void setFormat(const QString &value);
    QString getAnno() const;
    void setAnno(const QString &value);
};

#endif // VCFLINE_H
