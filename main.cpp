#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Singleton.h"
#include "Parser.h"
#include <thread>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {

  Singleton *s = Singleton::getInstance();
  Parser pars = Parser(argv[1]);
  vector<string> lexer = pars.makeLexer(argv[1]);
  pars.runParser();
  s->runTreads = false; //terminates the threads that send & receive messages to & from the simulator.
  close(s->clientSocketNumber); //close the client socket.
  close(s->serverSocketNumber); //close the server socket.
  cout << "end of main" << endl;
  return 0;
}