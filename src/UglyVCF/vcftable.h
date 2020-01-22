#ifndef VCFTABLE_H
#define VCFTABLE_H

#include <QByteArrayList>
#include <QList>
#include <vcfline.h>
#include "vcfline.h"

class VCFtable
{
public:
    //
    QList<VCFline> listOfLines;
    QString name;
    // constructor
    VCFtable();

    // methods
    void parse(std::string filename);
};



#endif // VCFTABLE_H
