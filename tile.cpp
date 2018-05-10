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

//get/set tile variables
void tile::set_unit(unit newUnit){
  _unit=newUnit;
}

unit tile::get_unit(){
  return _unit;
}

void tile::set_building(building newBuilding){
  _building=newBuilding;
}

building tile::get_building(){
  return _building;
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
    return _building.get_icon();
  }
  else if (_hasUnit==true){
    return _unit.get_icon();
  }
  else{
    char temp = 'O'; //32; space
    return temp;
  }
}

//call get/set functions of unit
int tile::unit_moveSpeed(){
  return _unit.get_moveSpeed();
}

bool tile::unit_AI(){
  return _unit.get_AI();
}

void tile::unitSet_health(int health){
  _unit.set_health(health);
}

int tile::unitGet_health(){
  return _unit.get_health();
}

void tile::unitSet_dmg(int dmg){
  _unit.set_dmg(dmg);
}

int tile::unitGet_dmg(){
    return _unit.get_dmg();
}

void tile::unitSet_AC(int AC){
  _unit.set_AC(AC);
}

int tile::unitGet_AC(){
    return _unit.get_AC();
}

string tile::unitGet_name(){
  return _unit.get_name();
}

//call get/set functions of building
bool tile::building_AI(){
  return _building.get_AI();
}

void tile::buildingSet_health(int health){
  _building.set_health(health);
}

int tile::buildingGet_health(){
  return _building.get_health();
}

void tile::buildingSet_AC(int AC){
  _building.set_AC(AC);
}

int tile::buildingGet_AC(){
    return _building.get_AC();
}

string tile::buildingGet_name(){
  return _building.get_name();
}

void tile::building_spawnUnit(string uType){
  cout<<"test2"<<endl;
  building *temp = new buildingBarrack();
  _unit=temp->spawnUnit(uType);
  cout<<_unit.get_name()<<endl;
  _hasUnit=true;
}

tile::~tile(){

}
