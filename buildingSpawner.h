//defines spawner building type as abstract class  spawner is a building able to spawn units
//******this class is mainly for book keeping and simplification of some code*****
#ifndef BUILDINGSPAWNER_H
#define BUILDINGSPAWNER_H

#include "headers.h"
#include "building.h"
#include "unit.h"

class buildingSpawner: public building
{
protected:

public:
  buildingSpawner();
  virtual unit* spawnUnit(string uType, bool AI)=0;
  ~buildingSpawner();
};

#endif //BUILDINGSPAWNER_H
