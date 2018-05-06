#include "headers.h"
#include "unit.h"

unit::unit(){
  _health=0;
}

void unit::set_health(int health){
  _health=health;
}

int unit::get_health(){
  return _health;
}

void unit::set_AC(int AC){
  _AC=AC;
}

int unit::get_AC(){
  return _AC;
}

char unit::get_icon(){
  return _icon;
}

void unit::set_moveSpeed(int moveSpeed){
  _moveSpeed=moveSpeed;
}

int unit::get_moveSpeed(){
  return _moveSpeed;
}

void unit::set_dmg(int dmg){
  _dmg=dmg;
}

int unit::get_dmg(){
  return _dmg;
}

int unit::get_cost(){
  return _cost;
}

void unit::set_AI(bool AI){
  _AI=AI;
}

bool unit::get_AI(){
  return _AI;
}

/*void unit::resetInitialStats(){

}*/


unit::~unit(){
  //why?
}
