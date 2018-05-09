//impliments example building for testing purposes
#include "headers.h"
#include "exampleBuilding.h"

exampleBuilding::exampleBuilding(){  //defult constructor
  _health=100;
  _AC=4;
  _icon='E';
  _cost=25;
  _name="example";
  _AI=false;
}

exampleBuilding::exampleBuilding(bool AI){  //constructor with input for AI ownership
  _health=100;
  _AC=4;
  _icon='B';
  _cost=25;
  _name="example";
  _AI=AI;
}

exampleBuilding::~exampleBuilding(){  //defult deconstructor

}
