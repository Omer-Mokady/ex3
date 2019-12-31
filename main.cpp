#include <iostream>
#include "Singleton.h"
#include "Parser.h"
#include <unistd.h>

using namespace std;

int main(int, char *argv[]) {
  // create first Singleton
  Singleton *s = Singleton::getInstance();
  Parser pars = Parser(argv[1]);
  // run the program
  pars.runParser();
  s->runTreads = false; //terminates the threads that send & receive messages to & from the simulator.
  close(s->clientSocketNumber); //close the client socket.
  close(s->serverSocketNumber); //close the server socket.
  cout << "end of main" << endl;
  return 0;
}