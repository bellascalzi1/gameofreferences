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

int tile::getUnits_moveSpeed(){
  return _unit.get_moveSpeed();
}

tile::~tile(){

}
