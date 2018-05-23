//defines tile class which stores the unit and building at each grid reffernce on the map
#ifndef TILE_H
#define TILE_H

#include "headers.h"
#include "unit.h"
#include "building.h"
#include "buildingTypes.h"
#include "unitTypes.h"


class tile
{
protected:
  string _pos;
  bool _hasUnit;
  bool _hasBuilding;
  bool _isSpawner;
  int _id;
  building *_building;
  unit *_unit;
  int _priority;
public:
  tile();
  tile(int id);
  int get_id();
  void set_unit(unit *newUnit);
  unit* get_unit();
  void set_building(building *newBuilding);
  building get_building();
  void set_hasUnit(bool hasUnit);
  bool get_hasUnit();
  void set_hasBuilding(bool hasBuilding);
  bool get_hasBuilding();
  void set_isSpawner(bool isSpawner);
  bool get_isSpawner();
  char get_icon();
  int unit_moveSpeed();
  bool unit_AI();
  void unitSet_health(int health);
  int unitGet_health();
  void unitSet_dmg(int dmg);
  int unitGet_dmg();
  void unitSet_AC(int AC);
  int unitGet_AC();
  string unitGet_name();
  int unitGet_movesLeft();
  int unitGet_attacksLeft();
  void unitSet_movesLeft(int movesLeft);
  bool building_AI();
  void buildingSet_health(int health);
  int buildingGet_health();
  void buildingSet_AC(int AC);
  int buildingGet_AC();
  string buildingGet_name();
  void building_spawnUnit(string uType, bool AI);
  void turnTick();
  int getTileIncome();
  void killUnit();
  void killBuilding();
  int get_priority();
  ~tile();
};

#endif //TILE_H
