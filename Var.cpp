//
// Created by omer on 23/12/2019.
//

#include "Var.h"

Var::Var(string name1, string direction1, string sim1){
  this->name = name1;
  this->direction = direction1;
  this->sim = sim1;
}
Var::Var(string sim1){
  this->sim = sim1;
  this->name = "";
}
Var::Var(){
  this->value = 0;
  this->name = "";

}


void Var::setSim(string sim1) {
  this->sim = sim1;
}
