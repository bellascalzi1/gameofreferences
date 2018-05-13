//implements barracks
#include "headers.h"
#include "buildingBarrack.h"
#include "buildingTypes.h"
#include "unitTypes.h"

buildingBarrack::buildingBarrack(){  //defult constructor
  _health=100;
  _baseHealth=100;
  _AC=2;
  _icon='B';
  _cost=100;
  _name="Barracks";
  _buildingIncome=-15;
  _hasSpawned=false;
  _AI=false;
}

buildingBarrack::buildingBarrack(bool AI){  //constructor with input to set AI ownership
  _health=100;
  _baseHealth=100;
  _AC=2;
  _icon='B';
  _cost=100;
  _name="Barracks";
  _buildingIncome=-15;
  _hasSpawned=false;
  _AI=AI;
}

unit* buildingBarrack::spawnUnit(string uType){    //spawns a new unit
  if(uType=="infantry"){
    _hasSpawned=true;
    return new unitInfantry();
  }
  else if(uType=="heavy"){
    _hasSpawned=true;
    return new unitHeavyInfantry();
  }
  else if(uType=="light"){
    _hasSpawned=true;
    unit *temp=new unitLightInfantry();
    return temp;
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
    _health=round(_baseHealth*1.1);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
}

buildingBarrack::~buildingBarrack(){    //defult deconstructor

}
