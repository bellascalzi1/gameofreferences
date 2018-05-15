#include "headers.h"
#include "unit.h"
#include "building.h"
#include "tile.h"
#include "buildingTypes.h"
#include "unitTypes.h"

int width=11;
int height=11;
int playerRec=100;
int AIRec=100;
bool gameRunning=true;

struct task{
	int type;
	int priority;
	int id;
};

struct assignment{
	int type;
	int score;
	int id;
	int unitId;
};

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
	//cout << setw(2) << temp2;
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
		if(i<10){
		cout<<temp;
		}
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
  cout <<"Recources: "<<playerRec<< endl;
  cout << "" << endl;
}

int moveUnit(int Sx, int Sy, int Fx, int Fy, vector<vector<tile> >*map){ //moves unit from one place to another if posible
  int dist=abs(Fx-Sx)+abs(Fy-Sy);
  if(map[0][Fx][Fy].get_hasUnit()==true){
		//already has unit
    return 1;
  }
	else if(map[0][Sx][Sy].get_hasUnit()==false){
		//no unit to move
		return 2;
	}
  else if(map[0][Sx][Sy].unitGet_movesLeft()<dist){
		//out of range
    return 3;
  }
  else{
    map[0][Fx][Fy].set_unit(map[0][Sx][Sy].get_unit());
    map[0][Sx][Sy].set_hasUnit(false);
    map[0][Fx][Fy].set_hasUnit(true);
		map[0][Fx][Fy].unitSet_movesLeft(map[0][Fx][Fy].unitGet_movesLeft()-dist);
    return 0;
  }
}

