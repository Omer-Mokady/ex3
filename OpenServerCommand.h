//
// Created by gal on 22/12/2019.
//

#ifndef EX3_NEW__OPENSERVERCOMMAND_H_
#define EX3_NEW__OPENSERVERCOMMAND_H_
#include "Command.h"
class OpenServerCommand : public Command {
 public:
  OpenServerCommand();
  OpenServerCommand(string portNumber);
  void readFile(const int i);
  int execute(vector<string>::iterator);
  ~OpenServerCommand() {};
  int openSocket();
  void listener();
 private:
  int serverSocketNumber;
  int clientSocketNumber;
  int portNumber;
  string ipNumber = "0.0.0.0";
};

#endif //EX3_NEW__OPENSERVERCOMMAND_H_
