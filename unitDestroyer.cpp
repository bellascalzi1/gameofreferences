#include "headers.h"
#include "unitDestroyer.h"

unitDestroyer::unitDestroyer() { // default constructor
  _health=50;
  _baseHealth = 50;
  _AC=2;
  _icon='D';
  _moveSpeed=3;
  _dmg=100;
  _cost=120;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=12;
  _name="destroyer";
  _income=-12;

}
unitDestroyer::unitDestroyer(bool AI) { // constructor with input for AI
  _health=50;
  _baseHealth = 50;
  _AC=2;
  _icon='D';
  _moveSpeed=3;
  _dmg=100;
  _cost=120;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=12;
  _name="destroyer";
  _income=-12;
  _AI = AI;
}

void unitDestroyer::tickTurn(){
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
  _movesLeft=_moveSpeed;
  _attacksLeft=1;
}
unitDestroyer::~unitDestroyer() { // default deconstructor

}
