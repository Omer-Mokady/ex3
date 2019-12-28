//
// Created by omer on 25/12/2019.
//

#include "ConditionParser.h"
#include "Singleton.h"
#include <iostream>
using namespace std;

//int ConditionParser::execute(vector<string>::iterator it) {
//  string conditionType = *it;
//  string condition = *(it+1);
//  int counter = 3;
//  while(*(it+counter)=="}") {
//
//
//
//  }
//}
list<Command *> ConditionParser::makeCommandList(vector<string>::iterator it) {
  int counter=3;
  list<Command *> listCommands;
  Command* c;
  Singleton* s = Singleton::getInstance();
  while(*(it+counter) != "}") {
//    cout << "" << std::endl;
    if((*(it+counter) == ",") && (*(it+counter+1) != "}")) {
//      cout << "we got command: " << *(it+counter+1) << std::endl;
      // check if Command is not in the map
      if(s->commandsMap.find(*(it+counter+1)) == s->commandsMap.end()){
        // check if it is not command, it's a var which is already exists.
        // error - command is invalid
        if(s->symbolTable.find(*(it+counter+1)) == s->symbolTable.end()) {
          cout << "command is invalid!! - error" << endl;
          break;
          // it's a var which is already exists.
        } else {
          cout << "var that already exists" << endl;
          c = s->commandsMap["var"];
        }
      // command is in the map
      } else {
        c = s->commandsMap.at(*(it+counter+1));
      }
      // insert to list
      listCommands.push_back(c);
    }
    counter++;
  }
  cout << "we found } sign" << endl;
  return listCommands;
}
bool ConditionParser::checkCondition(string condition) {
  Singleton* s = Singleton::getInstance();
  Expression *exp = nullptr;
  string leftStr, rightStr, startP;
  float left=0, right=0;
  if(condition.find("<=") != std::string::npos) {
    leftStr = condition.substr(0, condition.find("<="));
    rightStr = condition.substr(condition.find("<=") + 2, condition.length()-(condition.find("<=")+2));
    try {
      exp = s->interpreter->interpret(leftStr);
      left = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    try {
      exp = s->interpreter->interpret(rightStr);
      right = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    cout << "left: " << left << endl;
    cout << "right: " << right << endl;
    return (left<=right);
  } else if(condition.find(">=") != std::string::npos) {
    leftStr = condition.substr(0, condition.find(">="));
    rightStr = condition.substr(condition.find(">=") + 2,
        condition.length()-(condition.find(">=")+2));
    try {
      exp = s->interpreter->interpret(leftStr);
      left = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    try {
      exp = s->interpreter->interpret(rightStr);
      right = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    cout << "left: " << left << endl;
    cout << "right: " << right << endl;
    return (left>=right);
  } else if(condition.find("==") != std::string::npos) {
    leftStr = condition.substr(0, condition.find("=="));
    rightStr = condition.substr(condition.find("==") + 2,
        condition.length()-(condition.find("==")+2));
    try {
      exp = s->interpreter->interpret(leftStr);
      left = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    try {
      exp = s->interpreter->interpret(rightStr);
      right = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    cout << "left: " << left << endl;
    cout << "right: " << right << endl;
    return (left==right);
  } else if(condition.find("!=") != std::string::npos) {
    leftStr = condition.substr(0, condition.find("!="));
    rightStr = condition.substr(condition.find("!=") + 2,
        condition.length()-(condition.find("!=")+2));
    try {
      exp = s->interpreter->interpret(leftStr);
      left = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    try {
      exp = s->interpreter->interpret(rightStr);
      right = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    cout << "left: " << left << endl;
    cout << "right: " << right << endl;
    return (left!=right);
  } else if(condition.find("<") != std::string::npos) {
    leftStr = condition.substr(0, condition.find("<"));
    rightStr = condition.substr(condition.find("<") + 1,
        condition.length()-(condition.find("<")+1));
    try {
      exp = s->interpreter->interpret(leftStr);
      left = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    try {
      exp = s->interpreter->interpret(rightStr);
      right = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    cout << "left: " << left << endl;
    cout << "right: " << right << endl;
    return (left<right);
  } else if(condition.find(">") != std::string::npos) {
    leftStr = condition.substr(0, condition.find(">"));
    rightStr = condition.substr(condition.find(">") + 1,
                                condition.length()-(condition.find(">")+1));
    try {
      exp = s->interpreter->interpret(leftStr);
      left = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    try {
      exp = s->interpreter->interpret(rightStr);
      right = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
    cout << "left: " << left << endl;
    cout << "right: " << right << endl;
    return (left>right);
  }







  cout << "problem on conditon, can't find operator: " << endl;
  return false;
}
