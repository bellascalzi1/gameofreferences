#ifndef UNITDESTROYER_H
#define UNITDESTROYER_H

#include "headers.h"
#include "unit.h"

class unitDestroyer : public unit {

protected:

public:
  unitDestroyer();
  unitDestroyer(bool AI);
  void tickTurn();
  ~unitDestroyer();
};
#endif
