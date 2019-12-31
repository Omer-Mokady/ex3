//
// Created by omer on 27/12/2019.
//

#include "WhileCommand.h"
#include "Singleton.h"
#include <iostream>
using namespace std;

WhileCommand::WhileCommand() {
}
int WhileCommand::execute(vector<string>::iterator it) {
  int counter = 3;
  list<Command*>::iterator listItr;
  list<Command*> CommandList = makeCommandList(it);
  cout << "created commandList in size: " << CommandList.size() << endl;
    while(checkCondition(*(it+1))) {
      cout << "start while from start" << endl;
      listItr = CommandList.begin();
      counter = 3;
      // run over the scope
      while(*(it+counter) != "}") {
        // if iterator is on command
        if ((*(it + counter) == ",") && (*(it + counter + 1) != "}")) {
          Command* c = *(listItr);
          cout << "execute command: " << *(it + counter + 1) << endl;
          // execute in command on the commandList
          counter+= c->execute(it+counter+1);
          advance(listItr, 1);
//          if(listItr == CommandList.end()) {
//            cout << "we don't have more commands on the list: " << endl;
//          }
        } else {
          counter++;
        }
      }
    }
    // calculate steps for the next command on the lexer
    int stepsToEnd = 0;
    while(*(it+stepsToEnd) != "}") {
      stepsToEnd++;
    }
  return stepsToEnd+1;
}