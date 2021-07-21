#ifndef NPC_H
#define NPC_H
#include "Monster.h"
#include "AbilityData.h"
#include "rlutil.h"
#include<iostream>
#include<iomanip>
using namespace std;
using namespace rlutil;
class NPC
{
public:
	NPC(Monster& tomonsterdatabase);
	void MakeCombatList(int);
	void getMonster();
	void showAliveMonsters();
	void loadImage();
	void clearCombatlist();
	AbilityPtr* getCurrentMonster();
private:
	vector<AbilityPtr*> NpcCombatlist;
	detail NpcMonsterlist[13][3];
	Monster& monsterdatabase;
};


















#endif
