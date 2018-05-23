//implements building main mine
#include "headers.h"
#include "buildingMine.h"

buildingMine::buildingMine(){  //defult constructor
  _health=100;
  _baseHealth=100;
  _AC=3;
  _icon='@';
  _cost=100;
  _name="Mine";
  _buildingIncome=150;
  _hasSpawned = false;
  _priority=10;
  _AI=false;
}

buildingMine::buildingMine(bool AI){  //constructor with input for AI ownership
  _health=100;
  _baseHealth=100;
  _AC=3;
  _icon='@';
  _cost=0;
  _name="Mine";
  _hasSpawned = false;
  _buildingIncome=150;
  _priority=10;
  _AI=AI;
}

void buildingMine::tickTurn(){
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
}

buildingMine::~buildingMine(){  //defult deconstructor

}
