//defines infantry unit type
#ifndef UNITINFANTRY_H
#define UNITINFANTRY_H

#include "headers.h"
#include "unit.h"

class unitIfantry: public unit
{
protected:

public:
  unitIfantry();
  unitIfantry(bool AI);
  ~unitIfantry();
};

#endif //UNITINFANTRY_H
