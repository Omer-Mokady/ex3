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
  // fly.txt file address
  string addressFile;
 public:
  /**
   * constractor
   * @param addressFile fly.txt file address
   */
  Parser(string addressFile);
  /**
   * delete string's spaces
   * @param str original string
   * @return the current string without spaces
   */
  string deleteSpaces(string str);
  /**
   * create lexer from the current file
   * @param address address to the certain file
   * @return lexer
   */
  vector<string> makeLexer(string address);
  /**
   * run the program.
   * create the lexer, run over it and execute all the commands.
   */
  void runParser();
};

#endif //EX3_NEW__PARSER_H_