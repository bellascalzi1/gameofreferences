//defiens unit base class
#ifndef UNIT_H
#define UNIT_H

#include "headers.h"

class unit
{
protected:
  string _name;
  int _health;
  int _baseHealth;
  int _AC;
  char _icon;
  int _moveSpeed;
  int _movesLeft;
  int _dmg;
  int _attacksLeft;
  int _cost;
  bool _AI;
  int _priority;
  int _income;
public:
  unit();
  string get_name();
  void set_health(int health);
  int get_health();
  void set_AC(int AC);
  int get_AC();
  char get_icon();
  int get_moveSpeed();
  void set_moveSpeed(int moveSpeed);
  int get_dmg();
  void set_dmg(int dmg);
  int get_cost();
  int get_income();
  void set_AI(bool AI);
  bool get_AI();
  int get_movesLeft();
  void set_movesLeft(int movesLeft);
  int get_attacksLeft();
  void set_attacksLeft(int attacksLeft);
  virtual void tickTurn();
  int get_priority();
  ~unit();
};

#endif //UNIT_H
