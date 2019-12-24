//
// Created by gal on 22/12/2019.
//

#ifndef EX3_NEW__CONNECTCOMMAND_H_
#define EX3_NEW__CONNECTCOMMAND_H_
#include "Command.h"
#include <iostream>

class ConnectCommand : public Command {
 public:
  ConnectCommand();
  ~ConnectCommand() {};
  int execute(vector<string>::iterator);

};

#endif //EX3_NEW__CONNECTCOMMAND_H_
