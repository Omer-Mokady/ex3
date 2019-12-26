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
// to delete
OpenServerCommand::OpenServerCommand(string port) {
  Expression *e;
  Interpreter *i = new Interpreter();
  e = i->interpret(port);
  this->portNumber = (int) e->calculate();
}

OpenServerCommand::OpenServerCommand() {

}

int OpenServerCommand::execute(vector<string>::iterator it) { //starting a thread where the server is listening on.
  cout << "OpenServerCommand execute check" << endl;
  string value = *(it + 1);
  cout << "value in iterator: " << value << endl;

  Expression *e;
  Interpreter *i = new Interpreter();
  e = i->interpret(value);
  this->portNumber = (int) e->calculate();

  thread openServer([this] { openSocket(); });
  openServer.join(); //wait until someone (the simulator) will connect to the socket, and continue only afterward - therefore we need thread.join().
  thread listenThread([this] { listener(); });
  listenThread.detach(); //read constantly, we wan it to run with the rest of the program - so we detach it.
  return 2; //return the number of elements + 1 to the parser.
}

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
  vector<float> flightValues(36);
  vector<float>::iterator it = flightValues.begin();
  string firstBuffer = "";
  Singleton *s = Singleton::getInstance();
  size_t index;
  int temp = 0;
  while (temp < 1000) { ///////////////////////////////////////////////////////////////replace this line.
    char line[1024] = {0};
    read(socketNumber, line, 1024);
    string secondBuffer = line;
    firstBuffer = firstBuffer + secondBuffer;
    string firstToken = firstBuffer.substr(0, firstBuffer.find("\n")); // in firstToken we will have from start to \n.
    string secondToken = firstBuffer.substr(firstBuffer.find("\n") + 1,
                                            firstBuffer.length()); // here we will have the string pass the \n.
    //separate firstToken by "," and update the map and the vector.
    stringstream ss(firstToken);
    cout << "\ndata from sim: \n";
    cout << firstBuffer << endl;
    while (ss.good()) {
      string subStr;
      getline(ss, subStr, ',');
      Expression *e;
      Interpreter *inter = new Interpreter();
      e = inter->interpret(subStr);

      double val = e->calculate();
      if (it != flightValues.end()) {
        /////////////////////////////////////////////////////////////here we will update our maps
      }
      *it = val;
      advance(it, 1);
//      flightValues.at(*(it + index)) = val;
//      index++;
    }
    it = flightValues.begin();
    firstBuffer = secondToken; //this is the last line of the loop - DO NOT CHANGE IT
    cout << "flight values vector:\n";
    for (int k = 0; k < 36; k++) {
      cout << flightValues.at(k) << " ";
    }
  }
  cout << "updated 26.12 19:00" << endl;

}