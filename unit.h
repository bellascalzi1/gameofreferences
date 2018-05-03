#ifndef UNIT_H
#define UNIT_H

#include "headers.h"

class unit
{
protected:
int _health;
int _AC;
char _icon;
int _moveSpeed;
int _dmg;
int _cost;
public:
unit();
void set_health(int nHealth);
int get_health();
int get_AC();
char get_icon();
int get_moveSpeed();
int get_dmg();
int get_cost();
virtual void resetInitialStats();
~unit();
};

#endif //UNIT_H
