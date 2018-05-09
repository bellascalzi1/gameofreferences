#include "headers.h"
#include "buildingBarrack.h"

buildingBarrack::buildingBarrack(){
  _health=100;
  _AC=2;
  _icon='B';
  _cost=100;
  _name="Barracks";
  _AI=false;
}

buildingBarrack::buildingBarrack(bool AI){
  _health=100;
  _AC=2;
  _icon='B';
  _cost=100;
  _name="Barracks";
  _AI=AI;
}

unit buildingBarrack::spawnUnit(string uType){
  if(uType=="infantry"){
    _hasSpawned=true;
    return exampleUnit();
  }
  else if(uType=="heavy"){
    _hasSpawned=true;
    return exampleUnit();
  }
  else if(uType=="light"){
    _hasSpawned=true;
    return exampleUnit();
  }
  else if(uType=="rocket"){
    _hasSpawned=true;
    return exampleUnit();
  }
  else if(uType=="flamethrower"){
    _hasSpawned=true;
    return exampleUnit();
  }
}

buildingBarrack::~buildingBarrack(){

}
