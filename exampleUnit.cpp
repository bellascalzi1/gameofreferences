#include "headers.h"
#include "unit.h"

exampleUnit::exampleUnit(){
  _health=100;
  _AC=4;
  _icon='A';
  _moveSpeed=1;
  _dmg=20;
  _cost=25;
}

void exampleUnit::resetInitialStats(){
  _health=100;
  _AC=4;
  _icon='A';
  _moveSpeed=1;
  _dmg=20;
  _cost=25;
}

exampleUnit::~exampleUnit(){

}
