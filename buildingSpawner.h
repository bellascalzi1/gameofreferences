//defines spawner building type as abstract class
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
