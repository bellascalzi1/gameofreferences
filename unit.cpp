#include "headers.h"

unit::unit(){

}

void unit::set_health(int health){
  _health=health;
}

int unit::get_health(){
  return _health;
}

int unit::get_AC(){
  return _AC;
}

char unit::get_icon(){
  return icon;
}

int init::get_moveSpeed(){
  return _moveSpeed;
}

int unit::get_dmg(){
  return _dmg;
}

int unit::get_cost(){
  return _cost;
}

unit::~unit(){

}
