#ifndef DESTROYER_H
#define DESTROYER_H

#include "headers.h"
#include "unit.h"

class destroyer : public unit {

protected:

public:
  destroyer();
  destroyer(bool AI);
  ~destroyer();
};
#endif
