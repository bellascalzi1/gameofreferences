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
  int unit_moveSpeed();
  bool unit_AI();
  void unitSet_health(int health);
  int unitGet_health();
  void unitSet_dmg(int dmg);
  int unitGet_dmg();
  void unitSet_AC(int AC);
  int unitSet_AC();
  ~tile();
};

#endif //TILE_H
