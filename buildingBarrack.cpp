//implements barracks
#include "headers.h"
#include "buildingBarrack.h"
#include "buildingTypes.h"
#include "unitTypes.h"

buildingBarrack::buildingBarrack(){  //defult constructor
  _health=100;
  _AC=2;
  _icon='B';
  _cost=100;
  _name="Barracks";
  _AI=false;
}

buildingBarrack::buildingBarrack(bool AI){  //constructor with input to set AI ownership
  _health=100;
  _AC=2;
  _icon='B';
  _cost=100;
  _name="Barracks";
  _AI=AI;
}

unit buildingBarrack::spawnUnit(string uType){    //spawns a new unit
  cout<<"testx"<<endl;
  if(uType=="infantry"){
    _hasSpawned=true;
    cout<<"hi this is a test"<<endl;
    unit temp = unitInfantry();
    return temp;
  }
  else if(uType=="heavy"){
    _hasSpawned=true;
    return unitHeavyInfantry();
  }
  else if(uType=="light"){
    _hasSpawned=true;
    return unitLightInfantry();
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

buildingBarrack::~buildingBarrack(){    //defult deconstructor

}
