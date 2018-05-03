#include "headers.h"
#include "building.h"

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
  return _icon;
}

int building::get_cost(){
  return _cost;
}

building::~building(){

}
