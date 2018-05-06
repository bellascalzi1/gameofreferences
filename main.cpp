#include "headers.h"
#include "unit.h"
#include "building.h"
#include "tile.h"
#include "exampleUnit.h"

bool moveUnit(int Sx, int Sy, int Fx, int Fy, vector<vector<tile> >*map){
  int dist=abs(Fx-Sx)+abs(Fy-Sy);
  if(map[0][Fx][Fy].get_hasUnit()==true or map[0][Sx][Sy].get_hasUnit()==false){
    cout<<"code: 1"<<endl;
    return false;
  }
  else if(map[0][Sx][Sy].unit_moveSpeed()<dist){
    cout<<"code: 2"<<endl;
    return false;
  }
  else{
    map[0][Fx][Fy].set_unit(map[0][Sx][Sy].get_unit());
    map[0][Sx][Sy].set_hasUnit(false);
    map[0][Fx][Fy].set_hasUnit(true);
    return true;
  }
}

bool attackUnit(int Ax, int Ay, int Dx, int Dy, vector<vector<tile> >*map){
  int dist=abs(Dx-Ax)+abs(Dy-Ay);
  if(dist>1){
    return false;
  }
  /*else if(map[0][Dx][Dy].unit_AI()==map[0][Ax][Ay].unit_AI()){
    return false;
  }*/
  else{
    int dmgDef=map[0][Ax][Ay].unitGet_dmg()-map[0][Dx][Dy].unitSet_AC();      //damage delt to defender
    int dmgAtk=round((0.75*map[0][Dx][Dy].unitGet_dmg())-map[0][Dx][Dy].unitSet_AC());      //damage delt to attacker
    map[0][Dx][Dy].unitSet_health(map[0][Dx][Dy].unitGet_health()-dmgDef);
    map[0][Ax][Ay].unitSet_health(map[0][Ax][Ay].unitGet_health()-dmgAtk);
    return true;
  }
}

int main(){
  int width=10;
  int height=10;
  vector<vector<tile> >map;
  map.resize(width);
  for(int i=0;i<width;i++){
    map[i].resize(height);
  }
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      map[j][i]=tile();
    }
  }
  map[1][1].set_unit(exampleUnit());
  map[1][1].set_hasUnit(true);
  map[1][0].set_unit(exampleUnit());
  map[1][0].set_hasUnit(true);
  if(moveUnit(1,1,0,0,&map)==false){
    cout<<"unable to move here"<<endl;
  }
  else{
      cout<<map[0][0].get_icon()<<endl;
  }
  if(attackUnit(1,0,0,0,&map)==false){
    cout<<"unable to attack"<<endl;
  }
  else{
      cout<<map[1][0].unitGet_health()<<endl;
      cout<<map[0][0].unitGet_health()<<endl;
  }
  cout<<"done"<<endl;
  return 0;
}
