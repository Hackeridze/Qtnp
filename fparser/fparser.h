#ifndef FPARSER_H
#define FPARSER_H

#include "muparser/muParser.h"
#include <string>

using namespace std;
using namespace mu;

class QtnpParser
{
private:
    Parser p;
public:
    QtnpParser();
    void setE(string str);
    double getR(value_type x);
};

#endif // FPARSER_H
