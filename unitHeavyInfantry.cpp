//implements heavy infantry unit
#include "headers.h"
#include "unitHeavyInfantry.h"

unitHeavyInfantry::unitHeavyInfantry(){  //defult constructor
  _health=200;
  _baseHealth=200;
  _AC=6;
  _icon='H';
  _moveSpeed=1;
  _dmg=40;
  _cost=200;
  _attacksLeft=0;
  _movesLeft=0;
  _priority=8;
  _name="heavy infantry";
}

unitHeavyInfantry::unitHeavyInfantry(bool AI){  //constructor with input to set ai ownwership
  _health=200;
  _baseHealth=200;
  _AC=6;
  _icon='H';
  _moveSpeed=1;
  _dmg=40;
  _cost=200;
  _attacksLeft=0;
  _priority=8;
  _name="heavy infantry";
  _AI=AI;
}

void unitHeavyInfantry::tickTurn(){
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
  _movesLeft=_moveSpeed;
  _attacksLeft=1;
}

unitHeavyInfantry::~unitHeavyInfantry(){

}
