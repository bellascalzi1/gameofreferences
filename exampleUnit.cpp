#include "headers.h"
#include "exampleUnit.h"

exampleUnit::exampleUnit(){
  _health=100;
  _AC=4;
  _icon='A';
  _moveSpeed=2;
  _dmg=20;
  _cost=25;
  _name="example";
}

exampleUnit::exampleUnit(bool AI){
  _health=100;
  _AC=4;
  _icon='A';
  _moveSpeed=2;
  _dmg=20;
  _cost=25;
  _name="example";
  _AI=AI;
}

exampleUnit::~exampleUnit(){

}
