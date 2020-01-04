//
// Created by gal on 25/12/2019.
//

#ifndef EX3_NEW__PRINTCOMMAND_H_
#define EX3_NEW__PRINTCOMMAND_H_
#include "Command.h"
#include <iostream>
#include <string>
class PrintCommand : public Command {
 public:
  /**
   * empty constructor.
   */
  PrintCommand();
  /**
   * default distructor.
   */
  ~PrintCommand() {};
  /**
   * gets a string or expression from the fly.txt file.
   * if it's a string - printing it.
   * if it's an expression - interpreting it and than printing it.
   * @param it described in Command.h.
   * @return described in Command.h.
   */
  int execute(vector<string>::iterator it);
};

#endif //EX3_NEW__PRINTCOMMAND_H_
