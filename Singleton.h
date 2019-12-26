//
// Created by omer on 24/12/2019.
//

#ifndef EX3_NEW__SINGLETON_H_
#define EX3_NEW__SINGLETON_H_
#include <string.h>
#include <unordered_map>
#include "Var.h"
using namespace std;


class Singleton {
 private:

  /* Here will be the instance stored. */
  static Singleton* instance;

  /* Private constructor to prevent instancing. */
  Singleton();

 public:
  unordered_map<string, Var> simTable;
  unordered_map<string, Var> symbolTable;


  /* Static access method. */
  static Singleton* getInstance();
};





#endif //EX3_NEW__SINGLETON_H_
