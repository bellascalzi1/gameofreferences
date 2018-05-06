#include "headers.h"
#include "unit.h"
#include "building.h"
#include "tile.h"
#include "exampleUnit.h"

bool moveUnit(int x, int y, int x1, int y1, vector<vector<tile> >*map){
  int dist=abs(x1-x)+abs(y1-y);
  if(map[0][x1][y1].get_hasUnit()==true or map[0][x][y].get_hasUnit()==false){
    return false;
  }
  else if(map[0][x][y].getUnits_moveSpeed()<dist){
    return false;
  }
  else{
    map[0][x1][y1].set_unit(map[0][x][y].get_unit());
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
  if(moveUnit(1,1,0,0,&map)==false){
    cout<<"unable to move here"<<endl;
  }
  else{
      cout<<map[0][0].get_icon()<<endl;
  }
  cout<<"done"<<endl;
  return 0;
}
