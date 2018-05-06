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
  unit _unit;
public:
  tile();
  void set_unit(unit newUnit);
  unit get_unit();
  void set_hasUnit(bool hasUnit);
  bool get_hasUnit();
  char get_icon();
  int getUnits_moveSpeed();
  ~tile();
};

#endif //TILE_H
