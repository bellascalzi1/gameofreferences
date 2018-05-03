#ifndef TILE_H
#define TILE_H

#include "headers.h"
#include "unit.h"
#include "building.h"

class tile
{
protected:
  string _pos;
  bool _hasUnit;
  bool _hasbuilding;
  building _building;
  //unit _unit;
public:
  tile();
  ~tile();
};

#endif //TILE_H
