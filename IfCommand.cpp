//
// Created by omer on 28/12/2019.
//

#include "IfCommand.h"
#include <iostream>
using namespace std;
IfCommand::IfCommand() {

}
int IfCommand::execute(vector<string>::iterator it) {
  int counter = 3;
  if (checkCondition(*(it + 1))) {
    list<Command *> CommandList = makeCommandList(it);
    list<Command *>::iterator listItr;
    listItr = CommandList.begin();
    // run over the scope
    while (*(it + counter) != "}") {
      // if iterator is on command
      if ((*(it + counter) == ",") && (*(it + counter + 1) != "}")) {
        Command *c = *(listItr);
        counter += c->execute(it + counter + 1);
        advance(listItr, 1);
      } else {
        counter++;
      }
    }
  }
  // calculate steps for the next command on the lexer
  int stepsToEnd = 0;
  while (*(it + stepsToEnd) != "}") {
    stepsToEnd++;
  }
  return stepsToEnd + 1;
}