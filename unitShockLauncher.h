#ifndef UNITSHOCKLAUNCHER_H
#define UNITSHOCKLAUNCHER_H

#include "headers.h"
#include "unit.h"

class unitShockLauncher : public unit {

protected:

public:
  unitShockLauncher();
  unitShockLauncher(bool AI);
  void tickTurn();
  ~unitShockLauncher();
};
#endif
