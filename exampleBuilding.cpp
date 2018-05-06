#include "headers.h"
#include "exampleBuilding.h"

exampleBuilding::exampleBuilding(){
  _health=100;
  _AC=4;
  _icon='A';
  _moveSpeed=1;
  _dmg=20;
  _cost=25;
}

void exampleBuilding::resetInitialStats(){
  _health=100;
  _AC=4;
  _icon='A';
  _moveSpeed=1;
  _dmg=20;
  _cost=25;
}

exampleBuilding::~exampleBuilding(){

}
