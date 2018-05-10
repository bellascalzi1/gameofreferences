#include "headers.h"
#include "unit.h"
#include "building.h"
#include "tile.h"
#include "buildingTypes.h"
#include "unitTypes.h"

int width=11;
int height=11;
int playerRec=0;
int AIRec=0;

void consoleRenderGrid(int sWidth, int sHight) { //renders the grid around the map in console
	char temp = '+';
	char temp2 = 32;
	cout << setw(2) << temp2;
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

void consoleRenderAlphCoord(int sWidth, int sHight) { //renders the top coords around the map in console
	char temp = 'A';
	char temp2 = 32;
	cout << setw(2) << temp2;
	cout << setw(2) << temp2;
	for (int j = 0; j < sWidth * 2 + 1; j++) {
		if (j % 2 == 0) {
			cout << setw(2) << temp2;
		}
		else {
			char temp3=temp+(j/2);
			cout << setw(2) << temp3;
		}
	}
	cout << "" << endl;
}

void consoleRenderFrame(int sWidth, int sHight, vector<vector<tile> >map) { //renders the map to the console
  for (int i = 0; i < 4*sWidth+4; i++) {
    cout<<"-";
  }
  cout << "" << endl;
	consoleRenderAlphCoord(sWidth, sHight);
	consoleRenderGrid(sWidth, sHight);
	for (int i = 0; i < sHight; i++) {
		char temp = 32;
		cout<<i;
		cout<<temp;
		cout<<temp;
		for (int j = 0; j < sWidth; j++) {
			cout << setw(3)<< map[j][i].get_icon()<<temp;
		}
		cout << "" << endl;
		consoleRenderGrid(sWidth, sHight);
	}
  for (int i = 0; i < 4*sWidth+4; i++) {
    cout<<"-";
  }
  cout << "" << endl;
  cout << "" << endl;
}

bool moveUnit(int Sx, int Sy, int Fx, int Fy, vector<vector<tile> >*map){ //moves unit from one place to another if posible
  int dist=abs(Fx-Sx)+abs(Fy-Sy);
  if(map[0][Fx][Fy].get_hasUnit()==true){
		cout<<"There is already a unit here"<<endl;
    return false;
  }
	else if(map[0][Sx][Sy].get_hasUnit()==false){
		cout<<"No unit selected"<<endl;
		return false;
	}
  else if(map[0][Sx][Sy].unit_moveSpeed()<dist){
		cout<<"Out of movement range"<<endl;
    return false;
  }
  else{
    map[0][Fx][Fy].set_unit(map[0][Sx][Sy].get_unit());
    map[0][Sx][Sy].set_hasUnit(false);
    map[0][Fx][Fy].set_hasUnit(true);
		consoleRenderFrame(width, height, *map);
    return true;
  }
}

bool attackUnit(int Ax, int Ay, int Dx, int Dy, vector<vector<tile> >*map){  //attacks unit with another if posible
  int dist=abs(Dx-Ax)+abs(Dy-Ay);
  if(dist>1){
		cout<<"Unit out of range"<<endl;
    return false;
  }
  /*else if(map[0][Dx][Dy].unit_AI()==map[0][Ax][Ay].unit_AI()){
		cout<<"This unit is friendly"<<endl;
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

void printTileInfo(int x, int y, vector<vector<tile> >*map){  //prints the details of a tile to the console
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

bool buildBuilding(int x, int y, vector<vector<tile> >*map, string bType){   //creates a new building if posible
	if(map[0][x+1][y].get_hasBuilding()==true or map[0][x-1][y].get_hasBuilding() or map[0][x][y+1].get_hasBuilding() or map[0][x][y-1].get_hasBuilding()){
		if(bType=="example"){
				map[0][x][y].set_hasBuilding(true);
				map[0][x][y].set_building(new exampleBuilding());
				consoleRenderFrame(width, height, *map);
				return true;
		}
		else if(bType=="barracks"){
			map[0][x][y].set_hasBuilding(true);
			map[0][x][y].set_building(new buildingBarrack());
			consoleRenderFrame(width, height, *map);
			map[0][x][y].set_isSpawner(true);
			return true;
		}
		else{
			cout<<"Invalid building type"<<endl;
			return false;
		}
	}
	else{
		cout<<"Unable to build here"<<endl;
		return false;
	}
}

int convertToASCII(string input_coords) {   //convers a character into int coord

	int number;

	string input = input_coords;
	number = int(input[0])-65;

	return number;

}

void spawnUnit(int x, int y, vector<vector<tile> >*map, string uType){
	if(map[0][x][y].get_hasUnit()==true){
		cout<<"This tile already has a unit in it"<<endl;
	}
	else if(map[0][x][y].get_isSpawner()==false){
		cout<<"This tile cannot spawn units"<<endl;
	}
	else{
		map[0][x][y].building_spawnUnit(uType);
	}
}

void income(tile map){
	if(map.get_hasUnit()==true){
		if(map.unit_AI()==true){
			AIRec+=map.getTileIncome();
		}
		else{
			playerRec+=map.getTileIncome();
		}
	}
	else if(map.get_hasUnit()==true){
		if(map.building_AI()==true){
			AIRec+=map.getTileIncome();
		}
		else{
			playerRec+=map.getTileIncome();
		}
	}
	else{

	}
}

void endTurn(vector<vector<tile> >*map){
	for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
			income(map[0][j][i]);
      map[0][j][i].turnTick();
    }
  }
}

void commandLine(vector<vector<tile> >*map, bool *gameRunning) {  //takes and interperates players input commands

	string input;

	while(input != "end" or "endturn") {

		cout << "Enter Command: (type end to quit or endturn to end your turn) ";
		cin >> input;

		if(input == "endTurn") {
			//cout << "You have ended the turn" << std::endl;
			//cin.ignore();
			break;
		}
		else if(input == "end") {
			cout << "You have ended the game" << std::endl;
			cin.ignore();
			*gameRunning=false;
			break;
		}
		else if(input == "attack") {

			string attacker, attacked;

			cout << "Which Unit would you like to attack with? ";
			cin >> attacker;

			cout << "What Unit would you like to attack? ";
			cin >> attacked;


			attackUnit(convertToASCII(attacker), attacker[1]-'0', convertToASCII(attacked), attacked[1]-'0', map);

		}
		else if(input == "move") {

			string unit_to_be_moved, new_pos;


			cout << "Which Unit would you like to move?";
			cin >> unit_to_be_moved;

			cout << "Where would you like to move it to?";
			cin >> new_pos;

			moveUnit(convertToASCII(unit_to_be_moved), unit_to_be_moved[1]-'0', convertToASCII(new_pos), new_pos[1]-'0', map);

		}
		else if(input == "look") {

			string tile;


			cout << "Where would you like to look?";
			cin >> tile;

			printTileInfo(convertToASCII(tile), tile[1]-'0',map);

		}
		else if(input == "build") {

			string tile;
			string bType;


			cout << "Where would you like to build?";
			cin >> tile;

			cout << "What would you like to build?";
			cin >> bType;

			buildBuilding(convertToASCII(tile), tile[1]-'0',map,bType);

		}
		else if(input == "spawn") {

			string tile;
			string uType;


			cout << "Which building would you like to spawn unit at?";
			cin >> tile;

			cout << "What unit you like to spawn?";
			cin >> uType;

			spawnUnit(convertToASCII(tile), tile[1]-'0',map,uType);
			}
		else{

			std::cout << "That is not a valid command" << std::endl;
		}
	}
}

int main(){
  vector<vector<tile> >map;  //sets up the map
  map.resize(width);
  for(int i=0;i<width;i++){
    map[i].resize(height);
  }
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      map[j][i]=tile();
    }
  }
	map[width/2][0].set_building(new buildingBase(true));
	map[width/2][0].set_hasBuilding(true);
	map[width/2][height-1].set_building(new buildingBase());
	map[width/2][height-1].set_hasBuilding(true);
  consoleRenderFrame(width, height, map);  //renders initial screen
	bool gameRunning=true;
	while(gameRunning==true){
		commandLine(&map,&gameRunning);   //runs console
		endTurn(&map);
		cout<<"Turn over"<<endl;
	}
	cout<<playerRec<<":"<<AIRec<<endl;
  cout<<"done"<<endl;   //testing output to see that game has finished with no errors
  return 0;
}
