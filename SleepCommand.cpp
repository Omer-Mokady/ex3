//
// Created by gal on 25/12/2019.
//

#include "SleepCommand.h"
#include "Singleton.h"
SleepCommand::SleepCommand() {

}
int SleepCommand::execute(vector<string>::iterator it) {
  Singleton *instance = Singleton::getInstance();
  cout << "in sleepCommand execute....." << endl;
  string timeToSleep = *(it + 1);
  Expression *exp;
  Interpreter *i = instance->interpreter;
  try {
    exp = i->interpret(timeToSleep);
    int time = (int) exp->calculate();
//    this_thread::sleep_for(chrono::milliseconds(time));
  } catch (const char *e) {
    std::cout << e << std::endl;
  }
  cout << "sleep command finished..." << endl;
  return 2;
}