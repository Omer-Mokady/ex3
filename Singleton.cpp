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
  this->checkMap["check1"] = 3;
  this->checkMap["check2"] = 4;




}