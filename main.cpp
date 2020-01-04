#include <iostream>
#include "Singleton.h"
#include "Parser.h"
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  // create first Singleton
  Singleton *s = Singleton::getInstance();
  try {
    if (argc < 2) {
      throw "error - there is no arguments";
    }
    Parser pars = Parser(argv[1]);
    // run the program
    pars.runParser();
    s->runTreads = false; //terminates the threads that send & receive messages to & from the simulator.
    close(s->clientSocketNumber); //close the client socket.
    close(s->serverSocketNumber); //close the server socket.
  } catch (const char *e) {
    std::cout << e << std::endl;
  }
  return 0;
}