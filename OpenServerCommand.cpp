//
// Created by gal on 22/12/2019.
//

#include "OpenServerCommand.h"
#include "Command.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <iostream>
#include <fstream>
#include "Expression.h"
#include "Interpreter.h"
OpenServerCommand::OpenServerCommand(string port) {
  Expression *e;
  Interpreter *i = new Interpreter();
  e = i->interpret(port);
  this->portNumber = (int) e->calculate();
}

int OpenServerCommand::execute() { //starting a thread where the server is listening on.

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

  int client_socket = accept((socketfd), ((struct sockaddr *) &address), ((socklen_t *) &address));

  if (client_socket == -1) {
    cerr << "Error with accepting client" << endl;
    return -4;
  }

  cout << "ready for listenening" << endl;

  thread reader([client_socket, this] { readFile(client_socket); });
  reader.join();
  cout << "after thread" << endl;
  return 2;
}

void OpenServerCommand::readFile(const int i) { //use as input function to the thread opening in execute of OpenServerCommand.
//  char line[1024] = {0};
//  int val = read(i, line, 1024);
//  cout << line << endl;

  //  vector<double> xmlValues(36);
//  ifstream xmlFile;
//  xmlFile.open("");
//  string fileLine;
//  if (xmlFile.is_open()) {
//    for (std::string line; getline(xmlFile, line);) {
//
//    }
//  }
//
  char line[1024] = {0};
  while (strcmp(line, "^]")) {
    int val = read(i, line, 1024);
    cout << line << endl;
  }

}