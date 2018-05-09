#include "headers.h"
#include "unitHeavyInfantry.h"

unitHeavyInfantry::unitHeavyInfantry(){
  _health=200;
  _AC=6;
  _icon='H';
  _moveSpeed=1;
  _dmg=40;
  _cost=200;
  _name="heavy infantry";
}

unitHeavyInfantry::unitHeavyInfantry(bool AI){
  _health=200;
  _AC=6;
  _icon='H';
  _moveSpeed=1;
  _dmg=40;
  _cost=200;
  _name="heavy infantry";
  _AI=AI;
}

unitHeavyInfantry::~unitHeavyInfantry(){

}
