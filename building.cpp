#include "headers.h"

building::building(){

}

void building::set_health(int health){
  _health=health;
}

int building::get_health(){
  return _health;
}

int building::get_AC(){
  return _AC;
}

char building::get_icon(){
  return icon;
}

int building::get_cost(){
  return _cost;
}

building::~building(){

}
