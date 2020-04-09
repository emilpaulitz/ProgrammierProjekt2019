#ifndef VCFTABLE_H
#define VCFTABLE_H

#include "vcfline.h"

#include <QByteArrayList>
#include <QList>
#include <string>

class VCFtable
{
private:
    // values
    QList<VCFline> listOfLines;
    QString header;

public:
    static bool invalidChrNum;

    // constructor
    VCFtable();

    //getter/setter
    QString getHeader() const;
    void setHeader(const QString &value);

    // methods
    QList<VCFline> getLines();
    VCFline &getLine(int i);
    void addLine(VCFline &newline);
    void parse(std::string filename);
    int getNumLines() const;
};

#endif // VCFTABLE_H
