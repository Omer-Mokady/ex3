#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Parser.h"

using namespace std;


int main(int argc, char* argv[]) {
  Parser pars = Parser(argv[1]);
  vector<string> lexer = pars.makeLexer(argv[1]);
  pars.runParser();
  return 0;
}