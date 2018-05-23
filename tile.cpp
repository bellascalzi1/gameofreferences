//impliments tile class
#include "headers.h"
#include "tile.h"
#include "buildingTypes.h"
#include "unitTypes.h"

tile::tile(){ //defult constructor
  _hasUnit=false;
  _hasBuilding=false;
  _isSpawner=false;
}

tile::tile(int id){ //defult constructor
  _id=id;
  _hasUnit=false;
  _hasBuilding=false;
  _isSpawner=false;
}

int tile::get_id(){
  return _id;
}

//get/set tile variables
void tile::set_unit(unit *newUnit){
  _unit=newUnit;
}

unit* tile::get_unit(){
  return _unit;
}

void tile::set_building(building *newBuilding){
  _building=newBuilding;
}

building tile::get_building(){
  return *_building;
}

void tile::set_hasUnit(bool hasUnit){
  _hasUnit=hasUnit;
}

bool tile::get_hasUnit(){
  return _hasUnit;
}

void tile::set_hasBuilding(bool hasBuilding){
  _hasBuilding=hasBuilding;
}

bool tile::get_hasBuilding(){
  return _hasBuilding;
}

void tile::set_isSpawner(bool isSpawner){
  _isSpawner=isSpawner;
}

bool tile::get_isSpawner(){
  return _isSpawner;
}

char tile::get_icon(){
  if(_hasBuilding==true){
    return _building->get_icon();
  }
  else if (_hasUnit==true){
    return _unit->get_icon();
  }
  else{
    char temp = 32; //32; space
    return temp;
  }
}

//call get/set functions of unit
int tile::unit_moveSpeed(){
  return _unit->get_moveSpeed();
}

bool tile::unit_AI(){
  return _unit->get_AI();
}

void tile::unitSet_health(int health){
  _unit->set_health(health);
}

int tile::unitGet_health(){
  return _unit->get_health();
}

void tile::unitSet_dmg(int dmg){
  _unit->set_dmg(dmg);
}

int tile::unitGet_dmg(){
  if(_hasUnit==true){
    return _unit->get_dmg();
  }
  else{
    return 0;
  }
}

void tile::unitSet_AC(int AC){
  _unit->set_AC(AC);
}

int tile::unitGet_AC(){
    return _unit->get_AC();
}

void tile::unitSet_movesLeft(int movesLeft){
  _unit->set_movesLeft(movesLeft);
}

int tile::unitGet_movesLeft(){
  return _unit->get_movesLeft();
}

string tile::unitGet_name(){
  return _unit->get_name();
}

//call get/set functions of building
bool tile::building_AI(){
  return _building->get_AI();
}

void tile::buildingSet_health(int health){
  _building->set_health(health);
}

int tile::buildingGet_health(){
  return _building->get_health();
}

void tile::buildingSet_AC(int AC){
  _building->set_AC(AC);
}

int tile::buildingGet_AC(){
    return _building->get_AC();
}

string tile::buildingGet_name(){
  return _building->get_name();
}

void tile::building_spawnUnit(string uType, bool AI){
  if(_building->get_hasSpawned()==false){
    _unit=_building->spawnUnit(uType, AI);
    _hasUnit=true;
  }
  else{
    cout<<"Building out of spawns"<<endl;
  }
}

void tile::turnTick(){
  if(_hasUnit==true){
    _unit->tickTurn();
  }
  if(_hasBuilding==true){
  _building->tickTurn();
  }
}

int tile::getTileIncome(){
  int income;
  if(_hasUnit==true){
    income+=_unit->get_income();
  }
  if(_hasBuilding==true){
    income+=_building->get_buildingIncome();
  }
  return income;
}

void tile::killUnit(){
  _hasUnit=false;
  delete _unit;
}

void tile::killBuilding(){
  _hasBuilding=false;
  _isSpawner=false;
  delete _building;
}

int tile::get_priority(){
  if(_hasUnit==true and _hasBuilding==true){
    if(_building->get_AI()==true){
      _priority=_building->get_priority();
    }
    else{
      _priority=_building->get_priority()-(_unit->get_priority()/2);
    }
  }
  else if(_hasUnit==true){
    if(_unit->get_AI()==true){
      _priority=-1;
    }
    else{
      _priority=_unit->get_priority();
    }
  }
  else if(_hasBuilding==true){
    if(_building->get_AI()==true){
      _priority=_building->get_priority();
    }
    else{
      _priority=_building->get_priority();
    }
  }
  else{
    _priority=0;
  }
  return _priority;
}

tile::~tile(){

}
