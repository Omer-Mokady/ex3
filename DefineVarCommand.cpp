//
// Created by gal on 22/12/2019.
//

#include "DefineVarCommand.h"
#include "Var.h"
using namespace std;


DefineVarCommand::DefineVarCommand(){

}

int DefineVarCommand::execute(vector<string>::iterator it) {
  if(*(it+2)=="->" || *(it+2) == "<-") {
    cout << "we got sim" << endl;
//    Var* newVar = new Var();



  }

  return 0;
}