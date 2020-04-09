#include "vcftable.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
bool VCFtable::invalidChrNum = false;

// constructor
VCFtable::VCFtable()
{
}

// getter and setter
QString VCFtable::getHeader() const
{
    return header;
}

void VCFtable::setHeader(const QString &value)
{
    header = value;
}

// methods
QList<VCFline> VCFtable::getLines()
{
    return this->listOfLines;
}

VCFline& VCFtable::getLine(int i)
{
    return this->listOfLines[i];
}


void VCFtable::addLine(VCFline& newline)
{
    this->listOfLines.append(newline);
}

int VCFtable::getNumLines() const {
    return this->listOfLines.size();
}

/* parse a vcf file to VCFtable and VCFline objects
 * @param filename of .vcf file
 */
void VCFtable::parse(string filename)
{
    string line;
    ifstream file(filename);
    vector<string> tokens;
    const char DELIM = '\t';

    while (getline(file, line))
    {
        // parse line
        if (line.find('#') == 0)
        {
            // add line to header
            setHeader(getHeader().append(QString::fromStdString(line)) + '\n');
        } else
        {
            // add new line
            istringstream stream(line);
            string token;
            tokens.clear();

            while (getline(stream, token, DELIM))
            {
                tokens.push_back(token);
            }
            // fill tokens into line
            VCFline& vcfline = *new VCFline();
           if ((QString::fromStdString(tokens[0]).size()) <= 5){
            vcfline.setChr(QString::fromStdString(tokens[0]));
            vcfline.setPos(QString::fromStdString(tokens[1]));
            vcfline.setId(QString::fromStdString(tokens[2]));
            vcfline.setRef(QString::fromStdString(tokens[3]));
            vcfline.setAlt(QString::fromStdString(tokens[4]));
            vcfline.setQual(QString::fromStdString(tokens[5]));
            vcfline.setFilter(QString::fromStdString(tokens[6]));
            vcfline.setInfo(QString::fromStdString(tokens[7]));
            if (tokens.size() >= 9)
            {
                vcfline.setFormat(QString::fromStdString(tokens[8]));
                if (tokens.size() >= 10)
                {
                    vcfline.setSample(QString::fromStdString(tokens[9]));
                }
            }

            // append line to table
            this->addLine(vcfline);
           }

           // not a valid chr1, chr2 ... notation
           else{
               invalidChrNum = true;
           }
        }
    }
}
