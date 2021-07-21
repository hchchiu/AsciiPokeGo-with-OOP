#include "Monster.h"
#include "AbilityPtr.h"
#include<iostream>
//��l�� �I�sloadMonsterŪ���Ǫ��ɮ�
Monster::Monster()
{
	loadMonster();
}
//Ū���ɮ�
//�ñNstring���A�૬
//�NŪ�i�Ӫ���Ʃ�Jdata member
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
//�^���H�����Ǫ�
//��Player�I�s
//�ھڤ��P�a�Τ��P���v�P�_�åB�^�ǩ��~
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
//�^���H�����~
//��NPC�I�s
detail Monster::getNPCMonster(int pos)
{
	return Monsterlist[pos];
}