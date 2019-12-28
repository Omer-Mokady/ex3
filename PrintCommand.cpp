//
// Created by gal on 25/12/2019.
//

#include "PrintCommand.h"
#include "Expression.h"
#include "Interpreter.h"
#include "Singleton.h"
//#include <string>
PrintCommand::PrintCommand() {

}
int PrintCommand::execute(vector<string>::iterator it) {
  Singleton *instance = Singleton::getInstance(); // contains maps and boolean key for threads.
  cout << "in PrintCommand execute....." << endl;
  string msgToPrint = *(it + 1);
  if (msgToPrint.at(0) == '"' && msgToPrint.at(msgToPrint.length() - 1) == '"') { // *(it+1) = "string", print it.
    msgToPrint = msgToPrint.substr(1, msgToPrint.length() - 2);
    cout << msgToPrint << endl;
    if (strcmp(msgToPrint.c_str(), "waiting 2 minutes for gui") == 0) {

    }
  } else { //we have an expression we want to print - calculate it.
    string value = *(it + 1);
    cout << "value in iterator: " << value << endl;
    Expression *exp = nullptr;
    try {
      exp = instance->interpreter->interpret(value);
      cout << exp->calculate() << endl;
    } catch (const char *e) {
      cout << e << endl;
      cout << "thrown in print command of " << msgToPrint << endl;
    }
  }
//  if (strcmp(msgToPrint.c_str(), "done") == 0) {
//    instance->runTreads = false;
//  }
  return 2;
}
