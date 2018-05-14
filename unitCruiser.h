#ifndef UNITCRUISER_H
#define UNITCRUISER_H

#include "headers.h"
#include "unit.h"

class unitCruiser : public unit {

protected:

public:
  unitCruiser();
  unitCruiser(bool AI);
  void tickTurn();
  ~unitCruiser();
};
#endif
