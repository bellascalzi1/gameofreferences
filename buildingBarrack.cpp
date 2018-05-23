//implements barracks
#include "headers.h"
#include "buildingBarrack.h"
#include "buildingTypes.h"
#include "unitTypes.h"

buildingBarrack::buildingBarrack(){  //defult constructor
  _health=100;
  _baseHealth=100;
  _AC=2;
  _icon='#';
  _cost=100;
  _name="Barracks";
  _buildingIncome=-15;
  _hasSpawned=false;
  _priority=5;
  _AI=false;
}

buildingBarrack::buildingBarrack(bool AI){  //constructor with input to set AI ownership
  _health=100;
  _baseHealth=100;
  _AC=2;
  _icon='#';
  _cost=100;
  _name="Barracks";
  _buildingIncome=-15;
  _hasSpawned=false;
  _priority=5;
  _AI=AI;
}

unit* buildingBarrack::spawnUnit(string uType, bool AI){    //spawns a new unit
  if(uType=="infantry"){
    _hasSpawned=true;
    return new unitInfantry(AI);
  }
  else if(uType=="heavy"){
    _hasSpawned=true;
    return new unitHeavyInfantry(AI);
  }
  else if(uType=="light"){
    _hasSpawned=true;
    return new unitLightInfantry(AI);
  }
  else if(uType=="rocket"){
    _hasSpawned=true;
    return new exampleUnit();
  }
  else if(uType=="flamethrower"){
    _hasSpawned=true;
    return new exampleUnit();
  }
}

void buildingBarrack::tickTurn(){
  _hasSpawned=false;
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
}

buildingBarrack::~buildingBarrack(){    //defult deconstructor

}
