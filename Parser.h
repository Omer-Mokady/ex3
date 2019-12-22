//
// Created by omer on 22/12/2019.
//

#ifndef EX3_NEW__PARSER_H_
#define EX3_NEW__PARSER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Parser {
 private:

  string addressFile;

 public:
  Parser(string addressFile);
  string deleteSpaces(string str);
  vector<string> makeLexer(string address);

};

#endif //EX3_NEW__PARSER_H_
