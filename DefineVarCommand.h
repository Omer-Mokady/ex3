//
// Created by gal on 22/12/2019.
//

#ifndef EX3_NEW__DEFINEVARCOMMAND_H_
#define EX3_NEW__DEFINEVARCOMMAND_H_
#include "Command.h"
#include <iostream>
class DefineVarCommand : public Command {
 public:
  int execute();
};

#endif //EX3_NEW__DEFINEVARCOMMAND_H_