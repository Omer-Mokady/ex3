//
// Created by gal on 22/12/2019.
//

#include "ConnectCommand.h"
#include <thread>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
ConnectCommand::ConnectCommand() {

}

int ConnectCommand::execute(vector<string>::iterator it) {
  cout << "in ConnectCommand execute....." << endl;
  string value1 = *(it + 1); //ip
  if (value1.at(0) == '"' && value1.at(value1.length() - 1) == '"') {
    value1 = value1.substr(1, value1.length() - 2);
  }
  this->ipNumber = value1;
  string value2 = *(it + 2); //port number
  this->serverPortNumber = stoi(value2);
  cout << "iteraor value1: " << value1 << endl;
  cout << "iteraor value2: " << value2 << endl;

  thread openServer([this] { openSocket(); });
  openServer.join(); //wait until someone (the simulator) will connect to the socket, and continue only afterward - therefore we need thread.join().
  thread listenThread([this] { sender(); });
  listenThread.detach();
  this_thread::sleep_for(30s);
  return 3;
}

int ConnectCommand::openSocket() {
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    cerr << "Could not create a socket" << endl;
    return -1;
  }
  this->clientSocketNumber = client_socket;
  sockaddr_in address;
  const char *validIP = this->ipNumber.c_str();
  cout << "ip sent to server: " << validIP << endl;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(validIP);
  address.sin_port = htons(this->serverPortNumber);
  int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
    return -2;
  } else {
    cout << "Client is now connected to server" << endl;
  }
  cout << "after connect to sim" << endl;
  return 0;
}
void ConnectCommand::sender() {
  char msg[] = "1";
  int is_send = send(this->clientSocketNumber, msg, strlen(msg), 0);
  if (is_send == -1) {
    cout << "Error sending message." << endl;
  } else {
    cout << "message sent to server." << endl;
  }
}