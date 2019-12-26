//
// Created by omer on 24/12/2019.
//

#include "Singleton.h"
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
  // create simToInsex table and IndexToVar table
  int counter = 0;


//  map<string, Var*>::iterator it=this->simTable.begin();
//  /*
  //1
//  this->simTable.insert(it,
//      pair<string, Var*>("/instrumentation/airspeed-indicator/indicated-speed-kt", new Var()));
  this->simToIndexTable["/instrumentation/airspeed-indicator/indicated-speed-kt"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/airspeed-indicator/indicated-speed-kt");
  counter++;

//  it=this->simTable.begin();
  //2
  this->simToIndexTable["/sim/time/warp"]= counter;
  this->indexToVarTable[counter]= new Var("/sim/time/warp");
  counter++;
//  this->simTable.insert(it,pair<string, Var*>("/sim/time/warp", new Var()));
//  it=this->simTable.begin();
//  this->simTable["/sim/time/warp"]= new Var();
//
//3
  this->simToIndexTable["/controls/switches/magnetos"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/magnetos");
  counter++;

//  this->simTable.insert(it,pair<string, Var*>("/controls/switches/magnetos", new Var()));
//  it=this->simTable.begin();
//  this->simTable["/controls/switches/magnetos"]= new Var();
//  //4!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  this->simToIndexTable["/instrumentation/heading-indicator/offset-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/heading-indicator/offset-deg");
  counter++;
//  this->simTable.insert(it,pair<string, Var*>("//instrumentation/heading-indicator/offset-deg", new Var()));
//  it=this->simTable.begin();
////  this->simTable["//instrumentation/heading-indicator/offset-deg"]= new Var();
//  //5
  this->simToIndexTable["/instrumentation/altimeter/indicated-altitude-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/altimeter/indicated-altitude-ft");
  counter++;
//  this->simTable.insert(it,pair<string, Var*>("/instrumentation/altimeter/indicated-altitude-ft", new Var()));
//  it=this->simTable.begin();

//  this->simTable["/instrumentation/altimeter/indicated-altitude-ft"]= new Var();
  //6
  this->simToIndexTable["/instrumentation/altimeter/pressure-alt-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/altimeter/pressure-alt-ft");
  counter++;
//  this->simTable.insert(it,pair<string, Var*>("/instrumentation/altimeter/pressure-alt-ft", new Var()));
//  it++;
////  this->simTable["/instrumentation/altimeter/pressure-alt-ft"]= new Var();
//  //7
  this->simToIndexTable["/instrumentation/attitude-indicator/indicated-pitch-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/attitude-indicator/indicated-pitch-deg");
  counter++;
//  this->simTable.insert(it,pair<string, Var*>("/instrumentation/attitude-indicator/indicated-pitch-deg", new Var()));
//  it++;
////  this->simTable["/instrumentation/attitude-indicator/indicated-pitch-deg"]= new Var();
//  //8
  this->simToIndexTable["/instrumentation/attitude-indicator/indicated-roll-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/attitude-indicator/indicated-roll-deg");
  counter++;
//  this->simTable.insert(it,
//      pair<string, Var*>("/instrumentation/attitude-indicator/indicated-roll-deg", new Var()));
//  it++;
////  this->simTable["/instrumentation/attitude-indicator/indicated-roll-deg"]= new Var();
//  //9
  this->simToIndexTable["/instrumentation/attitude-indicator/internal-pitch-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/attitude-indicator/internal-pitch-deg");
  counter++;
//  this->simTable.insert(it,
//                    pair<string, Var*>("/instrumentation/attitude-indicator/internal-pitch-deg", new Var()));
//  it++;
////  this->simTable["/instrumentation/attitude-indicator/internal-pitch-deg"]= new Var();
//  //10
  this->simToIndexTable["/instrumentation/attitude-indicator/internal-roll-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/attitude-indicator/internal-roll-deg");
  counter++;
//  this->simTable.insert(it,
//                        pair<string, Var*>("/instrumentation/attitude-indicator/internal-roll-deg", new Var()));
//  it++;
////  this->simTable["/instrumentation/attitude-indicator/internal-roll-deg"]= new Var();
//  //11
  this->simToIndexTable["/instrumentation/encoder/indicated-altitude-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/encoder/indicated-altitude-ft");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/encoder/indicated-altitude-ft", new Var()));
//  it++;
////  this->simTable["/instrumentation/encoder/indicated-altitude-ft"]= new Var();
//  //12
  this->simToIndexTable["/instrumentation/encoder/pressure-alt-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/encoder/pressure-alt-ft");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/encoder/pressure-alt-ft", new Var()));
////  this->simTable["/instrumentation/encoder/pressure-alt-ft"]= new Var();
//  it++;
//  //13
  this->simToIndexTable["/instrumentation/gps/indicated-altitude-ft"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/gps/indicated-altitude-ft");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/gps/indicated-altitude-ft", new Var()));
////  this->simTable["/instrumentation/gps/indicated-altitude-ft"]= new Var();
//  it++;
//  //14
  this->simToIndexTable["/instrumentation/gps/indicated-ground-speed-kt"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/gps/indicated-ground-speed-kt");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/gps/indicated-ground-speed-kt", new Var()));
////  this->simTable["/instrumentation/gps/indicated-ground-speed-kt"]= new Var();
//  it++;
//  //15
  this->simToIndexTable["/instrumentation/gps/indicated-vertical-speed"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/gps/indicated-vertical-speed");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/gps/indicated-vertical-speed", new Var()));
