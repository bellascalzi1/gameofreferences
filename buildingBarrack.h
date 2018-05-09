//defines barracks
#ifndef BUILDINGBARRACK_H
#define BUILDINGBARRACK_H

#include "headers.h"
#include "buildingSpawner.h"
#include "unit.h"
#include "unitTypes.h"

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
