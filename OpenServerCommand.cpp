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

int OpenServerCommand::execute() { //here we will open a socket and connect to read from the simulator.

//  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
//  if (socketfd == -1) {
//    cerr << "Could not create a socket" << endl;
//    return -1;
//  }
//
//  sockaddr_in address;
//  address.sin_family = AF_INET;
//  address.sin_addr.s_addr = INADDR_ANY;
//  address.sin_port = htons(this->portNumber);
//
//  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
//    cerr << "Could not bind the socket to the ip" << endl;
//    return -2;
//  }
//
//  if (listen(socketfd, 5) == -1) {
//    cerr << "Error during listening command" << endl;
//    return -3;
//
//  }
//
//  int client_socket = accept((socketfd), ((struct sockaddr *) &address), ((socklen_t *) &address));
//
//  if (client_socket == -1) {
//    cerr << "Error with accepting client" << endl;
//    return -4;
//  }
  thread openServer([this] { openSocket(); });
  openServer.join(); //wait until someone (the simulator) will connect to the socket, and continue only afterward - therefore we need thread.join().
  thread listenThread([this] { listener(); });
  listenThread.join(); //read constantly, we wan it to run with the rest of the program - so we detach it.
//  thread reader([client_socket, this] { readFile(client_socket); });
//  reader.join();
  return 2; //return the number of elements + 1 to the parser.
}

//void OpenServerCommand::readFile(const int socketNumber) { //use as input function to the thread opening in execute of OpenServerCommand.
//  char line[1024] = {0};
//  int val = read(socketNumber, line, 1024);
//  cout << line << endl;
//
//  vector<double> values(36);
//
//  stringstream delimiterReader(line);
//  for (int i; delimiterReader >> i;) {
//    values.push_back(i);
//    if (delimiterReader.peek() == ',') {
//      delimiterReader.ignore();
//    }
//  }
//
//  for (int j = 0; j < 36; j++) {
//    cout << values.at(j) << ",";
//  }
//
////  ifstream xmlFile;
////  xmlFile.open("");
////  string fileLine;
////  if (xmlFile.is_open()) {
////    for (std::string line; getline(xmlFile, line);) {
////
////    }
////  }
////
////  while (true) {
////    stringstream delimiterReader(line);
////    for (int i; delimiterReader >> i;) {
////      values.push_back(i);
////      if (delimiterReader.peek() == ',') {
////        delimiterReader.ignore();
////      }
////    }
////    break;
////  }
//
//}

int OpenServerCommand::openSocket() { //this thread is opening a server and wait for connection.
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
  this->clientSocketNumber = client_socket;
  return 0;
}

void OpenServerCommand::listener() { //this is the thread that actually listening to the simulator and updating vector & map values accordingly.
  int socketNumber = this->clientSocketNumber;
  char line[1024] = {0};
  int val = read(socketNumber, line, 1024);
  cout << line << endl;

  vector<double> values(36);

  stringstream delimiterReader(line);
  for (int i; delimiterReader >> i;) {
    values.push_back(i);
    if (delimiterReader.peek() == ',') {
      delimiterReader.ignore();
    }
  }
}



