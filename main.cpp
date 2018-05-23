#include "headers.h"
#include "unit.h"
#include "building.h"
#include "tile.h"
#include "buildingTypes.h"
#include "unitTypes.h"
#include <map>

int width=11;
int height=11;
int playerRec=100;
int playerIncome=0;
int AIRec=100;
int AIIncome=0;
bool gameRunning=true;
map<string,string> descriptions; // Creating Map with all of the descriptions for each building/unit

struct task{//defines a task
	int type;
	double priority;
	int id;
};

struct assignment{//desifens an assignment
	int type;
	double score;
	int id;
	int unitId;
};

int random(int min, int max){//outputs a random number between max and min
	int range=1+(max-min);
	return rand()%range+min;
}

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
			if(map[j][i].get_hasUnit()==true and map[j][i].get_hasBuilding()==true){  //renders icons and colours
				if(map[j][i].building_AI()==true){
					cout <<"\033[0;35m" <<setw(3)<< map[j][i].get_icon()<<temp<<"\033[0;37m";
				}
				else{
					cout <<"\033[0;34m"<< setw(3)<< map[j][i].get_icon()<<temp<<"\033[0;37m";
				}
			}
			else if(map[j][i].get_hasUnit()==true){
				if(map[j][i].unit_AI()==true){
					cout <<"\033[0;33m"<< setw(3)<< map[j][i].get_icon()<<temp<<"\033[0;37m";
				}
				else{
					cout<<"\033[0;32m" << setw(3)<< map[j][i].get_icon()<<temp<<"\033[0;37m";
				}
			}
			else if(map[j][i].get_hasBuilding()==true){
				if(map[j][i].building_AI()==true){
					cout<<"\033[0;33m" << setw(3)<< map[j][i].get_icon()<<temp<<"\033[0;37m";
				}
				else{
					cout<<"\033[0;32m" << setw(3)<< map[j][i].get_icon()<<temp<<"\033[0;37m";
				}
			}
			else{
				cout << setw(3)<< map[j][i].get_icon()<<temp<<"\033[0;37m";
			}
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

