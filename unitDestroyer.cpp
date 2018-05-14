#include "headers.h"
#include "unitDestroyer.h"

unitDestroyer::unitDestroyer() { // default constructor
  _health=200;
  _baseHealth = 200;
  _AC=5;
  _icon='D';
  _moveSpeed=1;
  _dmg=30;
  _cost=450;
  _attacksLeft = 0;
  _movesLeft = 0;
  _name="destroyer";

}
unitDestroyer::unitDestroyer(bool AI) { // constructor with input for AI
  _health=200;
  _baseHealth = 200;
  _AC=5;
  _icon='D';
  _moveSpeed=1;
  _dmg=30;
  _cost=450;
  _attacksLeft = 0;
  _movesLeft = 0;
  _name="destroyer";
  _AI = AI;
}

void unitDestroyer::tickTurn(){
  if(_health<_baseHealth){
    _health=round(_baseHealth*1.1);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
  _movesLeft=_moveSpeed;
  _attacksLeft=1;
}
unitDestroyer::~unitDestroyer() { // default deconstructor

}
