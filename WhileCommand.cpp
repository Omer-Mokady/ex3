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
  Singleton* s = Singleton::getInstance();
  int counter = 3;
  list<Command*> CommandList = makeCommandList(it);
  list<Command*>::iterator listItr;
//  this->checkCondition(*(it+1));
    cout << "list size: " << CommandList.size() << endl;
    while(checkCondition(*(it+1))) {
      cout << "start while from start" << endl;
      cout << "value in rpm" << s->indexToVarTable[35]->value << endl;

      listItr = CommandList.begin();
      counter = 3;
      // run over the scope
      while(*(it+counter) != "}") {
        // if iterator is on command
        if ((*(it + counter) == ",") && (*(it + counter + 1) != "}")) {
          Command* c = *(listItr);
          cout << "execute command: " << *(it + counter + 1) << endl;

          counter+= c->execute(it+counter+1);
          advance(listItr, 1);
          if(listItr == CommandList.end()) {
            cout << "we don't have more commands on the list: " << endl;
          }
        } else {
          counter++;
        }
      }
    }
    int stepsToEnd = 0;
    while(*(it+stepsToEnd) != "}") {
      stepsToEnd++;
    }
  return stepsToEnd+1;
}
