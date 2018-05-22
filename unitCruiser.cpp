#include "headers.h"
#include "unitCruiser.h"

unitCruiser::unitCruiser() { // default constructor
  _health=50;
  _baseHealth = 50;
  _AC=2;
  _icon='C';
  _moveSpeed=4;
  _dmg=5;
  _cost=300;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=5;
  _name="cruiser";
  _income=-6;

}
unitCruiser::unitCruiser(bool AI) { // constructor with input for AI
  _health=50;
  _baseHealth = 50;
  _AC=2;
  _icon='C';
  _moveSpeed=4;
  _dmg=5;
  _cost=300;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=5;
  _name="cruiser";
  _AI = AI;
  _income=-6;
}

void unitCruiser::tickTurn(){
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
  _movesLeft=_moveSpeed;
  _attacksLeft=1;
}

unitCruiser::~unitCruiser() { // default deconstructor

}
