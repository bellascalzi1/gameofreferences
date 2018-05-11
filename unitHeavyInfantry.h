//defines heavy infantry unit
#ifndef UNITHEAVYINFANTRY_H
#define UNITHEAVYINFANTRY_H

#include "headers.h"
#include "unit.h"

class unitHeavyInfantry: public unit
{
protected:

public:
  unitHeavyInfantry();
  unitHeavyInfantry(bool AI);
  void tickTurn();
  ~unitHeavyInfantry();
};

#endif //UNITHEAVYINFANTRY_H
