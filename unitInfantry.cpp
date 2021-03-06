//impliments infantry unit type
#include "headers.h"
#include "unitInfantry.h"

unitInfantry::unitInfantry(){  //defult constructor
  _health=100;
  _baseHealth=100;
  _AC=4;
  _icon='I';
  _moveSpeed=3;
  _dmg=20;
  _cost=70;
  _attacksLeft=0;
  _movesLeft=0;
  _priority=7;
  _name="infantry";
  _income=-7;
}

unitInfantry::unitInfantry(bool AI){   //constructor with input to set AI ownership
  _health=100;
  _baseHealth=100;
  _AC=4;
  _icon='I';
  _moveSpeed=3;
  _dmg=20;
  _cost=70;
  _attacksLeft=0;
  _movesLeft=0;
  _priority=7;
  _name="infantry";
  _income=-7;
  _AI=AI;
}

void unitInfantry::tickTurn(){
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
  _movesLeft=_moveSpeed;
  _attacksLeft=1;
}

unitInfantry::~unitInfantry(){  //defult deconstructor

}
