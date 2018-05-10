#include "headers.h"
#include "destroyer.h"

destroyer::destroyer() { // default constructor
  _health=200;
  _AC=5;
  _icon='D';
  _moveSpeed=1;
  _dmg=15;
  _cost=450;
  _name="destroyer";

}
destroyer::destroyer(bool AI) { // constructor with input for AI
  _health=200;
  _AC=5;
  _icon='D';
  _moveSpeed=1;
  _dmg=15;
  _cost=450;
  _name="destroyer";
  _AI = AI;
}
destroyer::~destroyer() { // default deconstructor

}
