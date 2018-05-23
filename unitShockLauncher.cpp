#include "headers.h"
#include "unitShockLauncher.h"

unitShockLauncher::unitShockLauncher() { // default constructor
  _health=80;
  _baseHealth = 80;
  _AC=1;
  _icon='S';
  _moveSpeed=1;
  _dmg=30;
  _cost=65;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=7;
  _name="shocklauncher";
  _income=-10;

}
unitShockLauncher::unitShockLauncher(bool AI) { // constructor with input for AI
  _health=80;
  _baseHealth = 80;
  _AC=1;
  _icon='S';
  _moveSpeed=1;
  _dmg=30;
  _cost=65;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=7;
  _name="shocklauncher";
  _AI = AI;
  _income=-10;
}

void unitShockLauncher::tickTurn(){
  if(_health<_baseHealth){
    _health=_health+round(_baseHealth*0.02);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
  _movesLeft=_moveSpeed;
  _attacksLeft=1;
}

unitShockLauncher::~unitShockLauncher() { // default deconstructor

}
