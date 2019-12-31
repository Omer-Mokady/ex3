//
// Created by gal on 25/12/2019.
//

#include "SleepCommand.h"
#include "Singleton.h"

SleepCommand::SleepCommand() {
}

int SleepCommand::execute(vector<string>::iterator it) {
  Singleton *instance = Singleton::getInstance();
  string timeToSleep = *(it + 1); // the time we need to sleep.
  Expression *exp;
  double time = 0;
  try {
    exp = instance->interpreter->interpret(timeToSleep);
    time = exp->calculate();
  } catch (const char *e) {
    std::cout << e << std::endl;
  }
  chrono::milliseconds duration((int) time);
  this_thread::sleep_for(duration); // make this thread sleep.
  return 2;
}