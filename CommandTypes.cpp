//
// Created by gal on 19/12/2019.
//

#include "CommandTypes.h"
#include "Command.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

OpenServerCommand::OpenServerCommand(int port) {
  this->arguments = 1;
  this->portNumber = port;
}

OpenServerCommand::OpenServerCommand(string port) {

  this->arguments = 1;
  Expression *e;
  Interpreter *i = new Interpreter();
  e = i->interpret(port);
  this->portNumber = (int) e->calculate();
}
int OpenServerCommand::execute() {
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    cerr << "Could not create a socket" << endl;
    return -1;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(this->portNumber);
  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    cerr << "Could not bind the socket to the ip" << endl;
    return -2;
  }

  if (listen(socketfd, 5) == -1) {
    cerr << "Error during listening command" << endl;
    return -3;
  }

  int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
  if (client_socket == -1) {
    cerr << "Error with accepting client" << endl;
    return -4;
  }
  return 0;
}