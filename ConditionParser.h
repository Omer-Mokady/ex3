//
// Created by omer on 25/12/2019.
//

#ifndef EX3_NEW__CONDITIONPARSER_H_
#define EX3_NEW__CONDITIONPARSER_H_
#include "Command.h"
#include <list>

class ConditionParser: public Command {
 protected:
  /**
   * making command list for the certain scope
   * @return command list for the certain scope
   */
  list<Command*> makeCommandList(vector<string>::iterator);
  /**
   * check equation's validation
   * @param condition  string equation
   * @return equation's validation
   */
  bool checkCondition(string condition);
 public:
//  virtual int execute(vector<string>::iterator);
};

#endif //EX3_NEW__CONDITIONPARSER_H_
