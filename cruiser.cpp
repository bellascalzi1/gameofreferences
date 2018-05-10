#include "headers.h"
#include "cruiser.h"

cruiser::cruiser() { // default constructor
  _health=50;
  _AC=2;
  _icon='C';
  _moveSpeed=6;
  _dmg=5;
  _cost=300;
  _name="cruiser";

}
cruiser::cruiser(bool AI) { // constructor with input for AI
  _health=50;
  _AC=2;
  _icon='C';
  _moveSpeed=6;
  _dmg=5;
  _cost=300;
  _name="cruiser";
  _AI = AI;
}
cruiser::~cruiser() { // default deconstructor

}
