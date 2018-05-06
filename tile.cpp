#include "headers.h"
#include "tile.h"

tile::tile(){
  _hasUnit=false;
}

void tile::set_unit(unit newUnit){
  _unit=newUnit;
}

unit tile::get_unit(){
  return _unit;
}

void tile::set_hasUnit(bool hasUnit){
  _hasUnit=hasUnit;
}

bool tile::get_hasUnit(){
  return _hasUnit;
}

char tile::get_icon(){
  return _unit.get_icon();
}

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

int tile::unitSet_AC(){
    return _unit.get_AC();
}

tile::~tile(){

}
