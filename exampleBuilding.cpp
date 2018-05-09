#include "headers.h"
#include "exampleBuilding.h"

exampleBuilding::exampleBuilding(){
  _health=100;
  _AC=4;
  _icon='B';
  _cost=25;
  _name="example";
  _AI=false;
}

exampleBuilding::exampleBuilding(bool AI){
  _health=100;
  _AC=4;
  _icon='B';
  _cost=25;
  _name="example";
  _AI=AI;
}

/*void exampleBuilding::resetInitialStats(){
  _health=100;
  _AC=4;
  _icon='B';
  _cost=25;
}*/

exampleBuilding::~exampleBuilding(){

}
