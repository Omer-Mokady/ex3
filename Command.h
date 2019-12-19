//
// Created by gal on 19/12/2019.
//

#ifndef EX3_NEW__COMMAND_H_
#define EX3_NEW__COMMAND_H_

class Command {
 public:
  virtual int execute() = 0;
  virtual ~Command() {};
 protected:
  int arguments;
};

#endif //EX3_NEW__COMMAND_H_
