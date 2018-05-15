//defines building base class
#ifndef BUILDING_H
#define BUILDING_H

#include "headers.h"
#include "unit.h"

class building
{
protected:
  string _name;
  int _health;
  int _baseHealth;
  int _AC;
  char _icon;
  int _cost;
  bool _AI;
  int _buildingIncome;
  bool _hasSpawned;
  int _priority;
public:
  building();
  string get_name();
  void set_health(int nHealth);
  int get_health();
  virtual unit* spawnUnit(string uType);
  int get_AC();
  void set_AC(int AC);
  char get_icon();
  int get_cost();
  void set_AI(bool AI);
  bool get_AI();
  void set_hasSpawned(bool hasSpawned);
  bool get_hasSpawned();
  int get_buildingIncome();
  virtual void tickTurn();
  int get_priority();
  ~building();
};

#endif //BUILDING_H
