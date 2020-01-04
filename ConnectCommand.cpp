//
// Created by gal on 22/12/2019.
//

#include "ConnectCommand.h"
#include <thread>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Singleton.h"
#include <unistd.h>

/**
 * empty constructor.
 */
using namespace std;

ConnectCommand::ConnectCommand() {

}

int ConnectCommand::execute(vector<string>::iterator it) {
  Singleton *instance = Singleton::getInstance();
  string value1 = *(it + 1); //ip
  if (value1.at(0) == '"' && value1.at(value1.length() - 1) == '"') { //remove extra ' " ' symbols from the ip address.
    value1 = value1.substr(1, value1.length() - 2);
  }
  this->ipNumber = value1;
  string value2 = *(it + 2); //port number
  Expression *port = nullptr;
  try {
    port = instance->interpreter->interpret(value2);
    this->serverPortNumber = (int) port->calculate();
  } catch (const char *e) {
    cout << e << endl;
    cout << "exception in ConnectCommand.execute()" << endl;
  }

  thread openServer([this] { openSocket(); });
  openServer.join(); //wait until the simulator connect to the socket, and continue only afterward.
  thread listenThread([this] { sender(); });
  listenThread.detach(); // runs in the background when the the program is running.
  return 3;
}

int ConnectCommand::openSocket() {
  Singleton *instance = Singleton::getInstance();
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    cerr << "Could not create a socket" << endl;
    return -1;
  }
  this->clientSocketNumber = client_socket;
  instance->clientSocketNumber = client_socket;
  sockaddr_in address;
  const char *validIP = this->ipNumber.c_str();
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(validIP);
  address.sin_port = htons(this->serverPortNumber);
  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
    return -2;
  }
  return 0;
}

void ConnectCommand::sender() {
  Singleton *instance = Singleton::getInstance();
  map<int, Var *>::iterator it; // creates iterator based on IndexToVarTable map from Singleton.
  it = instance->indexToVarTable.begin();
  while (instance->runTreads) { // run as long as the boolean Singleton flag is true.
    while (it != instance->indexToVarTable.end()) { // iterate all over the singleton map.
      if (strcmp((*it).second->direction.c_str(), "->") == 0 && (*it).second->hasValue == true
          && (*it).second->hasUpdated == true) {
        (*it).second->hasValue = false;
        ostringstream valueToSend;
        valueToSend << (*it).second->value; // turning the float value to string stream.
        string setCommand = "set ";
        string sim = (*it).second->sim;
        string whiteSpace = " ";
        string valueAsStr = valueToSend.str();
        valueAsStr.append("\r\n");
        string final_message = "";
        final_message.append(setCommand); // "set "
        final_message.append(sim); // path
        final_message.append(whiteSpace); // " "
        final_message.append(valueAsStr); // "value\r\n"
        char *msg = new char[final_message.length() + 1];
        strcpy(msg, final_message.c_str());
        int is_send =
            send(this->clientSocketNumber, msg, strlen(msg), 0); // trying to send the message to the simulator.
        if (is_send == -1) {
          if (instance->runTreads) {
            cout << "Error in sending message." << endl;
          }
        }
        delete[] msg;
      }
      advance(it, 1);
    }
    it = instance->indexToVarTable.begin();
  }
}