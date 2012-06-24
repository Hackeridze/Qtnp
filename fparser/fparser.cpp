#include "fparser.h"
#include <ostream>

using namespace mu;

QtnpParser::QtnpParser()
{
    Parser p;
};

void QtnpParser::setE(std::string str)
{
    p.SetExpr(str);
}

double QtnpParser::getR(value_type x)
{
    try
    {
        p.DefineVar("x",&x);
    }
    catch (Parser::exception_type &e)
    {
        std::cerr << e.GetMsg() << endl;
    }
    return p.Eval();
}
