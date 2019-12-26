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
  PrintCommand();
  ~PrintCommand() {};
  int execute(vector<string>::iterator);
};

#endif //EX3_NEW__PRINTCOMMAND_H_
