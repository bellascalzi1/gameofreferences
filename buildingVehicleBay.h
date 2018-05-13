//defines vehicle bay
#ifndef BUILDINGVEHICLEBAY_H
#define BUILDINGVEHICLEBAY_H

#include "headers.h"
#include "buildingSpawner.h"
#include "unit.h"
#include "unitTypes.h"

class buildingVehicleBay: public buildingSpawner
{
protected:

public:
  buildingVehicleBay();
  buildingVehicleBay(bool AI);
  unit* spawnUnit(string uType);
  void tickTurn();
  ~buildingVehicleBay();
};

#endif //BUILDINGBARRACK_H
