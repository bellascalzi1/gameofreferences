//impliments unit base class
#include "headers.h"
#include "unit.h"

unit::unit(){ //defult constructor
  _health=0;
}

//get/set functions
string unit::get_name(){
  return _name;
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

void unit::set_movesLeft(int movesLeft){
  _movesLeft=movesLeft;
}

int unit::get_movesLeft(){
  return _movesLeft;
}

void unit::set_dmg(int dmg){
  _dmg=dmg;
}

int unit::get_dmg(){
  return _dmg;
}

void unit::set_attacksLeft(int attacksLeft){
  _attacksLeft=attacksLeft;
}

int unit::get_attacksLeft(){
  return _attacksLeft;
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

void unit::tickTurn(){
 
}

unit::~unit(){//defult deconstructor

}
