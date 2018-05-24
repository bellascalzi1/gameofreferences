#include "headers.h"
#include "unitCruiser.h"

unitCruiser::unitCruiser() { // default constructor
  _health=250;
  _baseHealth = 250;
  _AC=6;
  _icon='C';
  _moveSpeed=2;
  _dmg=20;
  _cost=100;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=10;
  _name="cruiser";
  _income=-10;

}
unitCruiser::unitCruiser(bool AI) { // constructor with input for AI
  _health=250;
  _baseHealth = 250;
  _AC=6;
  _icon='C';
  _moveSpeed=2;
  _dmg=20;
  _cost=100;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=10;
  _name="cruiser";
  _income=-10;
  _AI = AI;
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
