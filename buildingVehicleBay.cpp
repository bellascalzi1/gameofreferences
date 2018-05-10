//implements vehicle bay
#include "headers.h"
#include "buildingVehicleBay.h"

buildingVehicleBay::buildingVehicleBay(){  //defult constructor
  _health=80;
  _AC=2;
  _icon='V';
  _cost=300;
  _name="Vehicle Bay";
  _buildingIncome=-15;
  _AI=false;
}

buildingVehicleBay::buildingVehicleBay(bool AI){  //constructor with input to set AI ownership
  _health=80;
  _AC=2;
  _icon='V';
  _cost=300;
  _name="Vehicle Bay";
  _buildingIncome=-15;
  _AI=AI;
}

unit buildingVehicleBay::spawnUnit(string uType){    //spawns a new vehicle
  if(uType=="destroyer"){
    _hasSpawned=true;
    return destroyer();
  }
  else if(uType=="cruiser"){
    _hasSpawned=true;
    return cruiser();
  }
  else if(uType=="shocklauncher"){
    _hasSpawned=true;
    return shocklauncher();
  }
}

buildingVehicleBay::~buildingVehicleBay(){    //defult deconstructor

}