////  this->simTable["/instrumentation/gps/indicated-vertical-speed"]= new Var();
//  it++;
//  //16
  this->simToIndexTable["/instrumentation/heading-indicator/indicated-heading-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/heading-indicator/indicated-heading-deg");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/heading-indicator/indicated-heading-deg", new Var()));
////  this->simTable["/instrumentation/heading-indicator/indicated-heading-deg"]= new Var();
//  it++;
//  //17
  this->simToIndexTable["/instrumentation/magnetic-compass/indicated-heading-deg"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/magnetic-compass/indicated-heading-deg");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/magnetic-compass/indicated-heading-deg", new Var()));
////  this->simTable["/instrumentation/magnetic-compass/indicated-heading-deg"]= new Var();
//  it++;
//  //18
  this->simToIndexTable["/instrumentation/slip-skid-ball/indicated-slip-skid"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/slip-skid-ball/indicated-slip-skid");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/slip-skid-ball/indicated-slip-skid", new Var()));
////  this->simTable["/instrumentation/slip-skid-ball/indicated-slip-skid"]= new Var();
//  it++;
//  //19
  this->simToIndexTable["/instrumentation/turn-indicator/indicated-turn-rate"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/turn-indicator/indicated-turn-rate");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/turn-indicator/indicated-turn-rate", new Var()));
////  this->simTable["/instrumentation/turn-indicator/indicated-turn-rate"]= new Var();
//  it++;
//  //20
  this->simToIndexTable["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"]= counter;
  this->indexToVarTable[counter]= new Var("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", new Var()));
////  this->simTable["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"]= new Var();
//  it++;
//  //21
  this->simToIndexTable["/controls/flight/aileron"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/aileron");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/flight/aileron", new Var()));
//  it++;
////  this->simTable["/controls/flight/aileron"]= new Var();
//  //22
  this->simToIndexTable["/controls/flight/elevator"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/elevator");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/flight/elevator", new Var()));
//  it++;
////  this->simTable["/controls/flight/elevator"]= new Var();
//  //23
  this->simToIndexTable["/controls/flight/rudder"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/rudder");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/flight/rudder", new Var()));
//  it++;
////  this->simTable["/controls/flight/rudder"]= new Var();
//  //24
  this->simToIndexTable["/controls/flight/flaps"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/flaps");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/flight/flaps", new Var()));
//  it++;
////  this->simTable["/controls/flight/flaps"]= new Var();
  //25
  this->simToIndexTable["/controls/engines/engine/throttle"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/engines/engine/throttle");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/engines/engine/throttle", new Var()));
//  it++;
//  this->simTable["/controls/engines/engine/throttle"]= new Var();
//  //26

  this->simToIndexTable["/controls/engines/current-engine/throttle"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/engines/current-engine/throttle");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/engines/current-engine/throttle", new Var()));
//  it++;
////  this->simTable["/controls/engines/current-engine/throttle"]= new Var();
  //27
  this->simToIndexTable["/controls/switches/master-avionics"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/master-avionics");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/switches/master-avionics", new Var()));
//  it++;
//  //  this->simTable["/controls/switches/master-avionics"]= new Var();
//  //28
  this->simToIndexTable["/controls/switches/starter"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/starter");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/switches/starter", new Var()));
//  it++;
////  this->simTable["/controls/switches/starter"]= new Var();
//  //29
  this->simToIndexTable["/engines/active-engine/auto-start"]= counter;
  this->indexToVarTable[counter]= new Var("/engines/active-engine/auto-start");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/engines/active-engine/auto-start", new Var()));
//  it++;
////  this->simTable["/engines/active-engine/auto-start"]= new Var();
//  //30
  this->simToIndexTable["/controls/flight/speedbrake"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/flight/speedbrake");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/flight/speedbrake", new Var()));
//  it++;
////  this->simTable["/controls/flight/speedbrake"]= new Var();
//  //31
  this->simToIndexTable["/sim/model/c172p/brake-parking"]= counter;
  this->indexToVarTable[counter]= new Var("/sim/model/c172p/brake-parking");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/sim/model/c172p/brake-parking", new Var()));
//  it++;
////  this->simTable["/sim/model/c172p/brake-parking"]= new Var();
//  //32
  this->simToIndexTable["/controls/engines/engine/primer"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/engines/engine/primer");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/engines/engine/primer", new Var()));
//  it++;
////  this->simTable["/controls/engines/engine/primer"]= new Var();
//  //33
  this->simToIndexTable["/controls/engines/current-engine/mixture"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/engines/current-engine/mixture");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/engines/current-engine/mixture", new Var()));
//  it++;
////  this->simTable["/controls/engines/current-engine/mixture"]= new Var();
//  //34
  this->simToIndexTable["/controls/switches/master-bat"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/master-bat");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/switches/master-bat", new Var()));
//  it++;
//  this->simTable["/controls/switches/master-bat"]= new Var();
  //35
  this->simToIndexTable["/controls/switches/master-alt"]= counter;
  this->indexToVarTable[counter]= new Var("/controls/switches/master-alt");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/controls/switches/master-alt", new Var()));
//  it++;
//  this->simTable["/controls/switches/master-alt"]= new Var();
//  //36
  this->simToIndexTable["/engines/engine/rpm"]= counter;
  this->indexToVarTable[counter]= new Var("/engines/engine/rpm");
  counter++;
//  this->simTable.insert(it, pair<string, Var*>("/engines/engine/rpm", new Var()));
//  it++;
////  this->simTable["/engines/engine/rpm"]= new Var();




//  this->checkMap["check1"] = 3;
//  this->checkMap["check2"] = 4;




}