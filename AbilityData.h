#ifndef ABILITYDATA_H
#define ABILITYDATA_H
#include "Monster.h"
#include "AbilityPtr.h"
#include "rlutil.h"
#include<iostream>
using namespace std;
using namespace rlutil;
//#include "Player.h"
//�@��Ǫ�
class Normal :public AbilityPtr
{
public:
	Normal(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//�C�^�X�^�_HP3
class Heal :public AbilityPtr
{
public:
	Heal(detail toPush) :AbilityPtr(toPush) {};
	void heal()
	{
		if (gethp() + 3 < getMaxHP()) {
			sethp(gethp() + 3);
			cout << getname() << "��_�F3�I�ͩR";
		}
		else {
			cout << getname() << "��_�F" << getMaxHP() - gethp() << "�I�ͩR";
			sethp(getMaxHP());
		}
	}
	void attack(AbilityPtr & enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//�H�����[�������m�v�T���ˮ`1~3
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

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal - spAtk << "�I�ˮ` " << " �U�N��O�y��" << spAtk << "�I�ˮ`";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//����1/5�Ҩ��ˮ`
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

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//�K�̭��C��O�Ȫ��S���O
class Immunology :public AbilityPtr
{
public:
	Immunology(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);
			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
// �C�������l��2~3HP
class LeechLife :public AbilityPtr
{
public:
	LeechLife(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(20, pos);
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout <<" "<< enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else {
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(20, pos);
			cout << enemy.getname() << " ���פF����";
		}
		if (enemy.gethp() > 0) {
			int absorbHP = 0;
			absorbHP = rand() % 2 + 2;
			if ((gethp() + absorbHP) < getMaxHP())
				sethp(gethp() + absorbHP);
			else
				sethp(getMaxHP());

			cout << getname() << " �l���F" << absorbHP << "�I���ͩR";

			enemy.sethp(enemy.gethp() - absorbHP);
		}
		else {
			locate(23, pos + 2);
			setColor(RED);
			cout << enemy.getname() << "�����F";
			setColor(WHITE);
		}
	}
};
//1/5���v�j�ק���
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
			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				if (gethp() <= 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else if (gethp() <= 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//1/5���v�⦸����
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
				cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";
			else
				cout << "�d�� " << getname() << "�s�����" << "�d�� " << enemy.getname() << " �y��"
				<< 2 * attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else if (gethp() == 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//�Q�������Ĥ褤�r�C�^�X-2HP(�@���u�o�ʤ@��, ���ͼv�T���U�@�^�X�}�l�p��A�����Q�����覺�`)
class Poison :public AbilityPtr
{
public:
	Poison(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			locate(23, pos);
			enemy.sethp(enemy.gethp() - attackVal);
			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (getLaunch() == false || enemy.getisPoison() == false) {
				setLaunch(true);
				enemy.setPoison(true);
				enemy.addPoinsonTime();
				cout << enemy.getname() << "���r�F";
			}

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0)
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else if (gethp() == 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//�����ɭ��C�Ĥ�t�׭�2(�@���u�o�ʤ@��, ���ͼv�T���U�@�^�X�}�l�p��A�����Q�����覺�`)
class LowerSpeed :public AbilityPtr
{
public:
	LowerSpeed(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			locate(23, pos);

			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if ((getfirst() == true || enemy.getfirstIn() == true) && enemy.getability() != 4)
			{
				enemy.setSpeedtime(true);
				enemy.setfirstIn(false);
				setfirst(false);
			}
			else if (enemy.getability() == 4)
				cout << enemy.getname() << "�K�̤F��O";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else if (gethp() == 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//�C�����쪺�ˮ`-2
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

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else if (gethp() == 0)
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//�����ɭ��C�Ĥ訾�m�O2(�@���u�o�ʤ@��, ���ͼv�T���U�@�^�X�}�l�p��A�����Q�����覺�`)
class LowerDefence :public AbilityPtr
{
public:
	LowerDefence(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			locate(23, pos);

			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if ((getfirst() == true || enemy.getfirstIn() == true) && enemy.getability() != 4)
			{
				enemy.setDefensetime(true);
				enemy.setfirstIn(false);
				setfirst(false);
			}
			else if (enemy.getability() == 4)
				cout << enemy.getname() << "�K�̤F��O";

			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
//�����ɭ��C�Ĥ�����O2(�@���u�o�ʤ@��, ���ͼv�T���U�@�^�X�}�l�p��A�����Q�����覺�`)
class LowerAttack :public AbilityPtr
{
public:
	LowerAttack(detail toPush) :AbilityPtr(toPush) {};
	void attack(AbilityPtr& enemy, int pos) {
		if (enemy.ProbabilityCheck()) {
			locate(23, pos);

			int attackVal = (getatk() - enemy.getdef() - enemy.Rockred()) * Typenum.getAtkMult(gettype(), enemy.gettype());
			enemy.sethp(enemy.gethp() - attackVal);

			cout << "�d�� " << getname() << " ����" << "�d�� " << enemy.getname() << " �y��"
				<< attackVal << "�I�ˮ` ";

			if (enemy.Rockred() > 0)
				cout << " " << enemy.getname() << "���";

			if ((getfirst() == true || enemy.getfirstIn() == true) && enemy.getability() != 4)
			{
				enemy.setAttacktime(true);
				enemy.setfirstIn(false);
				setfirst(false);
			}
			else if (enemy.getability() == 4)
				cout << enemy.getname() << "�K�̤F��O ";


			if (enemy.gethp() > 0) {
				sethp(gethp() - (enemy.getCounterAttack(getatk() - enemy.getdef())));
				if (enemy.getCounterAttack(getatk() - enemy.getdef()) > 0) {
					cout << enemy.getname() << "�����F" << enemy.getCounterAttack(getatk() - enemy.getdef()) << "�I���ˮ`";
				}
				if (gethp() == 0)
				{
					locate(23, pos + 2);
					setColor(RED);
					cout << getname() << "�����F";
					setColor(WHITE);
				}
			}
			else
			{
				locate(23, pos + 2);
				setColor(RED);
				cout << enemy.getname() << "�����F";
				setColor(WHITE);
			}
		}
		else {
			locate(23, pos);
			cout << enemy.getname() << " ���פF����";
		}
	}
};
#endif // !ABILITYDATA.H

