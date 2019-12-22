//
// Created by gal on 19/12/2019.
//

#ifndef EX3_NEW__COMMAND_H_
#define EX3_NEW__COMMAND_H_
#include <string>
#include <map>
using namespace std;
class Command {
 public:
  virtual int execute() = 0;
  virtual ~Command() {};
 protected:
//  map<string,
};

#endif //EX3_NEW__COMMAND_H_
