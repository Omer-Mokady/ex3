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
  // static instance
  static Singleton *instance;
  /**
   * Constructor
   * initialize commandsMap, indexToVar and simToIndex maps.
   */
  Singleton();
 public:
  // map with all the Vars by order
  map<int, Var *> indexToVarTable;
  // map with a value, which is the indexToVarTable map's key, for each sim
  unordered_map<string, int> simToIndexTable;
  // Map with a number value and a sim for each fly.txt symbol
  unordered_map<string, pair<string, float>> symbolTable;
  // global interpreter for math expressions
  Interpreter *interpreter = new Interpreter();
  // all the command types on one list
  unordered_map<string, Command *> commandsMap;
  bool runTreads = true; //runs the threads.
  int clientSocketNumber; //runs the client socket.
  int serverSocketNumber; //runs the server socket.
  static Singleton *getInstance();
};

#endif //EX3_NEW__SINGLETON_H_
