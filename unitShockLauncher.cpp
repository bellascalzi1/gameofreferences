#include "headers.h"
#include "unitShockLauncher.h"

unitShockLauncher::unitShockLauncher() { // default constructor
  _health=50;
  _baseHealth = 50;
  _AC=1;
  _icon='S';
  _moveSpeed=1;
  _dmg=16;
  _cost=500;
  _attacksLeft = 0;
  _movesLeft = 0;
  _name="shocklauncher";

}
unitShockLauncher::unitShockLauncher(bool AI) { // constructor with input for AI
  _health=50;
  _baseHealth = 50;
  _AC=1;
  _icon='S';
  _moveSpeed=1;
  _dmg=16;
  _cost=500;
  _attacksLeft = 0;
  _movesLeft = 0;
  _name="shocklauncher";
  _AI = AI;
}

void unitShockLauncher::tickTurn(){
  if(_health<_baseHealth){
    _health=round(_baseHealth*1.1);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
  _movesLeft=_moveSpeed;
  _attacksLeft=1;
}

unitShockLauncher::~unitShockLauncher() { // default deconstructor

}
