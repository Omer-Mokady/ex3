//
// Created by omer on 22/12/2019.
//

#include "Parser.h"
#include "Command.h"
#include "Singleton.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

Parser::Parser(string addressFile1) {
  this->addressFile = addressFile1;
}

string Parser::deleteSpaces(string str) {
  string::iterator endP = remove(str.begin(), str.end(), ' ');
  str.erase(endP, str.end());
  return str;
}

vector<string> Parser::makeLexer(string address) {
  bool commasFlag = false;
  bool insideScope = false;
  ifstream fs;
  fs.open(address);
  string line, tempStr, separateSigns = " ,()\t";
  int firstIndex = 0;
  unsigned int i = 0;
  vector<string> lexer;
  if (!fs) {
    throw "can't open file";
  }
  // sync every line of the file
  while (getline(fs, line)) {
    // sync every letter from  the certain line
    for (i = 0; i < line.length(); i++) {
      // if we got the end of the scope
      if (line.at(i) == '}') {
        insideScope = false;
      }
      // if the line is "var" type
      if (line.find("var") == 0 && i + 1 < line.length()) {
        if ((line.at(i) == '<' && line.at(i + 1) == '-') || ((line.at(i) == '-' && line.at(i + 1) == '>'))) {
          // there is no 'space' before the arrow sign
          if (unsigned(firstIndex) != i) {
            tempStr = line.substr(firstIndex, i - firstIndex);
            lexer.push_back(tempStr);
            firstIndex = i;
          }
          tempStr = line.substr(firstIndex, 2);
          firstIndex = i + 2;
          lexer.push_back(tempStr);
          continue;
        }
        // if the line is "while" type
      }
      if (line.find("while") == 0) {
        insideScope = true;
        lexer.push_back("while");
        firstIndex = 5;
        tempStr = deleteSpaces(line.substr(firstIndex, (line.length() - firstIndex)));
        if (tempStr.at(tempStr.length() - 1) == '{') {
          tempStr = tempStr.substr(0, (tempStr.length() - 1));
          lexer.push_back(tempStr);
          // don't push "{" to vector. it will happend in the end of the for loop
          firstIndex = line.length() - 1;
          break;
        }
      }
      // if the line is "while" type
      if (line.find("if") == 0) {
        insideScope = true;
        lexer.push_back("if");
        firstIndex = 2;
        tempStr = deleteSpaces(line.substr(firstIndex, (line.length() - firstIndex)));
        if (tempStr.at(tempStr.length() - 1) == '{') {
          tempStr = tempStr.substr(0, (tempStr.length() - 1));
          lexer.push_back(tempStr);
          // don't push "{" to vector. it will happend in the end of the for loop
          firstIndex = line.length() - 1;
          break;
        }
      }
      // if we got a quote
      if (line.at(i) == '"') {
        // if it's the opening commas
        if (commasFlag == false) {
          commasFlag = true;
          firstIndex = i;
          continue;
          // if it's the closing commas
        } else {
          commasFlag = false;
          tempStr = line.substr(firstIndex, i - firstIndex + 1);
          lexer.push_back(tempStr);
          firstIndex = i + 1;
          continue;
        }
        // if we got "=" symbol on the line
      } else if (line.at(i) == '=') {
        if (i > 0) {
          if (line.at(i) == '=' && (line.at(i - 1) != ' ')) {
            tempStr = line.substr(firstIndex, (i - firstIndex));
            if (!(tempStr.empty())) {
              lexer.push_back(tempStr);
            }
          }
        }
        firstIndex = i + 1;
        tempStr = deleteSpaces(line.substr(firstIndex, (line.length() - firstIndex)));
        lexer.push_back("=");
        lexer.push_back(tempStr);
        break;
        // default seperating strings
      } else if ((separateSigns.find(line.at(i)) != std::string::npos) && (commasFlag == false)) {
        tempStr = line.substr(firstIndex, (i - firstIndex));
        firstIndex = i + 1;
        if (!(tempStr.empty())) {
          lexer.push_back(tempStr);
        }
      } // end of for loop
    }
    // print last word on the line
    tempStr = line.substr(firstIndex, (i - firstIndex + 1));
    if (!(tempStr.empty())) {
      lexer.push_back(tempStr);
    }
    // check if we are still inside a scope
    if (insideScope) {
      lexer.push_back(",");
    }
    firstIndex = 0;
  } // end of while loop
  fs.close();
  return lexer;
}

void Parser::runParser() {
  unsigned int index = 0;
  // make Lexer
  vector<string> lexer = makeLexer(this->addressFile);
  Singleton *s = Singleton::getInstance();
  vector<string>::iterator it = lexer.begin();
  int counter = 0;
  // run over the Lexer values until the end of the lexer
  while (index < lexer.size()) {
    Command *c = nullptr;
    if (lexer[index] == "{" || lexer[index] == "}") {
      index++;
      advance(it, 1);
    }
    // check if Command is not in the map
    if (s->commandsMap.find(lexer[index]) == s->commandsMap.end()) {
      // check if it is not command, it's a var which is already exists.
      // error - command is invalid
      if (s->symbolTable.find(lexer[index]) == s->symbolTable.end()) {
        index++;
        advance(it, 1);
        continue;
        // it's a var which is already exists.
      } else {
        c = s->commandsMap["var"];
      }
    } else {
      c = s->commandsMap.at(lexer[index]);
    }
    // execute current command from the lexer
    counter = c->execute(it);
    index += counter;
    advance(it, counter);
  }
}