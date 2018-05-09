//defines infantry unit type
#ifndef UNITINFANTRY_H
#define UNITINFANTRY_H

#include "headers.h"
#include "unit.h"

class unitInfantry: public unit
{
protected:

public:
  unitInfantry();
  unitInfantry(bool AI);
  ~unitInfantry();
};

#endif //UNITINFANTRY_H
