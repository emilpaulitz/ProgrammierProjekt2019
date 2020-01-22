#include "vcftable.h"
#include <fstream>
#include<sstream>

using namespace std;

VCFtable::VCFtable()
{
}

void VCFtable::parse(string filename)
{
    // create new VCFtable
    VCFtable table = VCFtable();

    string line;
    ifstream file;
    file.open(filename);

    while (getline(file, line)) {
        // parse line

    }
}
