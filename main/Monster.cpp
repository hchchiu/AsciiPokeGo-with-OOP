#include "Monster.h"
#include "AbilityPtr.h"
#include<iostream>
//初始化 呼叫loadMonster讀取怪物檔案
Monster::Monster()
{
	loadMonster();
}
//讀取檔案
//並將string型態轉型
//將讀進來的資料放入data member
void Monster::loadMonster()
{
	string check, tosplit;
	stringstream ss;
	stringstream sn;
	ifstream inFile("pokemons.csv");
	while (getline(inFile, check))
	{
		ss.str("");
		ss.clear();
		ss << check;
		int pos = 0;
		detail tosave;
		while (getline(ss, tosplit, ',')) {
			sn.str("");
			sn.clear();
			sn << tosplit;
			switch (pos++) {
			case 0:sn >> tosave.No; break;
			case 1:sn >> tosave.name; break;
			case 2:sn >> tosave.type; break;
			case 3:sn >> tosave.hp; break;
			case 4:sn >> tosave.atk; break;
			case 5:sn >> tosave.def; break;
			case 6:sn >> tosave.speed; break;
			case 7:sn >> tosave.ability; break;
			}
		}
		Monsterlist.push_back(tosave);
	}
}
//回傳隨機的怪物
//由Player呼叫
//根據不同地形不同機率判斷並且回傳怪獸
detail Monster::getRandMonster(int terrain)
{
	int randList[10] = { 1,1,1,1,1,1,0,0,0,0 };
	int pos = 0, Remaining = 0, check = 0, randPos = 0;
	if (terrain == 1) {
		int randListPos = rand() % 10;
		if (randListPos == 0)
			randPos = rand() % 3;
		else
			randPos = rand() % 31 + 3;
	}
	else if (terrain == 2) {
		int randListPos = rand() % 10;

		if (randListPos == 0)
			randPos = rand() % 3 + 6;
		else
		{
			do {
				randPos = rand() % 31 + 3;
			} while (randPos > 5 && randPos<9);
		}
	}
	else if (terrain == 0)
	{
		randPos = rand() % 34;
	}
	return Monsterlist[randPos];
}
//回傳隨機怪獸
//由NPC呼叫
detail Monster::getNPCMonster(int pos)
{
	return Monsterlist[pos];
}