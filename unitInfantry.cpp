//impliments infantry unit type
#include "headers.h"
#include "unitInfantry.h"

unitInfantry::unitInfantry(){  //defult constructor
  _health=100;
  _AC=4;
  _icon='I';
  _moveSpeed=3;
  _dmg=20;
  _cost=75;
  _name="infantry";
}

unitInfantry::unitInfantry(bool AI){   //constructor with input to set AI ownership
  _health=100;
  _AC=3;
  _icon='I';
  _moveSpeed=3;
  _dmg=20;
  _cost=75;
  _name="infantry";
  _AI=AI;
}

unitInfantry::~unitInfantry(){  //defult deconstructor

}
