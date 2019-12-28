//
// Created by omer on 27/12/2019.
//

#ifndef EX3_NEW__WHILECOMMAND_H_
#define EX3_NEW__WHILECOMMAND_H_
#include "ConditionParser.h"

class WhileCommand : public ConditionParser {
 public:
  WhileCommand();
  int execute(vector<string>::iterator);

};

#endif //EX3_NEW__WHILECOMMAND_H_
