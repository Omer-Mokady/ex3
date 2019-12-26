//
// Created by gal on 25/12/2019.
//

#ifndef EX3_NEW__SLEEPCOMMAND_H_
#define EX3_NEW__SLEEPCOMMAND_H_
#include "Command.h"
#include <thread>
#include <iostream>
#include "Expression.h"
#include "Interpreter.h"

class SleepCommand {
  SleepCommand();
  ~SleepCommand() {};
  int execute(vector<string>::iterator);
};

#endif //EX3_NEW__SLEEPCOMMAND_H_
