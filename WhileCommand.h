//
// Created by omer on 27/12/2019.
//

#ifndef EX3_NEW__WHILECOMMAND_H_
#define EX3_NEW__WHILECOMMAND_H_
#include "ConditionParser.h"

class WhileCommand : public ConditionParser {
 public:
  /**
   * constructor
   */
  WhileCommand();
/**
 * perform the relevant actions need to be execute on each command.
 * @param it iterator of commands from the lexer.
 * @return the number of jumps we need to do (=the number of arguments we will use in this execute function)
 * to get the next command in the lexer.
 */
  int execute(vector<string>::iterator);

};

#endif //EX3_NEW__WHILECOMMAND_H_
