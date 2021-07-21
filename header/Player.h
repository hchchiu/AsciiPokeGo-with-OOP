#ifndef PLAYER_H
#define	PLAYER_H
#include "Monster.h"
#include "AbilityPtr.h"
class Player
{
public:
	Player(Monster& toMonsterdatavase);
	bool Interface(detail);
	bool dokanExist(int dokan);
	int getSize();
	int getSocre();
	void addScore();
	void addFinishDokan(int);
	void showBadge();
	void Catch(int terrain);
	void MakeCombatList();
	void Discard(int pos);
	void clearCombatlist();
	void showAliveMonsters();
	void bagShowMonsters();
	void loadImage();
	AbilityPtr* getCurrentMonster();
private:
	vector<detail> PlayerMonsterList;
	vector<AbilityPtr*> PlayerCombatList;
	Monster& monsterdatabase;
	vector<int> finishDokan;
	int score;
};
#endif // !PLAYER_H