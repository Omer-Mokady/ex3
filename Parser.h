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
#include <unordered_map>
#include "Command.h"
#include "ConnectCommand.h"

using namespace std;

class Parser {
 private:

  string addressFile;

 public:
  Parser(string addressFile);
  string deleteSpaces(string str);
  vector<string> makeLexer(string address);
  void runParser();
  unordered_map<string, Command *> initCommandMap();
};

#endif //EX3_NEW__PARSER_H_
