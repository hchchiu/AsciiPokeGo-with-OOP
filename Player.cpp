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
//玩家判斷抓寶地形
//並且呼叫介面讓玩家選取是否抓取
void Player::Catch(int terrain)
{
	detail space;
	if (terrain == 1) { space = monsterdatabase.getRandMonster(1); }
	else if (terrain == 2) { space = monsterdatabase.getRandMonster(2); }
	else
		space = monsterdatabase.getRandMonster(0);

	//呼叫介面
	if (Interface(space)) {
		PlayerMonsterList.push_back(space);
	}
}
//介面判定是否抓取怪物
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
	cout << "Pokemon 名字:" << MonstertoCatch.name;
	locate(64, 12);
	cout << "屬性:" << MonstertoCatch.type;
	locate(64, 14);
	cout << "生命:" << MonstertoCatch.hp;
	locate(64, 16);
	cout << "攻擊:" << MonstertoCatch.atk;
	locate(64, 18);
	cout << "防禦:" << MonstertoCatch.def;
	locate(64, 20);
	cout << "速度:" << MonstertoCatch.speed;

	locate(10, 26);
	cout << "你的怪物清單: \n";
	if (PlayerMonsterList.size() != 0) {
		for (int i = 0; i < PlayerMonsterList.size(); ++i)
			cout << setw(20) << right << i + 1 << "." << PlayerMonsterList[i].name << endl;
	}
	else
		cout << setw(50) << right << "你目前沒有怪物\n\n\n";
	for (int i = 0; i < 110; i++)
		cout << "-";
	int answer = 1;
	locate(35, 32);
	cout << "抓捕";
	locate(70, 32);
	cout << "放棄";
	locate(34, 32);
	cout << ">";
	char input;
	//選擇介面
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
	//判定是否抓寶和抓寶是否成功
	//並且顯示訊息
	if (answer == 1 && fifty == 1) {
		if (PlayerMonsterList.size() == 3) {
			do {
				locate(1, 32);
				cout << setw(110) << right << " ";
				locate(45, 32);
				cout << setw(20) << left << "選擇一個怪物拋棄(1~3,0取消)";
				cin >> choose;
				if (choose == 0)
					return false;
			} while (choose > 3 || choose < 1);
			Discard(choose);
		}
		cls();
		locate(45, 20);
		cout << "成功捕獲!!!";
		anykey("(按任意鍵繼續)");
		return true;
	}
	else if (answer == 1)
	{
		cls();
		locate(45, 20);
		cout << "怪物跑走了!!!";
		anykey("(按任意鍵繼續)");
		return false;
	}
	else if (answer == 0)
		return false;
}
//當玩家背包已有三隻怪獸時
//讓玩家選擇拋棄的怪獸
void Player::Discard(int pos)
{
	pos -= 1;
	vector<detail>::iterator it1 = PlayerMonsterList.begin();
	it1 = it1 + pos;
	PlayerMonsterList.erase(it1);
}
//將原本是detail型態的怪物列表轉型成player戰鬥列表
//戰鬥時轉成物件
//用能力分割各種物件
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
//清空戰鬥列表
void Player::clearCombatlist()
{
	PlayerCombatList.clear();
}
//回傳目前存活的怪物
AbilityPtr* Player::getCurrentMonster()
{
	for (int i = 0; i < PlayerCombatList.size(); i++)
		if (PlayerCombatList[i]->gethp() > 0)
			return PlayerCombatList[i];

	return nullptr;
}
//讀取怪物的圖片
//戰鬥時呼叫
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
//戰鬥時顯示玩家背包裡的怪物
void Player::showAliveMonsters()
{
	resetColor();
	locate(15, 38);
	cout << "Player的Pokemon清單:\n";
	int pos = 39;
	for (int i = 0; i < PlayerCombatList.size(); ++i)
	{
		locate(15, pos++);
		cout << i + 1 << "." << PlayerCombatList[i]->getname();
	}
}
//顯示玩家當前背包的怪物
void Player::bagShowMonsters()
{
	resetColor();
	locate(15, 35);
	cout << "你的背包:\n";
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
//當玩家成功挑戰NPC時
//獲得分數100
void Player::addScore()
{
	score += 100;
}
int Player::getSize()
{
	return PlayerMonsterList.size();
}
//當玩家挑戰道館成功時
//紀錄道館
void Player::addFinishDokan(int dokan)
{
	finishDokan.push_back(dokan);
}
//判斷道館是否挑戰過
bool Player::dokanExist(int dokan)
{
	for (int i = 0; i < finishDokan.size(); ++i)
		if (finishDokan[i] == dokan)
			return true;

	return false;
}
//顯示玩家的徽章
void Player::showBadge()
{
	stringstream sn;
	string file;
	string dokanFile;
	string badge;
	locate(60, 15);
	cout << "玩家的獎牌:";
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