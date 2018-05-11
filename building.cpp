//implements building base class
#include "headers.h"
#include "building.h"

building::building(){ //defult building constructer

}

//get/set functions
string building::get_name(){
  return _name;
}

void building::set_health(int health){
  _health=health;
}

int building::get_health(){
  return _health;
}

unit building::spawnUnit(string uType){
  return unit();
}

int building::get_AC(){
  return _AC;
}

void building::set_AC(int AC){
  _AC=AC;
}

char building::get_icon(){
  return _icon;
}

int building::get_cost(){
  return _cost;
}

void building::set_AI(bool AI){
  _AI=AI;
}

bool building::get_AI(){
  return _AI;
}

int building::get_buildingIncome(){
  return _buildingIncome;
}

void building::tickTurn(){

}

building::~building(){//defult building deconstrucer

}
