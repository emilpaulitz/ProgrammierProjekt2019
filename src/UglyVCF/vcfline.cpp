#include "vcfline.h"
#include <QString>

QString VCFline::getDataField(int i)
{
    return dataFields[i];
}

// TODO: this method somehow returns 4, but should return 10 (size of array)
int VCFline::getDataFieldsSize()
{
    return dataFields->size();
}

VCFline::VCFline()
{
}

QString VCFline::getHeader() const
{
    return header;
}

void VCFline::setHeader(const QString &value)
{
    header = value;
}

QString VCFline::getChr() const
{
    return dataFields[0];
}
void VCFline::setChr(const QString &value)
{
    dataFields[0] = value;
}

QString VCFline::getPos() const
{
    return dataFields[1];
}
void VCFline::setPos(QString value)
{
    dataFields[1] = value;
}

QString VCFline::getId() const
{
    return dataFields[2];
}
void VCFline::setId(const QString &value)
{
    dataFields[2] = value;
}

QString VCFline::getRef() const
{
    return dataFields[3];
}
void VCFline::setRef(const QString &value)
{
    dataFields[3] = value;
}

QString VCFline::getAlt() const
{
    return dataFields[4];
}
void VCFline::setAlt(const QString &value)
{
    dataFields[4] = value;
}

QString VCFline::getQual() const
{
    return dataFields[5];
}
void VCFline::setQual(QString value)
{
    dataFields[5] = value;
}

QString VCFline::getFilter() const
{
    return dataFields[6];
}
void VCFline::setFilter(const QString &value)
{
    dataFields[6] = value;
}

QString VCFline::getInfo() const
{
    return dataFields[7];
}
void VCFline::setInfo(const QString &value)
{
    dataFields[7] = value;
}

QString VCFline::getFormat() const
{
    return dataFields[8];
}
void VCFline::setFormat(const QString &value)
{
    dataFields[8] = value;
}

QString VCFline::getSample() const
{
    return dataFields[9];
}
void VCFline::setSample(const QString &value)
{
    dataFields[9] = value;
}

QString VCFline::getAnno() const
{
    return anno;
}
void VCFline::setAnno(const QString &value)
{
    anno = value;
}