int moveUnit(int Sx, int Sy, int Fx, int Fy, vector<vector<tile> >*map, bool AI){ //moves unit from one place to another if posible
  int dist=abs(Fx-Sx)+abs(Fy-Sy);
  if(map[0][Fx][Fy].get_hasUnit()==true){
		//already has unit
    return 1;
  }
	else if(map[0][Sx][Sy].get_hasUnit()==false){
		//no unit to move
		return 2;
	}
	else if(map[0][Sx][Sy].unit_AI()!=AI){
		//wrong team
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

int attack(int Ax, int Ay, int Dx, int Dy, vector<vector<tile> >*map, bool AI){  //attacks unit with another if posible
  int dist=abs(Dx-Ax)+abs(Dy-Ay);
	if(map[0][Ax][Ay].get_hasUnit()==false){
		//no unit
    return 1;
	}
	if(map[0][Ax][Ay].unitGet_attacksLeft()==0){
		//no unit
    return 1;
	}
	else if(map[0][Ax][Ay].unit_AI()!=AI){
		//wrong team
		return 1;
	}
	else if(map[0][Dx][Dy].get_hasUnit()==false and map[0][Dx][Dy].get_hasBuilding()==false){
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

int createBuilding(int x, int y, vector<vector<tile> >*map, string bType, bool AI){//creates a building by calling function in tile
	if(bType=="mine"){  //creates mine
		if(AI==false){
			if(playerRec>=100){
				map[0][x][y].set_hasBuilding(true);
				map[0][x][y].set_building(new buildingMine(AI));
				playerRec-=100;
				return 0;
			}
			else{
				return 4;
			}
		}
		else{
			map[0][x][y].set_hasBuilding(true);
			map[0][x][y].set_building(new buildingMine(AI));
			return 0;
		}
	}
	else if(bType=="vehicleBay"){  //creates vbay
		if(AI==false){
			if(playerRec>=120){
				map[0][x][y].set_hasBuilding(true);
				map[0][x][y].set_building(new buildingVehicleBay(AI));
				map[0][x][y].set_isSpawner(true);
				playerRec-=120;
				return 0;
			}
			else{
				return 4;
			}
		}
		else{
			map[0][x][y].set_hasBuilding(true);
			map[0][x][y].set_building(new buildingVehicleBay(AI));
			map[0][x][y].set_isSpawner(true);
			return 0;
		}
	}
	else if(bType=="barracks"){  //creates barracks
		if(AI==false){
			if(playerRec>=100){
				map[0][x][y].set_hasBuilding(true);
				map[0][x][y].set_building(new buildingBarrack(AI));
				map[0][x][y].set_isSpawner(true);
				playerRec-=100;
				return 0;
			}
			else{
				return 4;
			}
		}
		else{
			map[0][x][y].set_hasBuilding(true);
			map[0][x][y].set_building(new buildingBarrack(AI));
			map[0][x][y].set_isSpawner(true);
			return 0;
		}
	}
	else{
		//invalid type
		return 1;
	}
	return 1;
}

int buildBuilding(int x, int y, vector<vector<tile> >*map, string bType, bool AI){   //creates a new building if posible
	if(x<0 or x>10 or y<0 or y>10){
		return 2;
	}
	if(map[0][x][y].get_hasBuilding()==false){
	if(x==0){
		if(map[0][x+1][y].get_hasBuilding()==true or map[0][x][y+1].get_hasBuilding()==true or map[0][x][y-1].get_hasBuilding()==true){
			int temp=createBuilding(x,y,map,bType,AI);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	else if(x==10){
		if(map[0][x-1][y].get_hasBuilding()==true or map[0][x][y+1].get_hasBuilding()==true or map[0][x][y-1].get_hasBuilding()==true){
			int temp=createBuilding(x,y,map,bType,AI);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	else if(y==0){
		if(map[0][x+1][y].get_hasBuilding()==true==true or map[0][x-1][y].get_hasBuilding()==true or map[0][x][y+1].get_hasBuilding()==true){
			int temp=createBuilding(x,y,map,bType,AI);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	else if(y==10){
		if(map[0][x+1][y].get_hasBuilding()==true or map[0][x-1][y].get_hasBuilding()==true or map[0][x][y-1].get_hasBuilding()==true){
			int temp=createBuilding(x,y,map,bType,AI);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	else{
		if(map[0][x+1][y].get_hasBuilding()==true or map[0][x-1][y].get_hasBuilding()==true or map[0][x][y+1].get_hasBuilding()==true or map[0][x][y-1].get_hasBuilding()==true){
			int temp=createBuilding(x,y,map,bType,AI);
			return temp;
		}
		else{
			//unable to build here
			return 2;
		}
	}
	}
	else{
		return 2;
	}
	return 2;
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

int spawnUnit(int x, int y, vector<vector<tile> >*map, string uType, bool AI){//spawns a unit
	if(map[0][x][y].get_hasUnit()==true){
		//already has unit
		return 1;
	}
	else if(map[0][x][y].get_isSpawner()==false){
		//cannot spawn
		return 2;
	}
	else{
		if(map[0][x][y].buildingGet_name()=="Barracks" and map[0][x][y].building_AI()==AI){ //checks spawner type
			if(uType=="light" or uType=="infantry" or uType=="heavy"){ //checks unit type
				if(AI==true){
					map[0][x][y].building_spawnUnit(uType,AI);
					return 0;
				}
				else{
					if(uType=="light"){//uses money
						if(playerRec>=35){
							map[0][x][y].building_spawnUnit(uType,AI);
							playerRec-=35;
							return 0;
						}
						else{
							return 4;
						}
					}
					else if(uType=="infantry"){
						if(playerRec>=70){
							map[0][x][y].building_spawnUnit(uType,AI);
							playerRec-=70;
							return 0;
						}
						else{
							return 4;
						}
					}
					else if(uType=="heavy"){
						if(playerRec>=115){
							map[0][x][y].building_spawnUnit(uType,AI);
							playerRec-=115;
							return 0;
						}
						else{
							return 4;
						}
					}
				}
				map[0][x][y].building_spawnUnit(uType,AI);
				return 0;
			}
			else{
				return 3;
			}
		}
		else if(map[0][x][y].buildingGet_name()=="Vehicle Bay" and map[0][x][y].building_AI()==AI){ //checks spawner type
			if(uType=="destroyer" or uType=="cruiser" or uType=="shocklauncher"){ //checks unit type
				if(AI==true){
					map[0][x][y].building_spawnUnit(uType,AI);
					return 0;
				}
				else{
					if(uType=="destroyer"){ //uses money
						if(playerRec>=120){
							map[0][x][y].building_spawnUnit(uType,AI);
							playerRec-=120;
							return 0;
						}
						else{
							return 4;
						}
					}
					else if(uType=="cruiser"){
						if(playerRec>=100){
							map[0][x][y].building_spawnUnit(uType,AI);
							playerRec-=100;
							return 0;
						}
						else{
							return 4;
						}
					}
					else if(uType=="shocklauncher"){
						if(playerRec>=80){
							map[0][x][y].building_spawnUnit(uType,AI);
							playerRec-=80;
							return 0;
						}
						else{
							return 4;
						}
					}
				}
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

void helpFunction() { // outputs help
	cout << "Type \"look\" to examine what is on a tile" <<endl;
	cout << "Type \"move\" to move a unit. How far you can move a unit depends on how many moves it has left" <<endl;
	cout << "Type\"attack\" to attack a unit. You can only attack units that are adjacent to you" << endl;
	cout << "Type \"build\" to build a building. You can only build on tiles that are adjacent to a building that you own." << endl;
	cout << "Type \"spawn\" to spawn a unit. You can only spawn infantry on a barracks, and vehicles on a vehicle bay." << endl;
}

void description(string description) {//outputs description
	if(description=="list"){
		cout<<"light, infantry, heavy, base, mine, barracks, vehicleBay, cruiser, destroyer, shocklauncher"<<endl;
	}
	else{
		if(description=="light"){
			cout<<"An infantry unit that is quick on its feet. Prepere yourself, ZERG RUSH!"<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 50"<<endl;
			cout<<"AC = 1"<<endl;
			cout<<"Cost = 40"<<endl;
			cout<<"icon = L"<<endl;
			cout<<"Speed = 5"<<endl;
			cout<<"damage = 10"<<endl;
			cout<<"spawn command: \"light\""<<endl;
		}
		else if(description=="infantry"){
			cout<<"The standard infantry unit. Not the lightest or the most powerful but always reliable."<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 100"<<endl;
			cout<<"AC = 4"<<endl;
			cout<<"Cost = 70"<<endl;
			cout<<"icon = I"<<endl;
			cout<<"Speed = 3"<<endl;
			cout<<"damage = 20"<<endl;
			cout<<"spawn command: \"infantry\""<<endl;
		}
		else if(description=="heavy"){
			cout<<"An infantry unit that deals a lot of damage, but is slow. Heavy infantry are towering hulks of men hailing from the USSR!"<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 200"<<endl;
			cout<<"AC = 6"<<endl;
			cout<<"Cost = 115"<<endl;
			cout<<"icon = H"<<endl;
			cout<<"Speed = 1"<<endl;
			cout<<"damage = 50"<<endl;
			cout<<"spawn command: \"heavy\""<<endl;
		}
		else if(description=="konamicode"){
			cout<<"Present day... Present time... HAHAHAHAHAHAHA."<<endl;
		}
		else if(description=="base"){
			cout<<"Your main base. Destroy this, and you lose the game so just don't. Please? (I mean it, just don't even think about it!)"<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 400"<<endl;
			cout<<"AC = 8"<<endl;
			cout<<"icon = B"<<endl;
			cout<<"Income = 100"<<endl;
		}
		else if(description=="mine"){
			cout<<"Diggy diggy hole. This building is full of busy dwarves that are getting you recources. What more do you need to know?"<<endl;
			cout<<"Just remember to bring some jaffa cakes as a peace offering..."<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 0"<<endl;
			cout<<"AC = 0"<<endl;
			cout<<"Cost = 100"<<endl;
			cout<<"icon = @"<<endl;
			cout<<"Income = 150"<<endl;
			cout<<"build command: \"mine\""<<endl;
		}
		if(description=="barracks"){
			cout<<"Allows for the spawning of infantry units. NO! Don't ask where they come from, you don't want to know..."<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 100"<<endl;
			cout<<"AC = 2"<<endl;
			cout<<"Cost = 100"<<endl;
			cout<<"icon = #"<<endl;
			cout<<"spawn command: \"barracks\""<<endl;
		}
		else if(description=="vehicleBay"){
			cout<<"Allows for the spawning of vehicles. Its a shed, with some vehicles, you get the idea..."<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 120"<<endl;
			cout<<"AC = 4"<<endl;
			cout<<"Cost = 150"<<endl;
			cout<<"icon = V"<<endl;
			cout<<"spawn command: \"vehicleBay\""<<endl;
		}
		else if(description=="cruiser"){
			cout<<"A tough strudy craft woth a few guns. The Yamato is loaded and so am I.. wait, I have an announcement...! I am drunk!"<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 250"<<endl;
			cout<<"AC = 6"<<endl;
			cout<<"Cost = 100"<<endl;
			cout<<"icon = C"<<endl;
			cout<<"Speed = 2"<<endl;
			cout<<"damage = 20"<<endl;
			cout<<"spawn command: \"cruiser\""<<endl;
		}
		else if(description=="destroyer"){
			cout<<"A very powerful vehicle. Show me your foes. And I shall destroy them! Burn them to ash! And then, I'll destroy the ash. *evil laugh*"<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 50"<<endl;
			cout<<"AC = 2"<<endl;
			cout<<"Cost = 120"<<endl;
			cout<<"icon = D"<<endl;
			cout<<"Speed = 3"<<endl;
			cout<<"damage = 100"<<endl;
			cout<<"spawn command: \"destroyer\""<<endl;
		}
		else if(description=="shocklauncher"){
			cout<<"A vehicle that can deliver a powerful shock (it totally isn't an electric eel loaded into a cannon, why would you think this, what kind of mosters do you think we are?)."<<endl;
			cout<<"Stats:"<<endl;
			cout<<"Health = 120"<<endl;
			cout<<"AC = 3"<<endl;
			cout<<"Cost = 80"<<endl;
			cout<<"icon = S"<<endl;
			cout<<"Speed = 3"<<endl;
			cout<<"damage = 35"<<endl;
			cout<<"spawn command: \"shocklauncher\""<<endl;
		}
		else{
			cout<<"invalid type"<<endl;
		}
	}
}

void endTurn(vector<vector<tile> >*map){//resets everything and calculates income
	playerIncome=0;
	AIIncome=0;
	for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
			if(map[0][j][i].get_hasUnit()==true){
				if(map[0][j][i].unit_AI()==true){
					AIRec+=map[0][j][i].getTileIncome();
					AIIncome+=map[0][j][i].getTileIncome();
				}
				else{
					playerRec+=map[0][j][i].getTileIncome();
					playerIncome+=map[0][j][i].getTileIncome();
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
	if(map[0][width/2][0].get_hasBuilding()==false or AIRec<0){  //checks endgame
		gameRunning=false;
		cout<<"Winner winner chicken dinner!"<<endl;
	}
	else if(map[0][width/2][height-1].get_hasBuilding()==false or playerRec<0){
		gameRunning=false;
		cout<<"Epic fail: the AI kicked your ass!"<<endl;
	}
}

void commandLine(vector<vector<tile> >*map) {  //takes and interperates players input commands
	string input;
	while(input != "end") {
		cout << "Enter Command: (type end to quit or endturn to end your turn) ";
		cin >> input;

		if(input == "endTurn" or input == "endturn" ) {
			//cout << "You have ended the turn" << std::endl;
			//cin.ignore();
			break;
		}
		else if(input == "end") {
			cout << "You have ended the game" << endl;
			cin.ignore();
			gameRunning=false;
			break;
		}
		else if(input == "help") {
			helpFunction();
		}
		else if(input == "about") {
			string to_be_described;
			cout << "What would you like to know about?";
			cin >> to_be_described;
			description(to_be_described);
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
				int temp = attack(x, y, x1, y1, map,false);
				if(temp==1){
					cout<<"No unit selected"<<endl;
				}
				else if(temp==2){
					cout<<"No target selected"<<endl;
				}
				else if(temp==3){
					cout<<"Unit out of range"<<endl;
				}
				else if(temp==4){
					cout<<"This building is friendly"<<endl;
				}
				else if(temp==5){
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
				int temp = moveUnit(x, y, x1, y1, map, false);
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
				int temp = buildBuilding(x, y,map,bType,false);
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
				int temp = spawnUnit(x,y,map,uType,false);
				if(temp == 1) {
					cout<<"This tile already has a unit in it"<<endl;
				}
				else if(temp == 2) {
					cout<<"This tile cannot spawn units"<<endl;
				}
				else if(temp == 3) {
					cout << "Invalid Unit Type" <<endl;
				}
				else if(temp == 4) {
					cout << "Unable to spawn" <<endl;
				}
				else {

				}
			}
		}
		else if(input == "help") {
			helpFunction();
		}
		else if(input == "about") {

			string name;

			cout << "What would you like to know about? (type list for list of available objects)";
			cin >> name;
			description(name);
		}
		else if(input=="clear"){
		cout<<"\033[2J\033[1;1H";
		}
		else{

			cout << "That is not a valid command, type \"help\" for help" << endl;
		}
	}
}

int convertIDRow(int ID){//convertd ID to x
	int temp=ID;
	temp=round(temp/11);
	return temp;
}

int convertIDColumn(int ID){//convertd ID to y
	return ID-(convertIDRow(ID)*11);
}

int convertToID(int x, int y){//convertd x,y to ID
	int id=(y*11)+x;
	return id;
}

int distID(int id, int id1){//converts two ids to dist
	int x=convertIDColumn(id);
	int y=convertIDRow(id);
	int x1=convertIDColumn(id1);
	int y1=convertIDRow(id1);
	int dist=abs(x1-x)+abs(y1-y);
	return dist;
}

vector<int> findUnits(int AI,vector<vector<tile> >*map){//finds all ai units
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

vector<task> findTasks(vector<vector<tile> >*map){//finds tasks for ai
	vector<task>tasks;
	tasks.resize(121);
	for(int i=0;i<121;i++){//chacks each tile
		int x=convertIDColumn(i);
		int y=convertIDRow(i);
		tasks[i].id=i;
		if(map[0][x][y].get_hasBuilding()==true and map[0][x][y].building_AI()==false){//creates task based on whats on tile
			tasks[i].type=1;
			tasks[i].priority=map[0][x][y].get_priority();
		}
		else if(map[0][x][y].get_hasBuilding()==true and map[0][x][y].building_AI()==true){
			tasks[i].type=3;
			if(map[0][x][y].buildingGet_name()=="Barracks" or map[0][x][y].buildingGet_name()=="Vehicle Bay"){
				tasks[i].priority=-(map[0][x][y].get_priority()/4);
			}
			else{
				tasks[i].priority=map[0][x][y].get_priority();
			}
		}
		else if(map[0][x][y].get_hasUnit()==true and map[0][x][y].unit_AI()==false){
			tasks[i].type=2;
			tasks[i].priority=map[0][x][y].get_priority();
		}
		else{
			tasks[i].type=4;
			tasks[i].priority=map[0][x][y].get_priority();
		}
	}
	return tasks;
}

vector<assignment> sorter(vector<assignment>toSort) {//sorts assignemnts by score
	int n = toSort.size();
	for (int i = 0; i < (n-1); i++) {
		for (int j = 0; j < (n-i-1); j++) {
			if (toSort[j].score < toSort[j + 1].score) {
				assignment temp = toSort[j];
				toSort[j] = toSort[j + 1];
				toSort[j + 1] = temp;
			}
		}
	}
	return toSort;
}

bool doTask(assignment assign, vector<vector<tile> >*map, vector<task>tasks){//does the assignments allocated to each task
	int x=convertIDColumn(assign.id);
	int y=convertIDRow(assign.id);
	int Ux=convertIDColumn(assign.unitId);
	int Uy=convertIDRow(assign.unitId);
	if(assign.type==1){//if is attack move to and attack //works out best place to move
		if(distID(assign.id,assign.unitId)<=1){
			cout<<attack(Ux,Uy,x,y,map,true)<<endl;
			return true;
		}
		else{
			int dist1;
			int dist2;
			int dist3;
			int dist4;
			if(x+1>10){
				dist1=tasks[convertToID(x+1,y)].priority;
			}
			else{
				dist1=-1000;
			}
			if(x-1<0){
				dist2=tasks[convertToID(x-1,y)].priority;
			}
			if(y+1>10){
				dist3=tasks[convertToID(x,y+1)].priority;
			}
			else{
				dist1=-1000;
			}
			if(y-1<0){
				dist4=tasks[convertToID(x,y-1)].priority;
			}
			else{
				dist1=-1000;
			}
			if(dist1>=dist2 and dist1>=dist3 and dist1>=dist4){
				if(map[0][x+1][y].get_hasUnit()==true or map[0][x+1][y].get_hasUnit()==true){
					return false;
				}
				else{
					moveUnit(Ux,Uy,x+1,y,map,true);
					cout<<"atk"<<attack(x+1,y,x,y,map,true)<<endl;
					return true;
				}
			}
			else if(dist2>=dist3 and dist2>=dist4 and dist2>=dist1){
				if(map[0][x-1][y].get_hasUnit()==true or map[0][x-1][y].get_hasBuilding()==true){
					return false;
				}
				else{
					moveUnit(Ux,Uy,x-1,y,map,true);
					return true;
				}
			}
			else if(dist4>=dist1 and dist4>=dist2 and dist4>=dist4){
				if(map[0][x][y-1].get_hasUnit()==true or map[0][x][y-1].get_hasBuilding()==true){
					return false;
				}
				else{
					int temp = moveUnit(Ux,Uy,x,y-1,map,true);
					return true;
				}
			}
			else if(dist3>=dist1 and dist3>=dist4 and dist3>=dist2){
				if(map[0][x][y+1].get_hasUnit()==true or map[0][x][y+1].get_hasBuilding()==true){
					return false;
				}
				else{
				int temp = moveUnit(Ux,Uy,x,y+1,map,true);
				return true;
			}
			}
			else{
				return false;
			}
		}
	}
	else if(assign.type==2){//if is attack move to and attack //works out best place to move
		if(distID(assign.id,assign.unitId)<=1){
			attack(Ux,Uy,x,y,map,true);
			return true;
		}
		else{
			int dist1;
			int dist2;
			int dist3;
			int dist4;
			if(x+1>10){
				dist1=tasks[convertToID(x+1,y)].priority;
			}
			else{
				dist1=-1000;
			}
			if(x-1<0){
				dist2=tasks[convertToID(x-1,y)].priority;
			}
			if(y+1>10){
				dist3=tasks[convertToID(x,y+1)].priority;
			}
			else{
				dist1=-1000;
			}
			if(y-1<0){
				dist4=tasks[convertToID(x,y-1)].priority;
			}
			else{
				dist1=-1000;
			}
			if(dist1>=dist2 and dist1>=dist3 and dist1>=dist4){
				if(map[0][x+1][y].get_hasUnit()==true or map[0][x+1][y].get_hasUnit()==true){
					return false;
				}
				else{
					moveUnit(Ux,Uy,x+1,y,map,true);
					attack(x+1,y,x,y,map,true);
					return true;
				}
			}
			else if(dist2>=dist3 and dist2>=dist4 and dist2>=dist1){
				if(map[0][x-1][y].get_hasUnit()==true or map[0][x-1][y].get_hasBuilding()==true){
					return false;
				}
				else{
					moveUnit(Ux,Uy,x-1,y,map,true);
					attack(x-1,y,x,y,map,true);
					return true;
				}
			}
			else if(dist4>=dist1 and dist4>=dist2 and dist4>=dist4){
				if(map[0][x][y-1].get_hasUnit()==true or map[0][x][y-1].get_hasBuilding()==true){
					return false;
				}
				else{
					int temp = moveUnit(Ux,Uy,x,y-1,map,true);
					attack(x,y-1,x,y,map,true);
					return true;
				}
			}
			else if(dist3>=dist1 and dist3>=dist4 and dist3>=dist2){
				if(map[0][x][y+1].get_hasUnit()==true or map[0][x][y+1].get_hasBuilding()==true){
					return false;
				}
				else{
				int temp = moveUnit(Ux,Uy,x,y+1,map,true);
				attack(x,y+1,x,y,map,true);
				return true;
			}
			}
			else{
				return false;
			}
		}
	}
	else if(assign.type==3){//moves unit to defend
		if(map[0][x][y].get_hasUnit()==true){
			return false;
		}
		else{
			moveUnit(Ux,Uy,x,y,map,true);
			return true;
		}
	}
	else if(assign.type==4 and assign.score>0){  //moves unit to tile
		if(map[0][x][y].get_hasUnit()==true){
			return false;
		}
		else{
			moveUnit(Ux,Uy,x,y,map,true);
			return true;
		}
	}
	else{
		return false;
	}
}

void tacAI(vector<vector<tile> >*map){//moves all AI units and decides the bast course of action
	vector<int>listOfAIUnits=findUnits(true, map);//gets units
	vector<task>tasks=findTasks(map);//gets tasks
	vector<assignment>assignments;  //sets assignments
	for(int i=0;i<listOfAIUnits.size();i++){
		for(int j=0;j<tasks.size();j++){
			int x=convertIDColumn(listOfAIUnits[i]);
			int y=convertIDRow(listOfAIUnits[i]);
			if(distID(listOfAIUnits[i], tasks[j].id)<=map[0][x][y].unitGet_movesLeft()){
				assignments.resize(assignments.size()+1);
				assignments[assignments.size()-1].id=tasks[j].id;
				assignments[assignments.size()-1].type=tasks[j].type;
				double k;
				if(tasks[j].type==1){
					int dmgDef=map[0][convertIDColumn(listOfAIUnits[i])][convertIDRow(listOfAIUnits[i])].unitGet_dmg()-map[0][convertIDColumn(tasks[j].id)][convertIDRow(tasks[j].id)].buildingGet_AC();      //damage delt to defender
					int dmgAtk=round((0.75*map[0][convertIDColumn(tasks[j].id)][convertIDRow(tasks[j].id)].unitGet_dmg())-map[0][convertIDColumn(listOfAIUnits[i])][convertIDRow(listOfAIUnits[i])].unitGet_AC());
					k=(dmgAtk)/(dmgDef);
				}
				else if(tasks[j].type==2){
					int dmgDef=map[0][convertIDColumn(listOfAIUnits[i])][convertIDRow(listOfAIUnits[i])].unitGet_dmg()-map[0][convertIDColumn(tasks[j].id)][convertIDRow(tasks[j].id)].unitGet_AC();      //damage delt to defender
					int dmgAtk=round((0.75*map[0][convertIDColumn(tasks[j].id)][convertIDRow(tasks[j].id)].unitGet_dmg())-map[0][convertIDColumn(listOfAIUnits[i])][convertIDRow(listOfAIUnits[i])].unitGet_AC());
					k=(dmgAtk)/(dmgDef);
				}
				else{
					k=0;
				}
				if(tasks[j].type==4){
					int x=convertIDColumn(tasks[j].id);
					int y=convertIDRow(tasks[j].id);
					double sum=0;
					if(x>0){
						sum+=tasks[convertToID(x-1,y)].priority;
					}
					if(x<10){
						sum+=tasks[convertToID(x+1,y)].priority;
					}
					if(y>0){
						sum+=tasks[convertToID(x,y-1)].priority;
					}
					if(y<10){
						sum+=tasks[convertToID(x,y+1)].priority;
					}
					tasks[j].priority=sum/5;
				}
				if(distID(tasks[j].id,listOfAIUnits[i])>0){
					assignments[assignments.size()-1].score=((tasks[j].priority)/distID(tasks[j].id,listOfAIUnits[i]))+(3.5*y);
				}
				else{
					assignments[assignments.size()-1].score=((tasks[j].priority)-(5*k))+(3.5*y);
				}
				assignments[assignments.size()-1].unitId=listOfAIUnits[i];
			}
		}
	}
	assignments=sorter(assignments);//sorts assignments
	while(assignments.size()>0){//does assignments
		if(doTask(assignments[0],map,tasks)==true){
			int unitId=assignments[0].unitId;
			assignments.erase(assignments.begin()+0);
			for(int i=1;i<assignments.size();i++){
				if(assignments[i].unitId==unitId){
					assignments.erase(assignments.begin()+i);
				}
			}
		}
		else{
			assignments.erase(assignments.begin()+0);
		}
	}
	listOfAIUnits.clear();//clears from memory
	tasks.clear();
	assignments.clear();
}

void econAI(double bI, double cI, double bU, double bS, double bR, double cR, vector<vector<tile> >*map){
	double pI=0;//sets AI peramiters and calculates the ai actions
	double I=0;
	double pU=0;
	double U=0;
	double pS=0;
	double S=0;
	double pR=playerRec;
	double R=AIRec;
	vector<int>spawnerId;
	spawnerId.resize(0);
	int wX[2]={5,5};
	int wY[2]={0,0};
	for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
			if(map[0][j][i].get_hasUnit()==true){
				if(map[0][j][i].unit_AI()==true){
					I+=map[0][j][i].getTileIncome();
					U+=1;
				}
				else if(map[0][j][i].unit_AI()==false){
					pI+=map[0][j][i].getTileIncome();
					pU+=1;
				}
			}
			if(map[0][j][i].get_hasBuilding()==true and map[0][j][i].get_isSpawner()==true){
				if(map[0][j][i].building_AI()==true){
					spawnerId.resize(spawnerId.size()+1);
					spawnerId[spawnerId.size()-1]=convertToID(j,i);
					I+=map[0][j][i].getTileIncome();
					S+=1;
					if(j<wX[0]){
						wX[0]=j;
					}
					if(j>wX[1]){
						wX[1]=j;
					}
					if(i>wY[1]){
						wY[1]=i;
					}
				}
				else{
					pI+=map[0][j][i].getTileIncome();
					pS+=1;
				}
			}
			else if(map[0][j][i].get_hasBuilding()==true){
				if(map[0][j][i].building_AI()==true){
					I+=map[0][j][i].getTileIncome();

				}
				else{
					pI+=map[0][j][i].getTileIncome();
				}
			}
		}
	}
	wX[0]=max(wX[0]-1,0);
	wX[1]=min(wX[1]+1,10);
	wY[1]=min(wY[1]+1,10);
	//cout<<I<<":"<<pI<<":"<<U<<":"<<pU<<":"<<S<<":"<<pS<<":"<<pR<<":"<<R<<endl;
	double tI=bI+cI*pI;
	double rI=max(1.00-round(10*(I/tI))/10.00,0.00);
	double tU=bU+ceil(pU/2)+ceil(U/2);
	double rU=max(1.00-round(10*(U/tU))/10.00,0.00);
	double tS=bS+ceil(pS/2)+ceil(S/2);
	double rS=max(1.00-round(10*(S/tS))/10.00,0.00);
	double tR=bR+cR*pR;
	double rR=min(round(10*(R/tR))/10.00,1.00);
	double RUsable=floor(min(R*rR, R));
	double temp=max(rI+rU+rS,0.10);
	rI=max(floor(10*(rI/temp))/10,0.10);
	rU=max(floor(10*(rU/temp))/10,0.10);
	rS=max(floor(10*(rS/temp))/10,0.10);
	double RI=min(floor(RUsable*rI),R/(rR*3));
	double RU=min(floor(RUsable*rU),R/(rR*3));
	double RS=min(floor(RUsable*rS),R/(rR*3));
	//cout<<rI<<":"<<rU<<":"<<rS<<endl;
	//cout<<RUsable<<":"<<RI<<":"<<RU<<":"<<RS<<endl;
	//build/spawn buildings/units:
	int t=0;
	while(RI>=100 and t<100 and AIRec>=100){//creates mines
		int x=random(wX[0],wX[1]);
		int y=random(wY[0],wY[1]);
		while(map[0][x][y].get_hasBuilding()==true and t<100){
			x=random(wX[0],wX[1]);
			y=random(wY[0],wY[1]);
			t+=1;
		}
		while(buildBuilding(x,y,map,"mine",true)!=0 and t<100){
			x=random(wX[0],wX[1]);
			y=random(wY[0],wY[1]);
			while(map[0][x][y].get_hasBuilding()==true and t<100){
				x=random(wX[0],wX[1]);
				y=random(wY[0],wY[1]);
				t+=1;
			}
			t+=1;
		}
		if(t<100){
			RI-=100;
			AIRec-=100;
		}
		t+=1;
	}
	t=0;
	while(RU>=100 and t<100 and spawnerId.size()>0){//spawns units
		int spawner=random(0,spawnerId.size()-1);
		int id=spawnerId[spawner];
		int x=convertIDColumn(id);
		int y=convertIDRow(id);
		if(map[0][x][y].buildingGet_name()=="Barracks"){
			int type=random(1,3);
			if(type==1 and AIRec>=70){
				if(spawnUnit(x,y,map,"infantry",true)==0){
					RU-=70;
					AIRec-=70;
				}
			}
			else if(type==2 and AIRec>=115){
				if(spawnUnit(x,y,map,"heavy",true)==0){
					RU-=115;
					AIRec-=115;
				}
			}
			else if(type==3 and AIRec>=35){
				if(spawnUnit(x,y,map,"light",true)==0){
					RU-=35;
					AIRec-=35;
				}
			}
		}
		else if(map[0][x][y].buildingGet_name()=="Vehicle Bay"){
			int type=random(1,3);
			if(type==1 and AIRec>=120){
				if(spawnUnit(x,y,map,"destroyer",true)==0){
					RU-=120;
					AIRec-=120;
				}
			}
			else if(type==2 and AIRec>=100){
				if(spawnUnit(x,y,map,"cruiser",true)==0){
					RU-=100;
					AIRec-=100;
				}
			}
			else if(type==3 and AIRec>=80){
				if(spawnUnit(x,y,map,"shocklauncher",true)==0){
					RU-=80;
					AIRec-=80;
				}
			}
		}
		spawnerId.erase(spawnerId.begin()+spawner);
		t+=1;
	}
	t=0;
	while(RS>=100 and t<100 and AIRec>=100){//spawns spawners
		int x=random(wX[0],wX[1]);
		int y=random(wY[0],wY[1]);
		while(map[0][x][y].get_hasBuilding()==true and t<100){
			x=random(wX[0],wX[1]);
			y=random(wY[0],wY[1]);
			t+=1;
		}
		int type=random(0,1);
		if(type==0 and RS>=120 and AIRec>=120){
			while(buildBuilding(x,y,map,"vehicleBay",true)!=0 and t<100){
				x=random(wX[0],wX[1]);
				y=random(wY[0],wY[1]);
				while(map[0][x][y].get_hasBuilding()==true and t<100){
					x=random(wX[0],wX[1]);
					y=random(wY[0],wY[1]);
					t+=1;
				}
				t+=1;
			}
			if(t<100){
				RI-=120;
				AIRec-=120;
			}
		}
		else{
			while(buildBuilding(x,y,map,"barracks",true)!=0 and t<100){
				x=random(wX[0],wX[1]);
				y=random(wY[0],wY[1]);
				while(map[0][x][y].get_hasBuilding()==true and t<100){
					x=random(wX[0],wX[1]);
					y=random(wY[0],wY[1]);
					t+=1;
				}
				t+=1;
			}
			if(t<100){
				RI-=100;
				AIRec-=100;
			}
		}
		t+=1;
	}
}

int main(){
	srand(time(NULL));  //set random seed
	cout<<"\033[0;40m";
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
	int bI=random(100,500);  //set up AI
	double cI=random(0.00,200.00)/100.00;
	int bU=random(1,5);
	int bS=random(1,3);
	int bR=random(100,500);
	double cR=random(0.00,100.00)/100.00;
	map[width/2][0].set_building(new buildingBase(true));  //create bases
	map[width/2][0].set_hasBuilding(true);
	map[width/2][height-1].set_building(new buildingBase());
	map[width/2][height-1].set_hasBuilding(true);
  consoleRenderFrame(width, height, map);  //renders initial screen
	while(gameRunning==true){
		commandLine(&map);   //runs console
		econAI(bI, cI, bU, bS, bR, cR, &map);   //run AI
		tacAI(&map);
		endTurn(&map);  //endTurn
		if(gameRunning==true){
			cout<<"Turn over"<<endl;
		}
	}
  cout<<"Game over man, Game over!"<<endl;
  return 0;
}
