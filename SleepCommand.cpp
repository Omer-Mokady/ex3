//
// Created by gal on 25/12/2019.
//

#include "SleepCommand.h"
#include "Singleton.h"
/**
 * empty constructor.
 */
SleepCommand::SleepCommand() {
}

/**
 * @param it described in Command.h.
 * @return described in Command.h.
 */
int SleepCommand::execute(vector<string>::iterator it) {
  Singleton *instance = Singleton::getInstance();
  string timeToSleep = *(it + 1); // time we need to sleep.
  Expression *exp;
  double time = 0;
  try {
    exp = instance->interpreter->interpret(timeToSleep);
    time = exp->calculate();
  } catch (const char *e) {
    std::cout << e << std::endl;
  }
  chrono::milliseconds duration((int) time);
  this_thread::sleep_for(duration);
  return 2;
}