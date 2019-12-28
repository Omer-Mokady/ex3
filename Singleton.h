//
// Created by omer on 24/12/2019.
//

#ifndef EX3_NEW__SINGLETON_H_
#define EX3_NEW__SINGLETON_H_
#include <string.h>
#include <unordered_map>
#include <map>
#include "Var.h"
#include "Interpreter.h"
#include "Command.h"
using namespace std;


class Singleton {
 private:

  /* Here will be the instance stored. */
  static Singleton* instance;

  /* Private constructor to prevent instancing. */
  Singleton();

 public:
  map<int, Var*> indexToVarTable;
  unordered_map<string, int> simToIndexTable;
  unordered_map<string, pair <string, float>> symbolTable;
  Interpreter *interpreter = new Interpreter();
  unordered_map<string, Command*> commandsMap;
  bool runTreads = true;


  /* Static access method. */
  static Singleton* getInstance();
};





#endif //EX3_NEW__SINGLETON_H_
