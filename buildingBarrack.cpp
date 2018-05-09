#include "headers.h"
#include "buildingBarrack.h"

buildingBarrack::buildingBarrack(){

}

unit buildingBarrack::spawnUnit(){
  _hasSpawned=true;
  return exampleUnit();
}

buildingBarrack::~buildingBarrack(){

}
