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
  void set_AI(bool AI);
  bool get_AI();
  int get_movesLeft();
  void set_movesLeft(int movesLeft);
  int get_attacksLeft();
  void set_attacksLeft(int attacksLeft);
  virtual void tickTurn();
  ~unit();
};

#endif //UNIT_H
