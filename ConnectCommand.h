//
// Created by gal on 22/12/2019.
//

#ifndef EX3_NEW__CONNECTCOMMAND_H_
#define EX3_NEW__CONNECTCOMMAND_H_
#include "Command.h"
#include <iostream>

class ConnectCommand : public Command {
 public:
  /**
 * empty constructor.
 */
  ConnectCommand();

  /**
   * default distructor.
   */
  ~ConnectCommand() {};

  /**
 * @param it described in Command.h.
 * @return described in Command.h.
 */
  int execute(vector<string>::iterator);

  /**
 * this thread is opening socket so it's will work as a blocking call.
 * @return -1 or -2 if something went wrong, 0 otherwise.
 */
  int openSocket();

  /**
 * this Thread is sending information to the simulator.
 * it is sending info only if we are looking on variable with direction "->".
 */
  void sender();
 private:
  string ipNumber;
  int clientSocketNumber;
  int serverPortNumber;
};

#endif //EX3_NEW__CONNECTCOMMAND_H_
