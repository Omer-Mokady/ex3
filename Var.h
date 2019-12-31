//
// Created by omer on 23/12/2019.
//

#ifndef EX3_NEW__VAR_H_
#define EX3_NEW__VAR_H_
#include <string>

using namespace std;

class Var {
 public:
  // constructors
  Var(string name, string direction, string sim);
  Var(string sim);
  Var();
  // sim
  string sim;
  //symbol name
  string name;
  // communication direction
  string direction;
  // value
  float value;
  // indicates if exist current value
  bool hasValue = false;
  // indicates if the value had updated lately
  bool hasUpdated = false;
  /**
   * Setter
   * @param sim1 sim
   */
  void setSim(string sim1);
};

#endif //EX3_NEW__VAR_H_
