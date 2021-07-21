#ifndef MAP_H
#define MAP_H
#include<fstream>
#include<string>
#include "rlutil.h"
#include "Player.h"
#include "NPC.h"
//#include"Monster.h"
using namespace std;
using namespace rlutil;
class Map
{
public:
	Map(Player& toplayerdata, NPC& tonpcdata);
	void loadMap();
	void draw();
	void LowerCheck(string&);
	void showState();
	void fight(char building);
	void move(int&, int&, int, int);
	void CatchCheck(char);
	class WrongPlayerPokemonSize
	{
	public:
		WrongPlayerPokemonSize() {};
		const char* what() { return "你的Pokemon數量不夠!!!"; };
	};	
	class WrongDokan
	{
	public:
		WrongDokan() {};
		const char* what() { return "你已經挑戰過這間道館"; };
	};
private:
	int mapLength;
	int mapWidth[31];
	char lvl[32][150];
	Player& playerdata;
	NPC& npcdata;
};

#endif // !"MAP.H"

