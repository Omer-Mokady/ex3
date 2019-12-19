//
// Created by gal on 19/12/2019.
//

#ifndef EX3_NEW__COMMANDTYPES_H_
#define EX3_NEW__COMMANDTYPES_H_
#include "Command.h"
#include <string>
#include <thread>
#include "Expression.h"
#include "Interpreter.h"
using namespace std;
class CommandTypes {
};

class OpenServerCommand : public Command {
 public:
  OpenServerCommand(int portNumber);
  OpenServerCommand(string portNumber);
  int calculate(string expression); //need to import all ex1.
  int execute();
  ~OpenServerCommand() {};
 private:
  int portNumber;
  string ipNumber = "0.0.0.0";
};

#endif //EX3_NEW__COMMANDTYPES_H_