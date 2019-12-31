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

class SleepCommand : public Command {
 public:
  /**
 * empty constructor.
 */
  SleepCommand();
  /**
   * default distructor.
   */
  ~SleepCommand() {};
  /**
   * using the iterator, execute will make the current thread to sleep for it(=param) milliseconds.
   * @param it described in Command.h.
   * @return described in Command.h.
   */
  int execute(vector<string>::iterator it);

};

#endif //EX3_NEW__SLEEPCOMMAND_H_
