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
  list<Command*> CommandList = makeCommandList(it);
  list<Command*>::iterator listItr;
//  this->checkCondition(*(it+1));
  cout << "list size: " << CommandList.size() << endl;
  if(checkCondition(*(it+1))) {
    cout << "if is true. start from beginning" << endl;

    listItr = CommandList.begin();
//    counter = 3;
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
  return counter+1;

  return 0;
}