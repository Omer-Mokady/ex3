//
// Created by gal on 19/12/2019.
//

#ifndef EX3_NEW__COMMAND_H_
#define EX3_NEW__COMMAND_H_
#include <string>
#include <map>
#include <vector>
using namespace std;
class Command {
 public:
/**
 * perform the relevant actions need to be execute on each command.
 * @param it iterator of commands from the lexer.
 * @return the number of jumps we need to do (=the number of arguments we will use in this execute function)
 * to get the next command in the lexer.
 */
  virtual int execute(vector<string>::iterator it) = 0;
  virtual ~Command() {};
 protected:
  vector<string> lexerArray;
};

#endif //EX3_NEW__COMMAND_H_
