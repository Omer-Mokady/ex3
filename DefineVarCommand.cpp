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
  string strValue, tempStr, strName, sim;
  float floatValue = 0;
  int index;
  Singleton* s = Singleton::getInstance();
  Expression *exp = nullptr;


  // var not exist in the symbolTable.
  if(*it == "var") {
    if(*(it+2)=="->" || *(it+2) == "<-") {
      sim = *(it+4);
      if(sim.at(0)=='"'&& sim.at(sim.length()-1)=='"') {
        sim=sim.substr(1,sim.length()-2);
      }
      s->symbolTable[*(it+1)]=pair<string,float>(sim,0);

      if(s->simToIndexTable.find(sim) == s->simToIndexTable.end()) {
          cout << "can't find on sim map, the sim: " << sim << endl;
      }
      s->indexToVarTable[s->simToIndexTable[sim]]->direction = *(it+2);
      s->indexToVarTable[s->simToIndexTable[sim]]->name = *(it+1);
      return 5;
      //sim->index. index->var
    } else if(*(it+2)=="=") {
      // there is no sim!!
      strValue = *(it+3);
      // delete spaces
      string::iterator endP = remove(strValue.begin(), strValue.end(), ' ');
      strValue.erase(endP, strValue.end());
      // make string into float number
      try {
//        Expression *exp = nullptr;
        std::cout << "strValue is: " << strValue << std::endl;

        exp = s->interpreter->interpret(strValue);
        floatValue = exp->calculate();
        std::cout << "floatValue is: " << floatValue << std::endl;
      } catch (const char *e) {
        std::cout << e << std::endl;
      }
      s->symbolTable[*(it+1)]=pair<string,float>("", floatValue);
      // update global iterpreter
      tempStr = *(it+1) + "=" + to_string(floatValue);
      s->interpreter->setVariables(tempStr);
      return 4;
    }
  // var exist in the symbolTable.
  } else {
    strName = *it;
    strValue = *(it+2);
    // get value from somrething that exist.
    //check if it exist
    if(s->symbolTable.find(strName) == s->symbolTable.end()) {

      cout << "var isn't exists in the symbolTable Map" << endl;
      //ff
    } else {
      // remove spaces from string value
      string::iterator endP = remove(strValue.begin(), strValue.end(), ' ');
      strValue.erase(endP, strValue.end());
      // get float value
      try {
//        Expression *exp = nullptr;
      exp = s->interpreter->interpret(strValue);
      floatValue = exp->calculate();
    } catch (const char *e) {
      std::cout << e << std::endl;
    }
      sim = s->symbolTable[strName].first;
      index = s->simToIndexTable[sim];
      // insert value in symbolTable to "second" value;
      s->symbolTable[strName].second = floatValue;
      // insert  value to Var
      s->indexToVarTable[index]->value = floatValue;
      s->indexToVarTable[index]->hasValue = true;
      // update global iterpreter
      tempStr = strName + "=" + to_string(floatValue);
      std::cout << "strName for interpreter is: "  << tempStr << std::endl;
      s->interpreter->setVariables(tempStr);
      return 3;
    }


  }



  return 3;
}