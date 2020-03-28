#include "vcfline.h"
#include <QString>

QString VCFline::getDataField(int i)
{
    return dataFields[i];
}

int VCFline::getSize()
{
    return size;
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

Annotation VCFline::getAnno() const
{
    return anno;
}

Annotation &VCFline::getAnno()
{
    return anno;
}
void VCFline::setAnno(const Annotation &value)
{
    anno = value;
}

int VCFline::getIndex() const
{
    return index;
}
void VCFline::setIndex(const int value)
{
    index = value;
}

/**
 * @brief VCFline::getHgvsNotation returns HGVS Notation of the mutation in this VCFline
 * @return HGVS Notation of the mutation in this VCFline
 */
QString VCFline::getHgvsNotation()
{
    if (getAlt().length() == 1 && getRef().length() == 1)
    {
        // case SUBSTITUTION notation: CHR :g. POS REF>ALT (no spaces)
        // habe das ? abgeschnitten und in requst gelget
        QString notation = getChrNum() + ":g." + getPos() + getRef() + ">" + getAlt();
        return notation;
    }
    // INDEL notation covers Ins and Dels and yields the same results
    if (getAlt().length() > 1 || getRef().length() > 1){
        // case INDEL notation:
        QString endPos = QString::number(getPos().toInt() + getRef().length() - 1);
        QString notation = getChrNum() + ":g." + getPos() + "_" + endPos + getRef() + "delins" + getAlt();
        return notation;
    }
    return "";
}

// TODO: Improve error handling, e.g. show a warning
QString VCFline::getChrNum()
{
    if (this->getChr().left(3) == "chr"){
        QString num = this->getChr().remove(0,3);
        if (num == "X" || num == "23") return "x";
        if (num == "Y" || num == "24") return "y";
        if (num.length() <= 2) return num;
    }
    // not a valid chr1, chr2 ... notation
    return getChr();
}
