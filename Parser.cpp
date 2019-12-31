//
// Created by omer on 22/12/2019.
//

#include "Parser.h"
#include "Command.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "Singleton.h"
#include "PrintCommand.h"
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
  bool insideScope = false;
  ifstream fs;
  fs.open (address);
  string line, tempStr, separateSigns = " ,()\t";
  int firstIndex=0;
  unsigned int i = 0;
  vector<string> lexer;
  if(!fs){
    throw "can't open file";
  }
  // sync every line of the file
  while(getline(fs,line)) {
    // sync every letter from  the certain line
    for (i = 0; i < line.length(); i++) {
      if(line.at(i) == '}') {
        insideScope = false;
      }
      // if the line is "var" type
      if(line.find("var") == 0 && i+1<line.length()) {
        if ((line.at(i) == '<' && line.at(i + 1) == '-') || ((line.at(i) == '-' && line.at(i + 1) == '>'))) {
          // there is no 'space' before the arrow sign
          if (unsigned (firstIndex) != i) {
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
        insideScope = true;
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

        if(i>0) {
          if(line.at(i) == '=' && (line.at(i-1) != ' ')) {
            cout << "no space before '='" << endl;
            tempStr = line.substr(firstIndex, (i - firstIndex));
            if (!(tempStr.empty())) {
              lexer.push_back(tempStr);
            }
          }
        }
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
    if(insideScope) {
      lexer.push_back(",");
    }
    firstIndex = 0;
  } // end of while loop
  fs.close();
  return lexer;
}

//unordered_map<string, Command*> Parser::initCommandMap() {
//  unordered_map<string, Command*> commandsMap;
//  Command* connectCommandV = new ConnectCommand();
//  commandsMap["connectControlClient"] = connectCommandV;
//  Command* OpenServerCommandV = new OpenServerCommand();
//  commandsMap["openDataServer"] = OpenServerCommandV;
//  Command* defineVarCommandV = new DefineVarCommand();
//  commandsMap["var"] = defineVarCommandV;
////  Command* printCommandV = new PrintCommand();
////  commandsMap["Print"] = printCommandV;
//  //insert sleepCommand
//
//
//
//  return commandsMap;
//}



void Parser::runParser() {
  unsigned int index=0;
//  Singleton* s = Singleton::getInstance();
  vector<string> lexer= makeLexer(this->addressFile);
//  unordered_map<string, Command *> commandsMap = initCommandMap();
//  string str1 = lexer[3];
//  if(str1.at(0)=='"'&& str1.at(str1.length()-1)=='"') {
////    cout << "to deleteeeee: " << str1 << endl;
//    str1=str1.substr(1,str1.length()-2);
////    cout << "new word" << str1 << endl;
//
//
//  }
  Singleton* s = Singleton::getInstance();
//  unordered_map<string, Command *>::iterator cMapIt;
  vector<string>::iterator it = lexer.begin();
//  unordered_map<string, pair <string, float>>::iterator symbolTableIt = s->symbolTable.begin();;

//  std::advance( it, index );
//  /*
int counter=0;

  while(index<lexer.size()) {
    Command* c = nullptr;

    // to delete:
    if(lexer[index] == "{" || lexer[index] == "}") {
      cout << lexer[index] << endl;
      index++;
      advance( it, 1 );
    }

    cout << lexer[index] << endl;

    // check if Command is not in the map
    if(s->commandsMap.find(lexer[index]) == s->commandsMap.end()){
      // check if it is not command, it's a var which is already exists.
      // error - command is invalid
      if(s->symbolTable.find(lexer[index]) == s->symbolTable.end()) {
        cout << "command is invalid" << endl;

        break;
      // it's a var which is already exists.
      } else {
//        cout << "var that already exists" << endl;
        c = s->commandsMap["var"];
      }


    } else {
//      cout << "2" << endl;

      c = s->commandsMap.at(lexer[index]);
    }
//    cout << "3" << endl;

    counter=c->execute(it);
//    cout << "4" << endl;
    index+=counter;
    advance( it, counter );


//    cout << "iterator is: " << *it << endl;

//    cout << "end index: " << index << endl;

  }
//   */
//  cout << "check" << endl;



}
