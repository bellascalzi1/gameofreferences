#ifndef BUILDING_H
#define BUILDING_H

#include "headers.h"

class building
{
protected:
  int _health;
  int _AC;
  char _icon;
  int _cost;
public:
  building();
  void set_health(int nHealth);
  int get_health();
  int get_AC();
  char get_icon();
  int get_cost();
  virtual void resetInitialStats();
  ~building();
};

#endif //BUILDING_H
