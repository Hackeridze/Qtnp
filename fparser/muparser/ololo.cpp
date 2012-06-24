#include "muParser.h"
#include "muParserBase.h"


int main(int argc, char* argv[])
{
  using namespace mu;
  using namespace std;

  try
  {
    double fVal = 1;
    Parser p;
    p.DefineVar("a", &fVal); 
    p.SetExpr("sin(a)*pi+min(10,a)");
    std::cout << p.Eval() << endl;
  }
  catch (Parser::exception_type &e)
  {
    std::cout << e.GetMsg() << endl;
  }
  return 0;
}
