//
// Created by gal on 25/12/2019.
//

#include "SleepCommand.h"
SleepCommand::SleepCommand() {

}
int SleepCommand::execute(vector<string>::iterator it) {
  cout << "in sleepCommand execute....." << endl;
  /*
  string timeToSleep = *(it + 1);
  try {
    Expression *e;
    Interpreter *i = new Interpreter();
    e = i->interpret(timeToSleep);
    int time = (int) e->calculate();
    this_thread::sleep_for(chrono::milliseconds(time));
  } catch (const char *e) {
    std::cout << e << std::endl;
  }
   */
  return 2;
}
