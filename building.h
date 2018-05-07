#ifndef BUILDING_H
#define BUILDING_H

#include "headers.h"

class building
{
protected:
  string _name;
  int _health;
  int _AC;
  char _icon;
  int _cost;
  bool _AI;
public:
  building();
  string get_name();
  void set_health(int nHealth);
  int get_health();
  int get_AC();
  void set_AC(int AC);
  char get_icon();
  int get_cost();
  void set_AI(bool AI);
  bool get_AI();
  //virtual void resetInitialStats();
  ~building();
};

#endif //BUILDING_H
