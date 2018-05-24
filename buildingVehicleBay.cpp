//implements vehicle bay
#include "headers.h"
#include "buildingVehicleBay.h"

buildingVehicleBay::buildingVehicleBay(){  //defult constructor
  _health=150;
  _baseHealth=150;
  _AC=4;
  _icon='V';
  _cost=120;
  _name="Vehicle Bay";
  _hasSpawned = false;
  _buildingIncome=-12;
  _priority=12;
  _AI=false;
}

buildingVehicleBay::buildingVehicleBay(bool AI){  //constructor with input to set AI ownership
  _health=150;
  _baseHealth=150;
  _AC=4;
  _icon='V';
  _cost=120;
  _name="Vehicle Bay";
  _hasSpawned = false;
  _buildingIncome=-12;
  _priority=12;
  _AI=AI;
}

unit* buildingVehicleBay::spawnUnit(string uType, bool AI){    //spawns a new vehicle
  if(uType=="destroyer"){
    _hasSpawned=true;
    return new unitDestroyer(AI);
  }
  else if(uType=="cruiser"){
    _hasSpawned=true;
    return new unitCruiser(AI);
  }
  else if(uType=="shocklauncher"){
    _hasSpawned=true;
    return new unitShockLauncher(AI);
  }
}

void buildingVehicleBay::tickTurn(){
  _hasSpawned=false;
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
}

buildingVehicleBay::~buildingVehicleBay(){    //defult deconstructor

}
