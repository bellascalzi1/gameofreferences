//defines light infantry unit
#ifndef UNITLIGHTINFANTRY_H
#define UNITLIGHTINFANTRY_H

#include "headers.h"
#include "unit.h"

class unitLightInfantry: public unit
{
protected:

public:
unitLightInfantry();
unitLightInfantry(bool AI);
void tickTurn();
~unitLightInfantry();
};

#endif //UNITLIGHTINFANTRY_H
