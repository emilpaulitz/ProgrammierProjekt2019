#include "vcfline.h"

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
    return chr;
}

void VCFline::setChr(const QString &value)
{
    chr = value;
}

int VCFline::getPos() const
{
    return pos;
}

void VCFline::setPos(int value)
{
    pos = value;
}

QString VCFline::getId() const
{
    return id;
}

void VCFline::setId(const QString &value)
{
    id = value;
}

QString VCFline::getRef() const
{
    return ref;
}

void VCFline::setRef(const QString &value)
{
    ref = value;
}

QString VCFline::getAlt() const
{
    return alt;
}

void VCFline::setAlt(const QString &value)
{
    alt = value;
}

int VCFline::getQual() const
{
    return qual;
}

void VCFline::setQual(int value)
{
    qual = value;
}

QString VCFline::getFilter() const
{
    return filter;
}

void VCFline::setFilter(const QString &value)
{
    filter = value;
}

QString VCFline::getInfo() const
{
    return info;
}

void VCFline::setInfo(const QString &value)
{
    info = value;
}

QString VCFline::getFormat() const
{
    return format;
}

void VCFline::setFormat(const QString &value)
{
    format = value;
}

QString VCFline::getAnno() const
{
    return anno;
}

void VCFline::setAnno(const QString &value)
{
    anno = value;
}


