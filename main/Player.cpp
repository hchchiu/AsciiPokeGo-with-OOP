#include "Player.h"
#include "rlutil.h"
#include "AbilityData.h"
#include "Map.h"
#include <string>
#include <iomanip>
using namespace rlutil;
char MonsterImage[35][10] = { "","001.txt","002.txt","003.txt","004.txt","005.txt","006.txt","007.txt","008.txt","009.txt","010.txt",
							 "011.txt","012.txt","013.txt","014.txt","015.txt","016.txt","017.txt","018.txt","019.txt","020.txt",
							 "021.txt","022.txt","023.txt","024.txt","025.txt","026.txt","027.txt","028.txt","029.txt",
							 "030.txt","031.txt","032.txt","033.txt","034.txt" };
Player::Player(Monster& toMonsterdatavase)
	:monsterdatabase(toMonsterdatavase), score(0)
{
}
//���a�P�_���_�a��
//�åB�I�s���������a����O�_���
void Player::Catch(int terrain)
{
	detail space;
	if (terrain == 1) { space = monsterdatabase.getRandMonster(1); }
	else if (terrain == 2) { space = monsterdatabase.getRandMonster(2); }
	else
		space = monsterdatabase.getRandMonster(0);

	//�I�s����
	if (Interface(space)) {
		PlayerMonsterList.push_back(space);
	}
}
//�����P�w�O�_����Ǫ�
bool Player::Interface(detail MonstertoCatch)
{
	cls();
	string file="color/";
	string image;
	file += MonsterImage[MonstertoCatch.No];
	ifstream inFile(file);
	while (getline(inFile, image, '\n'))
		cout << image << endl;

	inFile.close();
	setColor(WHITE);
	locate(56, 10);
	cout << "Pokemon �W�r:" << MonstertoCatch.name;
	locate(64, 12);
	cout << "�ݩ�:" << MonstertoCatch.type;
	locate(64, 14);
	cout << "�ͩR:" << MonstertoCatch.hp;
	locate(64, 16);
	cout << "����:" << MonstertoCatch.atk;
	locate(64, 18);
	cout << "���m:" << MonstertoCatch.def;
	locate(64, 20);
	cout << "�t��:" << MonstertoCatch.speed;

	locate(10, 26);
	cout << "�A���Ǫ��M��: \n";
	if (PlayerMonsterList.size() != 0) {
		for (int i = 0; i < PlayerMonsterList.size(); ++i)
			cout << setw(20) << right << i + 1 << "." << PlayerMonsterList[i].name << endl;
	}
	else
		cout << setw(50) << right << "�A�ثe�S���Ǫ�\n\n\n";
	for (int i = 0; i < 110; i++)
		cout << "-";
	int answer = 1;
	locate(35, 32);
	cout << "�쮷";
	locate(70, 32);
	cout << "���";
	locate(34, 32);
	cout << ">";
	char input;
	//��ܤ���
	while (input = getch())
	{
		if (input == 'a') {
			locate(34, 32);
			cout << ">";
			locate(69, 32);
			cout << " ";
			answer = 1;
		}
		else if (input == 'd') {
			locate(69, 32);
			cout << ">";
			locate(34, 32);
			cout << " ";
			answer = 0;
		}
		else if (input == ' ')
			break;
	}
	int choose = 0;
	int fifty = rand() % 2;
	//�P�w�O�_���_�M���_�O�_���\
	//�åB��ܰT��
	if (answer == 1 && fifty == 1) {
		if (PlayerMonsterList.size() == 3) {
			do {
				locate(1, 32);
				cout << setw(110) << right << " ";
				locate(45, 32);
				cout << setw(20) << left << "��ܤ@�өǪ��߱�(1~3,0����)";
				cin >> choose;
				if (choose == 0)
					return false;
			} while (choose > 3 || choose < 1);
			Discard(choose);
		}
		cls();
		locate(45, 20);
		cout << "���\����!!!";
		anykey("(�����N���~��)");
		return true;
	}
	else if (answer == 1)
	{
		cls();
		locate(45, 20);
		cout << "�Ǫ��]���F!!!";
		anykey("(�����N���~��)");
		return false;
	}
	else if (answer == 0)
		return false;
}
//���a�I�]�w���T�����~��
//�����a��ܩ߱󪺩��~
void Player::Discard(int pos)
{
	pos -= 1;
	vector<detail>::iterator it1 = PlayerMonsterList.begin();
	it1 = it1 + pos;
	PlayerMonsterList.erase(it1);
}
//�N�쥻�Odetail���A���Ǫ��C���૬��player�԰��C��
//�԰����ন����
//�ί�O���ΦU�ت���
void Player::MakeCombatList()
{
	for (int i = 0; i < PlayerMonsterList.size(); ++i) {
		switch (PlayerMonsterList[i].ability) {
		case 0: {PlayerCombatList.push_back(new Normal(PlayerMonsterList[i])); break; }
		case 1: {PlayerCombatList.push_back(new Heal(PlayerMonsterList[i])); break; }
		case 2: {PlayerCombatList.push_back(new Burning(PlayerMonsterList[i])); break; }
		case 3: {PlayerCombatList.push_back(new CounterAttack(PlayerMonsterList[i])); break; }
		case 4: {PlayerCombatList.push_back(new Immunology(PlayerMonsterList[i])); break; }
		case 5: {PlayerCombatList.push_back(new LeechLife(PlayerMonsterList[i])); break; }
		case 6: {PlayerCombatList.push_back(new Avoid(PlayerMonsterList[i])); break; }
		case 7: {PlayerCombatList.push_back(new DoubleAttack(PlayerMonsterList[i])); break; }
		case 8: {PlayerCombatList.push_back(new Poison(PlayerMonsterList[i])); break; }
		case 9: {PlayerCombatList.push_back(new LowerSpeed(PlayerMonsterList[i])); break; }
		case 10: {PlayerCombatList.push_back(new RockSkin(PlayerMonsterList[i])); break; }
		case 11: {PlayerCombatList.push_back(new LowerDefence(PlayerMonsterList[i])); break; }
		case 12: {PlayerCombatList.push_back(new LowerAttack(PlayerMonsterList[i])); break; }
		}
	}
}
//�M�ž԰��C��
void Player::clearCombatlist()
{
	PlayerCombatList.clear();
}
//�^�ǥثe�s�����Ǫ�
AbilityPtr* Player::getCurrentMonster()
{
	for (int i = 0; i < PlayerCombatList.size(); i++)
		if (PlayerCombatList[i]->gethp() > 0)
			return PlayerCombatList[i];

	return nullptr;
}
//Ū���Ǫ����Ϥ�
//�԰��ɩI�s
void Player::loadImage()
{
	string file="color/";
	string image;
	int pos = 1;
	file += MonsterImage[getCurrentMonster()->getNo()];
	ifstream inFile(file);
	while (getline(inFile, image, '\n')) {
		locate(1, pos++);
		cout << image << endl;
	}
	inFile.close();
}
//�԰�����ܪ��a�I�]�̪��Ǫ�
void Player::showAliveMonsters()
{
	resetColor();
	locate(15, 38);
	cout << "Player��Pokemon�M��:\n";
	int pos = 39;
	for (int i = 0; i < PlayerCombatList.size(); ++i)
	{
		locate(15, pos++);
		cout << i + 1 << "." << PlayerCombatList[i]->getname();
	}
}
//��ܪ��a��e�I�]���Ǫ�
void Player::bagShowMonsters()
{
	resetColor();
	locate(15, 35);
	cout << "�A���I�]:\n";
	int pos = 36;
	for (int i = 0; i < PlayerMonsterList.size(); ++i)
	{
		locate(15, pos++);
		cout << i + 1 << "." << PlayerMonsterList[i].name;
	}
}

