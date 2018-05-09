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
  unit spawnUnit();
  ~buildingBarrack();
};

#endif //BUILDINGBARRACK_H
