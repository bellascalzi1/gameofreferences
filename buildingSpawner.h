#ifndef BUILDINGSPAWNER_H
#define BUILDINGSPAWNER_H

#include "headers.h"
#include "building.h"
#include "unit.h"

class buildingSpawner: public building
{
protected:
  bool _hasSpawned;
public:
  buildingSpawner();
  virtual unit spawnUnit()=0;
  ~buildingSpawner();
};

#endif //BUILDINGSPAWNER_H
