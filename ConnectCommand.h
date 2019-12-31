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
   * creates a socket for connecting to the simulator on a given ip number and port number.
   * @param it described in Command.h.
   * @return described in Command.h.
   */
  int execute(vector<string>::iterator it);

  /**
 * a thread for opening socket so it's will work as a blocking call.
 * @return -1 or -2 if something went wrong, 0 otherwise.
 */
  int openSocket();

  /**
   * a Thread for sending information to the simulator.
   * it is sending info only if we are looking on variable with direction "->".
   * it reads a string from the server, split it by the '\n' delimiter.
   * then it saves the part before the delimiter in one place, and the part beyond it in second place.
   * then process the first part and repeat such that every time we will have a buffer with 36 values to work on.
   */
  void sender();
 private:
  string ipNumber;
  int clientSocketNumber;
  int serverPortNumber;
};

#endif //EX3_NEW__CONNECTCOMMAND_H_