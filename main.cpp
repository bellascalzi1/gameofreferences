#include "headers.h"
#include "unit.h"
#include "building.h"
#include "tile.h"

void moveUnit(int x, int y, int x1, int y1){
  map[x1][y1].set_unit()=map[x][y].get_unit();

}

void createUnit(int x, int y){
  unit temp;
  map[x][y].set_unit(temp);
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
  cout<<"done"<<endl;
  return 0;
}
