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
bool _AI;
public:
unit();
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
//virtual void resetInitialStats();
~unit();
};

#endif //UNIT_H
