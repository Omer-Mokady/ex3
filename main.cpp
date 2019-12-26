#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Singleton.h"
#include "Parser.h"

using namespace std;


int main(int argc, char* argv[]) {






  Singleton* s = Singleton::getInstance();
//      cout << "value is: " << s->simToIndexTable["/sim/time/warp"] << endl;


  Parser pars = Parser(argv[1]);
  vector<string> lexer = pars.makeLexer(argv[1]);
  pars.runParser();
  return 0;
}