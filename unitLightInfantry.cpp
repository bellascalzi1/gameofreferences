//impliments light infantry unit
#include "headers.h"
#include "unitLightInfantry.h"

unitLightInfantry::unitLightInfantry(){  //defult constructor
  _health=50;
  _baseHealth=50;
  _AC=1;
  _icon='L';
  _moveSpeed=5;
  _dmg=10;
  _cost=35;
  _attacksLeft=0;
  _movesLeft=0;
  _priority=4;
  _name="light infantry";
  _income=-4;
}

unitLightInfantry::unitLightInfantry(bool AI){  //constructor wih input to set AI ownership
  _health=50;
  _baseHealth=50;
  _AC=1;
  _icon='L';
  _moveSpeed=5;
  _dmg=10;
  _cost=35;
  _attacksLeft=0;
  _movesLeft=0;
  _priority=4;
  _name="light infantry";
  _income=-4;
  _AI=AI;
}

void unitLightInfantry::tickTurn(){
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
  _movesLeft=_moveSpeed;
  _attacksLeft=1;
}

unitLightInfantry::~unitLightInfantry(){  //defult deconstructor

}