int Player::getSocre()
{
	return score;
}
//���a���\�D��NPC��
//��o����100
void Player::addScore()
{
	score += 100;
}
int Player::getSize()
{
	return PlayerMonsterList.size();
}
//���a�D�ԹD�]���\��
//�����D�]
void Player::addFinishDokan(int dokan)
{
	finishDokan.push_back(dokan);
}
//�P�_�D�]�O�_�D�ԹL
bool Player::dokanExist(int dokan)
{
	for (int i = 0; i < finishDokan.size(); ++i)
		if (finishDokan[i] == dokan)
			return true;

	return false;
}
//��ܪ��a������
void Player::showBadge()
{
	stringstream sn;
	string file;
	string dokanFile;
	string badge;
	locate(60, 15);
	cout << "���a�����P:";
	int pos = 17;
	int lpos = 60;
	for (int i = 0; i < finishDokan.size(); ++i)
	{
		sn.str("");
		sn.clear();
		file = "badge";
		sn << finishDokan[i];
		sn >> dokanFile;
		file += dokanFile;
		file += ".txt";
		ifstream inFile(file);
		while (getline(inFile, badge, '\n'))
		{
			locate(lpos, pos++);
			cout << badge << endl;
		}
		if (pos == 35)
			lpos++;
		file.clear();
		dokanFile.clear();
		inFile.close();
	}
}