int attack(int Ax, int Ay, int Dx, int Dy, vector<vector<tile> >*map){  //attacks unit with another if posible
  int dist=abs(Dx-Ax)+abs(Dy-Ay);
	if(map[0][Ax][Ay].get_hasUnit()==false){
		//no unit
    return 1;
	}
	else if(map[0][Dx][Dy].get_hasUnit()==false or map[0][Dx][Dy].get_hasBuilding()==false){
		//no target
		return 2;
	}
  else if(dist>1){
		//out of range
    return 3;
  }
	else{
		if(map[0][Dx][Dy].get_hasUnit()==true and map[0][Dx][Dy].get_hasBuilding()==true){ //attacking building with unit
			if(map[0][Dx][Dy].building_AI()==map[0][Ax][Ay].unit_AI()){
				//building is friendly
				return 4;
			}
			else{
				int dmgDef=map[0][Ax][Ay].unitGet_dmg()-map[0][Dx][Dy].buildingGet_AC();      //damage delt to defender
				int dmgAtk=round((0.75*map[0][Dx][Dy].unitGet_dmg())-map[0][Ax][Ay].unitGet_AC());      //damage delt to attacker
				map[0][Dx][Dy].buildingSet_health(map[0][Dx][Dy].buildingGet_health()-dmgDef);
				map[0][Ax][Ay].unitSet_health(map[0][Ax][Ay].unitGet_health()-dmgAtk);
				if(map[0][Dx][Dy].buildingGet_health()<=0){
					map[0][Dx][Dy].killBuilding();
				}
				if(map[0][Ax][Ay].unitGet_health()<=0){
					map[0][Ax][Ay].killUnit();
				}
				return 0;
			}
		}
		else if(map[0][Dx][Dy].get_hasBuilding()==true){   //attacking building
			if(map[0][Dx][Dy].building_AI()==map[0][Ax][Ay].unit_AI()){
				//building is frendly
				return 4;
			}
			else{
				int dmgDef=map[0][Ax][Ay].unitGet_dmg()-map[0][Dx][Dy].buildingGet_AC();      //damage delt to defender
				//int dmgAtk=round((0.75*map[0][Dx][Dy].unitGet_dmg())-map[0][Ax][Ay].unitGet_AC());      //damage delt to attacker
				map[0][Dx][Dy].buildingSet_health(map[0][Dx][Dy].buildingGet_health()-dmgDef);
				//map[0][Ax][Ay].unitSet_health(map[0][Ax][Ay].unitGet_health()-dmgAtk);
				if(map[0][Dx][Dy].buildingGet_health()<=0){
					map[0][Dx][Dy].killBuilding();
				}
				if(map[0][Ax][Ay].unitGet_health()<=0){
					map[0][Ax][Ay].killUnit();
				}
				return 0;
			}
		}
		else{ //attacking unit
			if(map[0][Dx][Dy].unit_AI()==map[0][Ax][Ay].unit_AI()){
				//unit is friendly
				return 5;
			}
			else{
				int dmgDef=map[0][Ax][Ay].unitGet_dmg()-map[0][Dx][Dy].unitGet_AC();      //damage delt to defender
				int dmgAtk=round((0.75*map[0][Dx][Dy].unitGet_dmg())-map[0][Ax][Ay].unitGet_AC());      //damage delt to attacker
				map[0][Dx][Dy].unitSet_health(map[0][Dx][Dy].unitGet_health()-dmgDef);
				map[0][Ax][Ay].unitSet_health(map[0][Ax][Ay].unitGet_health()-dmgAtk);
				if(map[0][Dx][Dy].unitGet_health()<=0){
					map[0][Dx][Dy].killUnit();
				}
				if(map[0][Ax][Ay].unitGet_health()<=0){
					map[0][Ax][Ay].killUnit();
				}
				return 0;
			}
		}
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
		cout<<"-Unit moves left: "<<map[0][x][y].unitGet_movesLeft()<<endl;
		cout<<"-Unit damage: "<<map[0][x][y].unitGet_dmg()<<endl;
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

int createBuilding(int x, int y, vector<vector<tile> >*map, string bType){
	if(bType=="example"){
			map[0][x][y].set_hasBuilding(true);
			map[0][x][y].set_building(new exampleBuilding());
			return 0;
	}
	else if(bType=="barracks"){
		map[0][x][y].set_hasBuilding(true);
		map[0][x][y].set_building(new buildingBarrack());
		map[0][x][y].set_isSpawner(true);
		return 0;
	}
	else{
		//invalid type
		return 1;
	}
}

int buildBuilding(int x, int y, vector<vector<tile> >*map, string bType){   //creates a new building if posible
	if(x==0){
		if(map[0][x+1][y].get_hasBuilding()==true or map[0][x][y+1].get_hasBuilding() or map[0][x][y-1].get_hasBuilding()){
			int temp=createBuilding(x,y,map,bType);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	else if(x==10){
		if(map[0][x-1][y].get_hasBuilding() or map[0][x][y+1].get_hasBuilding() or map[0][x][y-1].get_hasBuilding()){
			int temp=createBuilding(x,y,map,bType);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	else if(y==0){
		if(map[0][x+1][y].get_hasBuilding()==true or map[0][x-1][y].get_hasBuilding() or map[0][x][y+1].get_hasBuilding()){
			int temp=createBuilding(x,y,map,bType);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	else if(y==10){
		if(map[0][x+1][y].get_hasBuilding()==true or map[0][x-1][y].get_hasBuilding() or map[0][x][y-1].get_hasBuilding()){
			int temp=createBuilding(x,y,map,bType);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	else{
		if(map[0][x+1][y].get_hasBuilding()==true or map[0][x-1][y].get_hasBuilding() or map[0][x][y+1].get_hasBuilding() or map[0][x][y-1].get_hasBuilding()){
			int temp=createBuilding(x,y,map,bType);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
}

int convertToASCII(string input_coords) {   //convers a character into int coord

	int number;

	string input = input_coords;
	number = int(input[0])-65;

	return number;

}

int convertNumToASCII(string input_coords) {   //convers a character into int coord

	int number;
	string input = input_coords;
	if(input.length()==3){
		number=((int(input[1])-'0')*10)+int(input[2])-'0';
	}
	else{
		number = int(input[1])-'0';
	}

	return number;

}

int spawnUnit(int x, int y, vector<vector<tile> >*map, string uType){
	if(map[0][x][y].get_hasUnit()==true){
		return 1;
		cout<<"This tile already has a unit in it"<<endl;
	}
	else if(map[0][x][y].get_isSpawner()==false){
		cout<<"This tile cannot spawn units"<<endl;
		return 2;
	}
	else{
		if(map[0][x][y].buildingGet_name()=="Barracks"){
			if(uType=="light" or uType=="infantry" or uType=="heavy" or uType=="rocket" or uType=="flamethrower"){
				map[0][x][y].building_spawnUnit(uType);
				return 0;
			}
			else{
				return 3;
			}
		}
		else if(map[0][x][y].buildingGet_name()=="Vehicle Bay"){
			if(uType=="destroyer" or uType=="cruiser" or uType=="shocklauncher"){
				map[0][x][y].building_spawnUnit(uType);
				return 0;
			}
			else{
				return 3;
			}
		}
		else{
			return 4;
		}
	}
}

void endTurn(vector<vector<tile> >*map){
	for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
			if(map[0][j][i].get_hasUnit()==true){
				if(map[0][j][i].unit_AI()==true){
					AIRec+=map[0][j][i].getTileIncome();
				}
				else{
					playerRec+=map[0][j][i].getTileIncome();
				}
			}
			else if(map[0][j][i].get_hasBuilding()==true){
				if(map[0][j][i].building_AI()==true){
					AIRec+=map[0][j][i].getTileIncome();
				}
				else{
					playerRec+=map[0][j][i].getTileIncome();
				}
			}
			else{

			}
      map[0][j][i].turnTick();
    }
  }
	consoleRenderFrame(width, height, *map);
	if(map[0][width/2][0].get_hasBuilding()==false){
		gameRunning=false;
		cout<<"Winner winner chicken dinner!"<<endl;
	}
	else if(map[0][width/2][height-1].get_hasBuilding()==false){
		gameRunning=false;
		cout<<"Epic fail: the AI kicked your ass!"<<endl;
	}
}

void commandLine(vector<vector<tile> >*map) {  //takes and interperates players input commands
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
			gameRunning=false;
			break;
		}
		else if(input == "attack") {

			string attacker, attacked;

			cout << "Which Unit would you like to attack with? ";
			cin >> attacker;

			cout << "What Unit would you like to attack? ";
			cin >> attacked;
			int x=convertToASCII(attacker);
			int y=convertNumToASCII(attacker);
			int x1=convertToASCII(attacked);
			int y1=convertNumToASCII(attacked);
			if(x<0 or x>10 or y<0 or y>10 or x1<0 or x1>10 or y1<0 or y1>10){
				cout<<"Invalid tile"<<endl;
			}
			else{
				int temp = attack(x, y, x1, y1, map);
				if(temp=1){
					cout<<"No unit selected"<<endl;
				}
				else if(temp=2){
					cout<<"No target selected"<<endl;
				}
				else if(temp=3){
					cout<<"Unit out of range"<<endl;
				}
				else if(temp=4){
					cout<<"This building is friendly"<<endl;
				}
				else if(temp=5){
					cout<<"This unit is friendly"<<endl;
				}
				else {
					consoleRenderFrame(width, height, *map);
				}
			}
		}
		else if(input == "move") {

			string unit_to_be_moved, new_pos;


			cout << "Which Unit would you like to move?";
			cin >> unit_to_be_moved;

			cout << "Where would you like to move it to?";
			cin >> new_pos;
			int x=convertToASCII(unit_to_be_moved);
			int y=convertNumToASCII(unit_to_be_moved);
			int x1=convertToASCII(new_pos);
			int y1=convertNumToASCII(new_pos);
			if(x<0 or x>10 or y<0 or y>10 or x1<0 or x1>10 or y1<0 or y1>10){
				cout<<"Invalid tile"<<endl;
			}
			else{
				int temp = moveUnit(x, y, x1, y1, map);
				if(temp==1){
					cout<<"There is already a unit here"<<endl;
				}
				else if(temp==2){
					cout<<"No unit selected"<<endl;
				}
				else if(temp==3){
					cout<<"Out of movement range"<<endl;
				}
				else {
					consoleRenderFrame(width, height, *map);
				}
			}
		}
		else if(input == "look") {

			string tile;

			cout << "Where would you like to look?";
			cin >> tile;
			int x=convertToASCII(tile);
			int y=convertNumToASCII(tile);
			if(x<0 or x>10 or y<0 or y>10){
				cout<<"Invalid tile"<<endl;
			}
			else{
				printTileInfo(x, y,map);
			}
		}
		else if(input == "build") {

			string tile;
			string bType;


			cout << "Where would you like to build?";
			cin >> tile;

			cout << "What would you like to build?";
			cin >> bType;
			int x=convertToASCII(tile);
			int y=convertNumToASCII(tile);
			if(x<0 or x>10 or y<0 or y>10){
				cout<<"Invalid tile"<<endl;
			}
			else{
				int temp = buildBuilding(x, y,map,bType);
				if(temp==1){
					cout<<"Invalid building type"<<endl;
				}
				else if(temp==2){
					cout<<"Unable to build here"<<endl;
				}
				else{
					consoleRenderFrame(width, height, *map);
				}
			}

		}
		else if(input == "spawn") {

			string tile;
			string uType;


			cout << "Which building would you like to spawn unit at?";
			cin >> tile;

			cout << "What unit you like to spawn?";
			cin >> uType;

			int x=convertToASCII(tile);
			int y=convertNumToASCII(tile);
			if(x<0 or x>10 or y<0 or y>10){
				cout<<"Invalid tile"<<endl;
			}
			else{
				spawnUnit(x, y,map,uType);
			}
		}
		else{

			std::cout << "That is not a valid command" << std::endl;
		}
	}
}

int convertIDRow(int ID){
	int temp=ID;
	temp=round(temp/11);
	return temp;
}

int convertIDColumn(int ID){
	return ID-(convertIDRow(ID)*11);
}

int convertToID(int x, int y){
	int id=(y*11)+x;
	return id;
}

int distID(int id, int id1){
	int x=convertIDColumn(id);
	int y=convertIDRow(id);
	int x1=convertIDColumn(id1);
	int y1=convertIDRow(id1);
	int dist=abs(x1-x)+abs(y1-y);
	return dist;
}

vector<int> findUnits(int AI,vector<vector<tile> >*map){
	int count=0;
	vector<int>units;
	for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
			if(map[0][i][j].get_hasUnit()==true and map[0][i][j].unit_AI()==AI){
				count+=1;
				units.resize(count);
				units[count-1]=map[0][i][j].get_id();
			}
		}
	}
	return units;
}

vector<task> findTasks(vector<vector<tile> >*map){
	vector<task>tasks;
	tasks.resize(121);
	for(int i=0;i<121;i++){
		int x=convertIDRow(i);
		int y=convertIDColumn(i);
		tasks[i].id=i;
		if(map[0][x][y].get_hasBuilding()==true and map[0][x][y].building_AI()==false){
			tasks[i].type=1;
		}
		else if(map[0][x][y].get_hasUnit()==true and map[0][x][y].unit_AI()==false){
			tasks[i].type=1;
		}
		else if(map[0][x][y].get_hasBuilding()==true and map[0][x][y].building_AI()==true){
			tasks[i].type=2;
		}
		else{
			tasks[i].type=3;
		}
		tasks[i].priority=map[0][x][y].get_priority();
	}
	return tasks;
}

void tacAI(vector<vector<tile> >*map){
	vector<int>listOfAIUnits=findUnits(true, map);
	vector<task>tasks=findTasks(map);
	vector<assignment>assignments;
	for(int i=0;i<listOfAIUnits.size();i++){
		for(int j=0;j<tasks.size();j++){
			int x=convertIDColumn(listOfAIUnits[i]);
			int y=convertIDRow(listOfAIUnits[i]);
			if(distID(listOfAIUnits[i], tasks[j].id)<=map[0][x][y].unitGet_movesLeft()){
				assignments.resize(assignments.size()+1);
				assignments[assignments.size()-1].id=tasks[j].id;
				assignments[assignments.size()-1].type=tasks[j].type;
				assignments[assignments.size()-1].score=tasks[j].priority;
				assignments[assignments.size()-1].id=listOfAIUnits[i];
			}
		}
	}
	listOfAIUnits.clear();
	tasks.clear();
}

int main(){
  vector<vector<tile> >map;  //sets up the map
  map.resize(width);
  for(int i=0;i<width;i++){
    map[i].resize(height);
  }
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
			int id=convertToID(j,i);
      map[j][i]=tile(id);
    }
  }
	map[width/2][0].set_building(new buildingBase(true));
	map[width/2][0].set_hasBuilding(true);
	map[width/2][height-1].set_building(new buildingBase());
	map[width/2][height-1].set_hasBuilding(true);
  consoleRenderFrame(width, height, map);  //renders initial screen
	tacAI(&map);
	while(gameRunning==true){
		commandLine(&map);   //runs console
		endTurn(&map);
		cout<<"Turn over"<<endl;
	}
  cout<<"Game over man, Game over!"<<endl;   //testing output to see that game has finished with no errors
  return 0;
}
