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
#include "Singleton.h"

OpenServerCommand::OpenServerCommand() {

}

int OpenServerCommand::execute(vector<string>::iterator it) { //starting a thread where the server is listening on.
  string value = *(it + 1);
  Expression *exp;
  Interpreter *i = new Interpreter();
  try {
    exp = i->interpret(value);
    this->portNumber = (int) exp->calculate();
  } catch (const char *e) {
    cout << e << endl;
    cout << "exception in OpenServerCommand.execute()" << endl;
  }

  thread openServer([this] { openSocket(); }); //create socket thread.s
  openServer.join(); //wait until someone (the simulator) will connect to the socket, and continue only afterward - therefore we need thread.join().
  thread listenThread([this] { listener(); }); // receiving data from simulator thread.
  listenThread.detach(); //read constantly, we wan it to run with the rest of the program - so we detach it.
  return 2; //return the number of elements + 1 to the parser.
}

int OpenServerCommand::openSocket() { //this thread is opening a server and wait for connection.
  Singleton *instance = Singleton::getInstance();
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
  instance->serverSocketNumber = client_socket;
  return 0;
}

void OpenServerCommand::listener() { //this is the thread that actually listening to the simulator and updating vector & map values accordingly.
  Singleton *instance = Singleton::getInstance();
  int socketNumber = this->clientSocketNumber;
  map<int, Var *>::iterator mapIterator; // creates iterator based on IndexToVarTable map from Singleton.
  mapIterator = instance->indexToVarTable.begin();
  vector<float> flightValues(36);
  vector<float>::iterator it = flightValues.begin();
  string firstBuffer = "";
  while (instance->runTreads) {
    char line[1024] = {0};
    read(socketNumber, line, 1024);
    string secondBuffer = line;
    firstBuffer = firstBuffer + secondBuffer;
    string firstToken = firstBuffer.substr(0, firstBuffer.find("\n")); // in firstToken we will have from start to \n.
    string secondToken = firstBuffer.substr(firstBuffer.find("\n") + 1,
                                            firstBuffer.length()); // here we will have the string pass the \n.
    //separate firstToken by "," and update the the vector.
    stringstream ss(firstToken);
    while (ss.good()) { //"insert to vector" while.
      string subStr;
      getline(ss, subStr, ',');
      Expression *exp;
      double val = 0;
      try {
        exp = instance->interpreter->interpret(subStr);
        val = exp->calculate();
      } catch (const char *e) {
        cout << e << endl;
        cout << "exception in Open server while updating interpreter" << endl;
      }
      *it = val;
      advance(it, 1);
    }
    //start of updating map and interpreter.
    it = flightValues.begin();
    mapIterator = instance->indexToVarTable.begin();
    while (mapIterator != instance->indexToVarTable.end()) {
      if (strcmp((*mapIterator).second->direction.c_str(), "<-") == 0) {
        float valueToUpdate = *it;
        (*mapIterator).second->value = (*it);
        if (strcmp(((*mapIterator).second->name).c_str(), "") != 0) {
          string format = ((*mapIterator).second->name) + "=" + to_string(valueToUpdate);
          try {
            instance->interpreter->setVariables(format);
          } catch (const char *e) {
            cout << e << endl;
            cout << "exception while inserting to interpreter!" << endl;
          }
        }

      }
      advance(it, 1);
      advance(mapIterator, 1);
    }
    //end of updating map.
    //reinitialize the iterators to begin.
    it = flightValues.begin();
    mapIterator = instance->indexToVarTable.begin();

    firstBuffer = secondToken; //take what ever values found after the "\n" (if we found any)
  }
}

