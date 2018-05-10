#include "headers.h"
#include "shocklauncher.h"

shocklauncher::shocklauncher() { // default constructor
  _health=50;
  _AC=1;
  _icon='S';
  _moveSpeed=1;
  _dmg=16;
  _cost=500;
  _name="shocklauncher";

}
shocklauncher::shocklauncher(bool AI) { // constructor with input for AI
  _health=50;
  _AC=1;
  _icon='S';
  _moveSpeed=1;
  _dmg=16;
  _cost=500;
  _name="shocklauncher";
  _AI = AI;
}
shocklauncher::~shocklauncher() { // default deconstructor

}
