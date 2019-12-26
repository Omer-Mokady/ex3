//
// Created by omer on 25/12/2019.
//

#ifndef EX3_NEW__CONDITIONPARSER_H_
#define EX3_NEW__CONDITIONPARSER_H_
#include "Command.h"
#include <list>

class ConditionParser: public Command {
 protected:
  list<Command*> commandList;
 public:
  int execute(vector<string>::iterator);


};

#endif //EX3_NEW__CONDITIONPARSER_H_
