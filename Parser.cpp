//
// Created by omer on 22/12/2019.
//

#include "Parser.h"
#include "Command.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "Singleton.h"
#include <iostream>
#include <fstream>
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
  ifstream fs;
  fs.open (address);
  string line, tempStr, separateSigns = " ,()\t";
  int firstIndex=0, lastIndex=0, i=0;
  vector<string> lexer;
  if(!fs){
    throw "can't open file";
  }
  // sync every line of the file
  while(getline(fs,line)) {
    // sync every letter from  the certain line
    for (i = 0; i < line.length(); i++) {
      // if the line is "var" type
      if(line.find("var")==0 && i+1<line.length()) {
        if ((line.at(i) == '<' && line.at(i + 1) == '-') || ((line.at(i) == '-' && line.at(i + 1) == '>'))) {
          // there is no 'space' before the arrow sign
          if (firstIndex != i) {
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
      if(line.find("while")==0) {
        lexer.push_back("while");
        firstIndex=5;
        tempStr = deleteSpaces(line.substr(firstIndex, (line.length() - firstIndex)));
        if(tempStr.at(tempStr.length()-1) == '{') {
          tempStr = tempStr.substr(0, (tempStr.length() - 1));
          lexer.push_back(tempStr);
          // don't push "{" to vector. it will happend in the end of the for loop
          firstIndex = line.length() - 1;
          break;
        }
      }
      // if the line is "while" type
      if(line.find("if")==0) {
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
      if(line.at(i) == '"') {
        // if it's the opening commas
        if(commasFlag == false) {
          commasFlag = true;
          firstIndex = i;
          continue;
          // if it's the closing commas
        } else {
          commasFlag = false;
          tempStr = line.substr(firstIndex, i-firstIndex+1);
          lexer.push_back(tempStr);
          firstIndex = i+1;
          continue;
        }
        // if we got "=" symbol on the line
      } else if(line.at(i) == '=') {
        firstIndex = i+1;
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
    firstIndex = 0;
  }
  fs.close();
  return lexer;
}

unordered_map<string, Command*> Parser::initCommandMap() {
  unordered_map<string, Command*> commandsMap;
  Command* connectCommandV = new ConnectCommand();
  commandsMap["connectControlClient"] = connectCommandV;
  Command* OpenServerCommandV = new OpenServerCommand();
  commandsMap["openDataServer"] = OpenServerCommandV;
  Command* DefineVarCommandV = new DefineVarCommand();
  commandsMap["var"] = DefineVarCommandV;


  return commandsMap;
}



void Parser::runParser() {
  int index=0;
//  Singleton* s = Singleton::getInstance();
  vector<string> lexer= makeLexer(this->addressFile);
  unordered_map<string, Command *> commandsMap = initCommandMap();
//  unordered_map<string, Command *>::iterator cMapIt;
  vector<string>::iterator it = lexer.begin();
//  std::advance( it, index );
//  /*
  while(index<lexer.size()) {
    cout << "index: " << index << endl;
    cout << lexer[index] << endl;
//    cMapIt = commandsMap.find(lexer[index]);
    if(commandsMap.find(lexer[index]) == commandsMap.end()){
      cout << "not in the map" << endl;
      break;

    }
    Command* c = commandsMap.at(lexer[index]);
    index+=c->execute(it);
    advance( it, index );
  }
//   */
  cout << "check" << endl;



}
