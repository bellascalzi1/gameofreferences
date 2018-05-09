//impliments light infantry unit
#include "headers.h"
#include "unitLightInfantry.h"

unitLightInfantry::unitLightInfantry(){  //defult constructor
  _health=50;
  _AC=1;
  _icon='L';
  _moveSpeed=5;
  _dmg=10;
  _cost=40;
  _name="light infantry";
}

unitLightInfantry::unitLightInfantry(bool AI){  //constructor wih input to set AI ownership
  _health=50;
  _AC=1;
  _icon='L';
  _moveSpeed=5;
  _dmg=10;
  _cost=40;
  _name="light infantry";
  _AI=AI;
}

unitLightInfantry::~unitLightInfantry(){  //defult deconstructor

}
