#include "headers.h"
#include "unitInfantry.h"

unitIfantry::unitIfantry(){
  _health=100;
  _AC=4;
  _icon='I';
  _moveSpeed=3;
  _dmg=20;
  _cost=75;
  _name="infantry";
}

unitIfantry::unitIfantry(bool AI){
  _health=100;
  _AC=3;
  _icon='I';
  _moveSpeed=3;
  _dmg=20;
  _cost=75;
  _name="infantry";
  _AI=AI;
}

unitIfantry::~unitIfantry(){

}
