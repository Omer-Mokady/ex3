//
// Created by gal on 25/12/2019.
//

#include "PrintCommand.h"
PrintCommand::PrintCommand() {

}
int PrintCommand::execute(vector<string>::iterator it) {
  cout << "in PrintCommand execute....." << endl;
  string msgToPrint = *(it + 1);
  if (msgToPrint.at(0) == '"' && msgToPrint.at(msgToPrint.length() - 1) == '"') {
    msgToPrint = msgToPrint.substr(1, msgToPrint.length() - 2);
  }
  cout << msgToPrint << endl;
  return 2;
}