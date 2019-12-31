//
// Created by omer on 24/12/2019.
//

#include "Singleton.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "WhileCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"
/* Null, because instance will be initialized on demand. */
Singleton* Singleton::instance = 0;

Singleton* Singleton::getInstance()
{
  if (instance == 0)
  {
    instance = new Singleton();
  }
  return instance;
}

Singleton::Singleton()
{
  // create commandsMap
  Command* connectCommandV = new ConnectCommand();
  this->commandsMap["connectControlClient"] = connectCommandV;
  Command* OpenServerCommandV = new OpenServerCommand();
  this->commandsMap["openDataServer"] = OpenServerCommandV;
  Command* defineVarCommandV = new DefineVarCommand();
  this->commandsMap["var"] = defineVarCommandV;
  Command* printCommandV = new PrintCommand();
  this->commandsMap["Print"] = printCommandV;
  Command* sleepCommandV = new SleepCommand();
  this->commandsMap["Sleep"] = sleepCommandV;
  Command* whileCommandV = new WhileCommand();
  this->commandsMap["while"] = whileCommandV;
  Command* ifCommandV = new IfCommand();
  this->commandsMap["if"] = ifCommandV;



  // create simToInsex table and IndexToVar table
  int counter = 0;
  // enter var number 0
  this->simToIndexTable["/instrumentation/airspeed-indicator/indicated-speed-kt"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/airspeed-indicator/indicated-speed-kt");
  counter++;

  // enter var number 1
  this->simToIndexTable["/sim/time/warp"]= counter;
  this->indexToVarTable[counter]= new Var("/sim/time/warp");
  counter++;
  // enter var number 2
  this->simToIndexTable["/controls/switches/magnetos"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/magnetos");
  counter++;
  // enter var number 3
  this->simToIndexTable["/instrumentation/heading-indicator/offset-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/heading-indicator/offset-deg");
  counter++;
  // enter var number 4
  this->simToIndexTable["/instrumentation/altimeter/indicated-altitude-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/altimeter/indicated-altitude-ft");
  counter++;
  // enter var number 5
  this->simToIndexTable["/instrumentation/altimeter/pressure-alt-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/altimeter/pressure-alt-ft");
  counter++;
  // enter var number 6
  this->simToIndexTable["/instrumentation/attitude-indicator/indicated-pitch-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/attitude-indicator/indicated-pitch-deg");
  counter++;
  // enter var number 7
  this->simToIndexTable["/instrumentation/attitude-indicator/indicated-roll-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/attitude-indicator/indicated-roll-deg");
  counter++;
  // enter var number 8
  this->simToIndexTable["/instrumentation/attitude-indicator/internal-pitch-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/attitude-indicator/internal-pitch-deg");
  counter++;
  // enter var number 9
  this->simToIndexTable["/instrumentation/attitude-indicator/internal-roll-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/attitude-indicator/internal-roll-deg");
  counter++;
  // enter var number 10
  this->simToIndexTable["/instrumentation/encoder/indicated-altitude-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/encoder/indicated-altitude-ft");
  counter++;
  // enter var number 11
  this->simToIndexTable["/instrumentation/encoder/pressure-alt-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/encoder/pressure-alt-ft");
  counter++;
  // enter var number 12
  this->simToIndexTable["/instrumentation/gps/indicated-altitude-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/gps/indicated-altitude-ft");
  counter++;
  // enter var number 13
  this->simToIndexTable["/instrumentation/gps/indicated-ground-speed-kt"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/gps/indicated-ground-speed-kt");
  counter++;
  // enter var number 14
  this->simToIndexTable["/instrumentation/gps/indicated-vertical-speed"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/gps/indicated-vertical-speed");
  counter++;
  // enter var number 15
  this->simToIndexTable["/instrumentation/heading-indicator/indicated-heading-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/heading-indicator/indicated-heading-deg");
  counter++;
  // enter var number 16
  this->simToIndexTable["/instrumentation/magnetic-compass/indicated-heading-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/magnetic-compass/indicated-heading-deg");
  counter++;
  // enter var number 17
  this->simToIndexTable["/instrumentation/slip-skid-ball/indicated-slip-skid"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/slip-skid-ball/indicated-slip-skid");
  counter++;
  // enter var number 18
  this->simToIndexTable["/instrumentation/turn-indicator/indicated-turn-rate"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/turn-indicator/indicated-turn-rate");
  counter++;
  // enter var number 19
  this->simToIndexTable["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
  counter++;
  // enter var number 20
  this->simToIndexTable["/controls/flight/aileron"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/aileron");
  counter++;
  // enter var number 21
  this->simToIndexTable["/controls/flight/elevator"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/elevator");
  counter++;
  // enter var number 22
  this->simToIndexTable["/controls/flight/rudder"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/rudder");
  counter++;
  // enter var number 23
  this->simToIndexTable["/controls/flight/flaps"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/flaps");
  counter++;
  // enter var number 24
  this->simToIndexTable["/controls/engines/engine/throttle"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/engines/engine/throttle");
  counter++;
  // enter var number 25
  this->simToIndexTable["/controls/engines/current-engine/throttle"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/engines/current-engine/throttle");
  counter++;
  // enter var number 26
  this->simToIndexTable["/controls/switches/master-avionics"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/master-avionics");
  counter++;
  // enter var number 27
  this->simToIndexTable["/controls/switches/starter"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/starter");
  counter++;
  // enter var number 28
  this->simToIndexTable["/engines/active-engine/auto-start"]= counter;
  this->indexToVarTable[counter]= new Var("/engines/active-engine/auto-start");
  counter++;
  // enter var number 29
  this->simToIndexTable["/controls/flight/speedbrake"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/speedbrake");
  counter++;
  // enter var number 30
  this->simToIndexTable["/sim/model/c172p/brake-parking"]= counter;
  this->indexToVarTable[counter]= new Var("/sim/model/c172p/brake-parking");
  counter++;
  // enter var number 31
  this->simToIndexTable["/controls/engines/engine/primer"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/engines/engine/primer");
  counter++;
  // enter var number 32
  this->simToIndexTable["/controls/engines/current-engine/mixture"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/engines/current-engine/mixture");
  counter++;
  // enter var number 33
  this->simToIndexTable["/controls/switches/master-bat"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/master-bat");
  counter++;
  // enter var number 34
  this->simToIndexTable["/controls/switches/master-alt"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/master-alt");
  counter++;
  // enter var number 35
  this->simToIndexTable["/engines/engine/rpm"]= counter;
  this->indexToVarTable[counter]= new Var("/engines/engine/rpm");
  counter++;
}