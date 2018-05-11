//impliments building main base
#include "headers.h"
#include "buildingBase.h"

buildingBase::buildingBase(){  //defult constructor
  _health=500;
  _baseHealth=500;
  _AC=8;
  _icon='B';
  _cost=0;
  _name="Main base";
  _buildingIncome=100;
  _AI=false;
}

buildingBase::buildingBase(bool AI){  //constructor with input for AI ownership
  _health=500;
  _baseHealth=500;
  _AC=8;
  _icon='B';
  _cost=0;
  _name="Main base";
  _buildingIncome=100;
  _AI=AI;
}

void buildingBase::tickTurn(){
  if(_health<_baseHealth){
    _health=round(_baseHealth*1.1);
    if(_health>_baseHealth){
      _health=_baseHealth;
    }
  }
}

buildingBase::~buildingBase(){  //defult deconstructor

}
