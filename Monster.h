#ifndef MONSTER_H
#define MONSTER_H
#include<fstream>
#include<sstream>
#include<string>
//#include<vector>
#include"Vector.h"
using namespace std;
struct detail
{
	int No;
	string name;
	string type;
	int hp;
	int atk;
	int def;
	int speed;
	int ability;
};
class Monster
{
public:
	Monster();
	detail getRandMonster(int);
	detail getNPCMonster(int);
	void loadMonster();
private:
	vector<detail> Monsterlist;
	vector<detail> random;
};
#endif
