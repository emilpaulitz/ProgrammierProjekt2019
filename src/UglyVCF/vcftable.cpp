#include "vcftable.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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

VCFline VCFtable::getLine(int i)
{
    return this->listOfLines.takeAt(i);
}

void VCFtable::addLine(VCFline newline)
{
    this->listOfLines.append(newline);
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
    int countCols = 0;

    while (getline(file, line))
    {
        // parse line
        if (line.find('#') == 0)
        {
            // add line to header
            setHeader(getHeader().append(QString::fromStdString(line)) + '\n');
        } else
            // add new line
        {
            istringstream stream(line);
            string token;
            countCols = 0;

            while (getline(stream, token, DELIM))
            {
                tokens.push_back(token);
                countCols++;
            }
            // fill tokens into line
            VCFline vcfline = VCFline();
            vcfline.setChr(QString::fromStdString(tokens[0]));
            vcfline.setPos(stoi(tokens[1]));
            vcfline.setId(QString::fromStdString(tokens[2]));
            vcfline.setRef(QString::fromStdString(tokens[3]));
            vcfline.setAlt(QString::fromStdString(tokens[4]));
            vcfline.setQual(stoi(tokens[5]));
            vcfline.setFilter(QString::fromStdString(tokens[6]));
            if (countCols >= 8)
            {
                vcfline.setFormat(QString::fromStdString(tokens[7]));
            }
            // append line to table
            this->addLine(vcfline);
        }
    }
}
