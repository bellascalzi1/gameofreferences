//defiens main base building
#ifndef BUILDINGBASE_H
#define BUILDINGBASE_H

#include "headers.h"
#include "building.h"

class buildingBase: public building
{
protected:

public:
  buildingBase();
  buildingBase(bool AI);
  ~buildingBase();
};

#endif //BUILDINGBASE_H
