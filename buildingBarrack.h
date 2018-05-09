#ifndef BUILDINGBARRACK_H
#define BUILDINGBARRACK_H

#include "headers.h"
#include "buildingSpawner.h"
#include "unit.h"
#include "exampleUnit.h"

class buildingBarrack: public buildingSpawner
{
protected:

public:
  buildingBarrack();
  buildingBarrack(bool AI);
  unit spawnUnit(string uType);
  ~buildingBarrack();
};

#endif //BUILDINGBARRACK_H
