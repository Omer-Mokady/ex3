//
// Created by omer on 28/12/2019.
//

#ifndef EX3_NEW__IFCOMMAND_H_
#define EX3_NEW__IFCOMMAND_H_
#include "ConditionParser.h"

class IfCommand : public ConditionParser {
 public:
  /**
   * constructor
   */
  IfCommand();
  int execute(vector<string>::iterator);
};

#endif //EX3_NEW__IFCOMMAND_H_
