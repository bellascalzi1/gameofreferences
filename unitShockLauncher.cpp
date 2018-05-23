#include "headers.h"
#include "unitShockLauncher.h"

unitShockLauncher::unitShockLauncher() { // default constructor
  _health=120;
  _baseHealth = 120;
  _AC=3;
  _icon='S';
  _moveSpeed=3;
  _dmg=35;
  _cost=80;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=8;
  _name="shocklauncher";
  _income=-8;

}
unitShockLauncher::unitShockLauncher(bool AI) { // constructor with input for AI
  _health=120;
  _baseHealth = 120;
  _AC=3;
  _icon='S';
  _moveSpeed=3;
  _dmg=35;
  _cost=80;
  _attacksLeft = 0;
  _movesLeft = 0;
  _priority=8;
  _name="shocklauncher";
  _income=-8;
  _name="shocklauncher";
  _AI = AI;
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
