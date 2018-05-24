//impliments building main base
#include "headers.h"
#include "buildingBase.h"

buildingBase::buildingBase(){  //defult constructor
  _health=400;
  _baseHealth=400;
  _AC=8;
  _icon='B';
  _cost=0;
  _name="Main base";
  _buildingIncome=100;
  _priority=15;
  _AI=false;
}

buildingBase::buildingBase(bool AI){  //constructor with input for AI ownership
  _health=400;
  _baseHealth=400;
  _AC=8;
  _icon='B';
  _cost=0;
  _name="Main base";
  _buildingIncome=100;
  _priority=15;
  _AI=AI;
}

void buildingBase::tickTurn(){
  if(_health<_baseHealth){
    cout<<_health<<endl;
    _health=_health+round(_baseHealth*0.01);
    cout<<_health<<endl;
    if(_health>_baseHealth){
      _health=_baseHealth;
      cout<<_health<<endl;
    }
  }
}

buildingBase::~buildingBase(){  //defult deconstructor

}
