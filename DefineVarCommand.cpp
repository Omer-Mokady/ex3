//
// Created by gal on 22/12/2019.
//

#include "DefineVarCommand.h"
#include "Var.h"
#include "Singleton.h"
using namespace std;


DefineVarCommand::DefineVarCommand(){

}

int DefineVarCommand::execute(vector<string>::iterator it) {
  string strValue, tempStr;
  float floatValue = 0;
  Singleton* s = Singleton::getInstance();



  // var not exist in the symbolTable.
  if(*it == "var") {
    if(*(it+2)=="->" || *(it+2) == "<-") {
      string sim = *(it+4);
      if(sim.at(0)=='"'&& sim.at(sim.length()-1)=='"') {
        sim=sim.substr(1,sim.length()-2);
      }
      s->symbolTable[*(it+1)]=pair<string,float>(sim,0);

      if(s->simToIndexTable.find(sim) == s->simToIndexTable.end()) {
          cout << "can't find on sim map, the sim: " << sim << endl;
      }
      s->indexToVarTable[s->simToIndexTable[sim]]->direction = *(it+2);
      return 5;
      //sim->index. index->var
    } else if(*(it+2)=="=") {
      // there is no sim!!
      strValue = *(it+3);
      // make string into float number
      try {
        Expression *exp = nullptr;
        exp = s->interpreter->interpret(strValue);
        floatValue = exp->calculate();
      } catch (const char *e) {
        std::cout << e << std::endl;
      }
      s->symbolTable[*(it+1)]=pair<string,float>("", floatValue);
      // update global iterpreter
      tempStr = *(it+1) + "=" + *(it+3);
      s->interpreter->setVariables(tempStr);
      return 4;
    }
  // var exist in the symbolTable.
  } else {
    // get value from somrething that exist.
//    to update Simtable value and to update interpreter.


  }



  return 3;
}