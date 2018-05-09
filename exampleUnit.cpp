//impliments example unit for testing
#include "headers.h"
#include "exampleUnit.h"

exampleUnit::exampleUnit(){  //defult constructor
  _health=100;
  _AC=4;
  _icon='A';
  _moveSpeed=2;
  _dmg=20;
  _cost=25;
  _name="example";
}

exampleUnit::exampleUnit(bool AI){ //constructor with input for AI ownership
  _health=100;
  _AC=4;
  _icon='A';
  _moveSpeed=2;
  _dmg=20;
  _cost=25;
  _name="example";
  _AI=AI;
}

exampleUnit::~exampleUnit(){  //defult deconstructor

}
