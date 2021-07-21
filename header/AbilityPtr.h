#ifndef ABILITYPTR_H
#define ABILITYPTR_H
#include "Monster.h"
#include "rlutil.h"
#include <string>
#include<iostream>
#include "Type.h"
using namespace std;
using namespace rlutil;
class AbilityPtr
{
public:
	AbilityPtr(detail toFightContain)
		:fightContain(toFightContain), MaxHP(toFightContain.hp), Poisontime(0), Pos(39)
	{
		first = true;
		isPoison = false;
		isDefense = false;
		isAttack = false;
		isSpeed = false;
		firstIn = true;
		launch = false;
		Defensetime = Attacktime = Speedtime = false;
	};
	int getMaxHP() { return MaxHP; }


	int getNo() { return fightContain.No; };

	string getname() { return fightContain.name; };

	string gettype() { return fightContain.type; };

	void sethp(int toHp) {
		if (toHp < 0)
			fightContain.hp = 0;
		else
			fightContain.hp = toHp;
	};
	int gethp() { return fightContain.hp; };

	void setdef(int toDef) { fightContain.def = toDef; };
	int getdef() { return fightContain.def; };

	void setatk(int toAtk) { fightContain.atk = toAtk; };
	int getatk() { return fightContain.atk; };

	void setspeed(int tospeed) { fightContain.speed = tospeed; };
	int getspeed() { return fightContain.speed; };

	int getability() { return fightContain.ability; }

	bool getfirst() { return first; };
	bool getfirstIn() { return firstIn; };
	// Check if some Pokemons died,it's ability still can affect

	bool getDefensetime() { return Defensetime; };
	void setDefensetime(bool check) { Defensetime = check; };
	bool getAttacktime() { return Attacktime; };
	void setAttacktime(bool check) { Attacktime = check; };
	bool getSpeedtime() { return Speedtime; };
	void setSpeedtime(bool check) { Speedtime = check; };
	//---------------------end------------------------------------

	void setfirstIn(bool check) { firstIn = check; }
	void setfirst(bool check) { first = check; };

	//----------check if some Pokemon be affected by some Pokemon ------

	void setisPoison(bool check) { isPoison = check; };
	void setisAttack(bool check) { isAttack = check; };
	void setisDefense(bool check) { isDefense = check; };
	void setPoison(bool check) { isPoison = check; };
	void setLaunch(bool check) { launch = check; };
	void setisSpeed(bool check) { isSpeed = check; };
	bool getLaunch() { return launch; };
	bool getPoison() { return isPoison; };
	bool getisSpeed() { return isSpeed; };
	bool getisPoison() { return isPoison; };
	bool getisDefense() { return isDefense; };
	bool getisAttack() { return isAttack; };
	//-----------------------end---------------------------

	//=====================virtual functions==========================

	virtual void attack(AbilityPtr& enemy, int pos) { enemy.gethp() - (getatk() - enemy.getdef()); };
	virtual void heal() { return; };
	virtual bool ProbabilityCheck() { return true; };
	virtual int getCounterAttack(int atk) { return 0; };
	virtual int Rockred() { return 0; };

	//================================================================

	//----------------Poison minus ---------------------------
	void Poison() {
		if (getisPoison()) {
			fightContain.hp -= 2 * Poisontime;
			cout << getname() << "中毒損失" << 2 * Poisontime << "點生命";
			if (fightContain.hp < 0)
			{
				setColor(RED);
				cout << fightContain.name << " 死掉了";
				setColor(WHITE);
			}
		}
	};
	void addPoinsonTime() { Poisontime++; };
	//-----------------------end------------------------------

	//-------------------Lower Speed ------------------------
	void LowerSpeedAffect(AbilityPtr & enemy, string & tomessage) {
		if (getability() == 9)
			if ((enemy.getfirstIn() == false && getfirst() == false && enemy.getability() != 4) || enemy.getSpeedtime() == true) {
				if (getLaunch() == false || enemy.getisSpeed() == false) {
					locate(28, 40);
					setLaunch(true);
					enemy.setisSpeed(true);
					enemy.setSpeedtime(false);
					enemy.setspeed(enemy.getspeed() - 2);
					//cout << enemy.getname() << "的速度被降低了2點";
					tomessage += enemy.getname();
					tomessage += "的速度被降低了 ";
				}
			}
	};
	//----------------- Lower Speed end-------------------

	//-------------------Lower ATK -------------------------
	void LowerAtkAffect(AbilityPtr & enemy, string & tomessage) {
		if (getability() == 12)
			if ((enemy.getfirstIn() == false && getfirst() == false && enemy.getability() != 4) || enemy.getAttacktime() == true) {
				if (getLaunch() == false || enemy.getisAttack() == false) {
					setLaunch(true);
					enemy.setisAttack(true);
					enemy.setatk(enemy.getatk() - 2);
					enemy.setAttacktime(false);
					//cout << enemy.getname() << " 的攻擊力被降低2點 ";
					tomessage += enemy.getname();
					tomessage += "的攻擊力被降低2點 ";
				}
			}
	};
	//----------------- Lower ATK end-------------------

	//-------------------Lower Deffence -------------------------
	void LowerDeffenceAffect(AbilityPtr & enemy, string & tomessage) {
		if (getability() == 11)
			if ((enemy.getfirstIn() == false && getfirst() == false && enemy.getability() != 4) || enemy.getDefensetime() == true) {
				if (getLaunch() == false || enemy.getisDefense() == false) {
					setLaunch(true);
					enemy.setisDefense(true);
					enemy.setdef(enemy.getdef() - 2);
					enemy.setDefensetime(false);
					//cout << enemy.getname() << " 的防禦力被降低了2點 ";
					tomessage += enemy.getname();
					tomessage += "的防禦力被降低了2點 ";
				}
			}
	};
	//----------------- Lower Deffence end-------------------
	Type Typenum;
private:
	detail fightContain;
	int MaxHP, Poisontime, Pos;
	bool Defensetime, Speedtime, Attacktime;
	bool first, firstIn, launch, isPoison, isDefense, isAttack, isSpeed;
};

#endif