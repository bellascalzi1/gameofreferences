//implements vehicle bay
#include "headers.h"
#include "buildingVehicleBay.h"

buildingVehicleBay::buildingVehicleBay(){  //defult constructor
  _health=80;
  _baseHealth=80;
  _AC=2;
  _icon='V';
  _cost=300;
  _name="Vehicle Bay";
  _hasSpawned = false;
  _buildingIncome=-15;
  _AI=false;
}

buildingVehicleBay::buildingVehicleBay(bool AI){  //constructor with input to set AI ownership
  _health=80;
  _baseHealth=80;
  _AC=2;
  _icon='V';
  _cost=300;
  _name="Vehicle Bay";
  _hasSpawned = false;
  _buildingIncome=-15;
  _AI=AI;
}

unit* buildingVehicleBay::spawnUnit(string uType){    //spawns a new vehicle
  if(uType=="destroyer"){
    _hasSpawned=true;
    return new unitDestroyer();
  }
  else if(uType=="cruiser"){
    _hasSpawned=true;
    return new unitCruiser();
  }
  else if(uType=="shocklauncher"){
    _hasSpawned=true;
    return new unitShockLauncher();
  }
}

void buildingVehicleBay::tickTurn(){
  _hasSpawned=false;
  if(_health<_baseHealth){
    _health=round(_baseHealth*1.1);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
}

buildingVehicleBay::~buildingVehicleBay(){    //defult deconstructor

}
