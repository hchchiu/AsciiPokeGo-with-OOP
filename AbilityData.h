#ifndef ABILITYDATA_H
#define ABILITYDATA_H
#include "Monster.h"
#include "AbilityPtr.h"
#include "rlutil.h"
#include<iostream>
using namespace std;
using namespace rlutil;
//#include "Player.h"
//一般怪物
class Normal :public AbilityPtr
{
public:
	Normal(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//每回合回復HP3
class Heal :public AbilityPtr
{
public:
	Heal(detail toPush) :AbilityPtr(toPush) {};
	void heal()
	{
		if (gethp() + 3 < getMaxHP()) {
			sethp(gethp() + 3);
			cout << getname() << "恢復了3點生命";
		}
		else {
			cout << getname() << "恢復了" << getMaxHP() - gethp() << "點生命";
			sethp(getMaxHP());
		}
	}
	void attack(AbilityPtr & enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//隨機附加不受防禦影響的傷害1~3
class Burning :public AbilityPtr
{
public:
	Burning(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int spAtk = rand() % 3 + 1;
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype()) + spAtk;
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal - spAtk << "點傷害 " << " 燃燒能力造成" << spAtk << "點傷害";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//反擊1/5所受傷害
class CounterAttack :public AbilityPtr
{
public:
	CounterAttack(detail toPush) :AbilityPtr(toPush) {};
	int getCounterAttack(int atk) {
		if (atk > 0)
			return atk * 0.2;
		else
			return 0;
	}
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//免疫降低能力值的特殊能力
class Immunology :public AbilityPtr
{
public:
	Immunology(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);
			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
// 每次攻擊吸收2~3HP
class LeechLife :public AbilityPtr
{
public:
	LeechLife(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(20, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout <<" "<< enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(20, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
		if (enemy.gethp() > 0) {
			int absorbHP = 0;
			absorbHP = rand() % 2 + 2;
			if ((gethp() + absorbHP) < getMaxHP())
				sethp(gethp() + absorbHP);
			else
				sethp(getMaxHP());

			cout << getname() << " 吸收了" << absorbHP << "點的生命";

			enemy.sethp(enemy.gethp() - absorbHP);
		}
		else {
			locate(23, pos + 2);
			setColor(RED);
			cout << enemy.getname() << "死掉了";
			setColor(WHITE);
		}
	}
};
//1/5機率迴避攻擊
class Avoid :public AbilityPtr
{
public:
	Avoid(detail toPush) :AbilityPtr(toPush) {};
	bool ProbabilityCheck() {
		int ProbaNum = rand() % 5;
		if (ProbaNum == 1)
			return false;
		return true;
	};
	void attack(AbilityPtr & enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);
			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				if (gethp() <= 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else if (gethp() <= 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//1/5機率兩次攻擊
class DoubleAttack :public AbilityPtr
{
public:
	DoubleAttack(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		int time = 1;
		if (enemy.ProbabilityCheck()) {
			locate(23, pos);
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			int doubleCheck = rand() % 5;
			if (doubleCheck == 1)
				time++;
			for (int i = 0; i < time; ++i)
				enemy.sethp(enemy.gethp() - attackVal);

			if (time == 1)
				cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";
			else
				cout << "寵物 " << getname() << "連續攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< 2 * attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else if (gethp() == 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//被攻擊的敵方中毒每回合-2HP(一場只發動一次, 產生影響的下一回合開始計算，持續到被攻擊方死亡)
class Poison :public AbilityPtr
{
public:
	Poison(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);
			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (getLaunch() == false || enemy.getisPoison() == false) {
				setLaunch(true);
				enemy.setPoison(true);
				enemy.addPoinsonTime();
				cout << enemy.getname() << "中毒了";
			}

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else if (gethp() == 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//攻擊時降低敵方速度值2(一場只發動一次, 產生影響的下一回合開始計算，持續到被攻擊方死亡)
class LowerSpeed :public AbilityPtr
{
public:
	LowerSpeed(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			locate(23, pos);

			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if ((getfirst() == true || enemy.getfirstIn() == true) && enemy.getability() != 4)
			{
				enemy.setSpeedtime(true);
				enemy.setfirstIn(false);
				setfirst(false);
			}
			else if (enemy.getability() == 4)
				cout << enemy.getname() << "免疫了能力";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else if (gethp() == 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//每次受到的傷害-2
class RockSkin :public AbilityPtr
{
public:
	RockSkin(detail toPush) :AbilityPtr(toPush) {};
	int Rockred() { return 2; }
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else if (gethp() == 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//攻擊時降低敵方防禦力2(一場只發動一次, 產生影響的下一回合開始計算，持續到被攻擊方死亡)
class LowerDefence :public AbilityPtr
{
public:
	LowerDefence(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			locate(23, pos);

			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if ((getfirst() == true || enemy.getfirstIn() == true) && enemy.getability() != 4)
			{
				enemy.setDefensetime(true);
				enemy.setfirstIn(false);
				setfirst(false);
			}
			else if (enemy.getability() == 4)
				cout << enemy.getname() << "免疫了能力";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
//攻擊時降低敵方攻擊力2(一場只發動一次, 產生影響的下一回合開始計算，持續到被攻擊方死亡)
class LowerAttack :public AbilityPtr
{
public:
	LowerAttack(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			locate(23, pos);

			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "寵物 " << getname() << " 攻擊" << "寵物 " << enemy.getname() << " 造成"
				<< attackVal << "點傷害 ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "減傷";

			if ((getfirst() == true || enemy.getfirstIn() == true) && enemy.getability() != 4)
			{
				enemy.setAttacktime(true);
				enemy.setfirstIn(false);
				setfirst(false);
			}
			else if (enemy.getability() == 4)
				cout << enemy.getname() << "免疫了能力 ";


			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "反擊了" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "點的傷害";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "死掉了";
					setColor(WHITE);
				}
			}
			else
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "死掉了";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " 躲避了攻擊";
		}
	}
};
#endif // !ABILITYDATA.H

