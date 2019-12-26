//
// Created by gal on 22/12/2019.
//

#include "ConnectCommand.h"
using namespace std;
int ConnectCommand::execute(vector<string>::iterator it) {
  string value1 = *(it+1);
  string value2 = *(it+2);
  cout << "iteraor value1: " << value1 << endl;
  cout << "iteraor value2: " << value2 << endl;
  cout << "ConnectComannd execute" << endl;


  return 3;
}
ConnectCommand::ConnectCommand() {

}
