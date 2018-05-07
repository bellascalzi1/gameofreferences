#include "headers.h"
#include "unit.h"
#include "building.h"
#include "tile.h"
#include "exampleUnit.h"
#include "exampleBuilding.h"

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
    int dmgDef=map[0][Ax][Ay].unitGet_dmg()-map[0][Dx][Dy].unitGet_AC();      //damage delt to defender
    int dmgAtk=round((0.75*map[0][Dx][Dy].unitGet_dmg())-map[0][Dx][Dy].unitGet_AC());      //damage delt to attacker
    map[0][Dx][Dy].unitSet_health(map[0][Dx][Dy].unitGet_health()-dmgDef);
    map[0][Ax][Ay].unitSet_health(map[0][Ax][Ay].unitGet_health()-dmgAtk);
    return true;
  }
}

void printTileInfo(int x, int y, vector<vector<tile> >*map){
  cout<<"TILE INFO:"<<endl;
  char temp=65+x;
  cout<<"Tile: "<<temp<<y<<endl;
  if(map[0][x][y].get_hasBuilding()==true){
    cout<<"Building present: yes"<<endl;
    cout<<"-Building name: "<<map[0][x][y].buildingGet_name()<<endl;
    cout<<"-Building health: "<<map[0][x][y].buildingGet_health()<<endl;
    cout<<"-Building AC: "<<map[0][x][y].buildingGet_AC()<<endl;
    if(map[0][x][y].building_AI()==true){
      cout<<"-Building owner: AI"<<endl;
    }
    else{
      cout<<"-Building owner: player"<<endl;
    }
  }
  else{
    cout<<"Building present: no"<<endl;
  }
  if(map[0][x][y].get_hasUnit()==true){
    cout<<"Unit present: yes"<<endl;
    cout<<"-Unit name: "<<map[0][x][y].unitGet_name()<<endl;
    cout<<"-Unit health: "<<map[0][x][y].unitGet_health()<<endl;
    cout<<"-Unit AC: "<<map[0][x][y].unitGet_AC()<<endl;
    if(map[0][x][y].unit_AI()==true){
      cout<<"-Unit owner: AI"<<endl;
    }
    else{
      cout<<"-Unit owner: player"<<endl;
    }
  }
  else{
    cout<<"Unit present: no"<<endl;
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
  map[1][0].set_building(exampleBuilding());
  map[1][0].set_hasBuilding(true);
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
  printTileInfo(1,0,&map);
  cout<<"done"<<endl;
  return 0;
}
