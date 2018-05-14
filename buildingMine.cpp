//implements building main mine
#include "headers.h"
#include "buildingMine.h"

buildingMine::buildingMine(){  //defult constructor
  _health=450;
  _baseHealth=450;
  _AC=8;
  _icon='M';
  _cost=100;
  _name="Mine";
  _buildingIncome=150;
  _hasSpawned = false;
  _AI=false;
}

buildingMine::buildingMine(bool AI){  //constructor with input for AI ownership
  _health=500;
  _baseHealth=500;
  _AC=8;
  _icon='B';
  _cost=0;
  _name="Mine";
  _hasSpawned = false;
  _buildingIncome=150;
  _AI=AI;
}

void buildingMine::tickTurn(){
  if(_health<_baseHealth){
    _health=round(_baseHealth*1.1);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
}

buildingMine::~buildingMine(){  //defult deconstructor

}
