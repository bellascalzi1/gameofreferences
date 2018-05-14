//defiens main mine building
#ifndef BUILDINGMINE_H
#define BUILDINGMINE_H

#include "headers.h"
#include "building.h"

class buildingMine: public building
{

protected:

public:
  buildingMine();
  buildingMine(bool AI);
  void tickTurn();
  ~buildingMine();
};

#endif //BUILDINGBASE_H
