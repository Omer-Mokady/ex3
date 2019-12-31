//
// Created by gal on 22/12/2019.
//

#ifndef EX3_NEW__OPENSERVERCOMMAND_H_
#define EX3_NEW__OPENSERVERCOMMAND_H_
#include "Command.h"
class OpenServerCommand : public Command {
 public:
  /**
  * empty constructor.
  */
  OpenServerCommand();
  /**
 * default distructor.
 */
  ~OpenServerCommand() {};
  /**
* @param it described in Command.h.
* @return described in Command.h.
*/
  int execute(vector<string>::iterator);
  /**
* a thread for opening socket for listening(as server). it will work as a blocking call.
* @return -1, -2, -3 or -4 if something went wrong, 0 otherwise.
*/
  int openSocket();
  /**
* a Thread for getting information from the simulator and updates the main singelton object with the data.
* it is updating info only if we are looking on variable with direction "<-".
*/
  void listener();
 private:
  int clientSocketNumber;
  int portNumber;
};

#endif //EX3_NEW__OPENSERVERCOMMAND_H_
