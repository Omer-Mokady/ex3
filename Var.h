//
// Created by omer on 23/12/2019.
//

#ifndef EX3_NEW__VAR_H_
#define EX3_NEW__VAR_H_
#include <string>

using namespace std;

class Var {
 private:

 public:
  Var(string name, string direction, string sim);
  Var(string sim);
  Var();


  string sim;
 string name;
  string direction;
 float value;
 bool hasValue = false;

  void setSim(string sim1);
};

#endif //EX3_NEW__VAR_H_
