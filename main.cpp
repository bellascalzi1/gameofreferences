#include "headers.h"
#include "unit.h"
#include "building.h"
#include "tile.h"
#include "exampleUnit.h"
#include "exampleBuilding.h"

void consoleRenderGrid(int sWidth, int sHight) {
	char temp = '+';
	char temp2 = 32;
	for (int j = 0; j < sWidth * 2 + 1; j++) {
		if (j % 2 == 0) {
			cout << setw(2) << temp;
		}
		else {
			cout << setw(2) << temp2;
		}
	}
	cout << "" << endl;
}

void consoleRenderFrame(int sWidth, int sHight, vector<vector<tile> >map) {
  for (int i = 0; i < 4*sHight+2; i++) {
    cout<<"-";
  }
  cout << "" << endl;
	consoleRenderGrid(sWidth, sHight);
	for (int i = 0; i < sHight; i++) {
		char temp = 32;
		cout<<temp;
		for (int j = 0; j < sWidth; j++) {
			cout << setw(3)<< map[j][i].get_icon()<<temp;
		}
		cout << "" << endl;
		consoleRenderGrid(sWidth, sHight);
	}
  for (int i = 0; i < 4*sHight+2; i++) {
    cout<<"-";
  }
  cout << "" << endl;
  cout << "" << endl;
}

bool moveUnit(int Sx, int Sy, int Fx, int Fy, vector<vector<tile> >*map){
  int dist=abs(Fx-Sx)+abs(Fy-Sy);
  if(map[0][Fx][Fy].get_hasUnit()==true or map[0][Sx][Sy].get_hasUnit()==false){
    return false;
  }
  else if(map[0][Sx][Sy].unit_moveSpeed()<dist){
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

bool buildBuilding(int x, int y, vector<vector<tile> >*map, int bType){
	if(map[0][x+1][y].get_hasBuilding()==true or map[0][x-1][y].get_hasBuilding() or map[0][x][y+1].get_hasBuilding() or map[0][x][y-1].get_hasBuilding()){
		switch(bType){
			case 1:
				map[0][x][y].set_hasBuilding(true);
				map[0][x][y].set_building(exampleBuilding());
				return true;
		}
	}
	else{
		return false;
	}
}

int convertToASCII(std::string input_coords) {

	int number;

	std::string input = input_coords;
	number = int(input[0])-65;

	return number;

}

int commandLine(vector<vector<tile> >*map) {

	std::string input;

	while(input != "end" or "endturn") {

		std::cout << "Enter Command: (type end to quit or endturn to end your turn) ";
		std::cin >> input;

		if(input == "end") {

			std::cout << "You have ended the game" << std::endl;
			std::cin.ignore();
			break;
		}
		else if(input == "attack") {

			std::string attacker, attacked;

			std::cout << "Which Unit would you like to attack with? ";
			std::cin >> attacker;

			std::cout << "What Unit would you like to attack? ";
			std::cin >> attacked;


			attackUnit(convertToASCII(attacker), attacker[1]-'0', convertToASCII(attacked), attacked[1]-'0', map);

		}
		else if(input == "move") {

			std::string unit_to_be_moved, new_pos;


			std::cout << "Which Unit would you like to move?";
			std::cin >> unit_to_be_moved;

			std::cout << "Where would you like to move it to?";
			std::cin >> new_pos;

			moveUnit(convertToASCII(unit_to_be_moved), unit_to_be_moved[1]-'0', convertToASCII(new_pos), new_pos[1]-'0', map);

		}
		else if(input == "look") {

			std::string tile;


			std::cout << "Where would you like to look?";
			std::cin >> tile;

			printTileInfo(convertToASCII(tile), tile[1]-'0',map);

		}
		else{

			std::cout << "That is not a valid command" << std::endl;
		}
	}

	return 0;



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
  consoleRenderFrame(width, height, map);
	commandLine(&map);
  /*if(moveUnit(1,1,0,0,&map)==false){
    cout<<"unable to move here"<<endl;
  }
  else{
      consoleRenderFrame(width, height, map);
  }
  if(attackUnit(1,0,0,0,&map)==false){
    cout<<"unable to attack"<<endl;
  }
  else{
    cout<<"attack compleate"<<endl;
  }
	if(buildBuilding(1,1,&map,1)==false){
    cout<<"unable to build here"<<endl;
  }
  else{
      consoleRenderFrame(width, height, map);
  }
  printTileInfo(1,0,&map);*/
  cout<<"done"<<endl;
  return 0;
}
