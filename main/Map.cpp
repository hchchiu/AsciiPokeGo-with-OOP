#include"Map.h"
#include<string>
string Ability[14] = {"Normal","Heal","Burning","Counter Attack","Immunology","LeechLife","Avoid","DoubleAttack",
					  "Poison","LowerSpeed","RockSkin","LowerDefence","LowerAttack" };
//��l��data member
Map::Map(Player& toplayerdata, NPC& tonpcdata)
	: playerdata(toplayerdata), npcdata(tonpcdata), mapLength(0)
{
	mapWidth[32] = {};

	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 150; j++)
			lvl[i][j] = ' ';
	loadMap();
}
//Ū���a���ɮ�
//�N�ɮצs��lvl�̭�
void Map::loadMap()
{
	string check[200];
	ifstream inFile("yzumap.txt");
	while (getline(inFile, check[mapLength], '\n'))
		mapLength++;

	for (int i = 0; i < mapLength; ++i) {
		mapWidth[i] = check[i].size();
		for (int j = 0; j < check[i].size(); j++) {
			lvl[i][j] = check[i][j];
		}
	}

	inFile.close();
	draw();
}
//�N�a�ϵe�X��
void Map::draw()
{
	resetColor();
	cls();
	for (unsigned int i = 0; i < mapLength; i++) {
		for (unsigned int j = 0; j < mapWidth[i]; ++j) {
			switch (lvl[i][j]) {
			case ';':
				setBackgroundColor(GREEN);
				cout << lvl[i][j];
				break;
			case'!':
				setColor(BROWN);
				cout << lvl[i][j];
				break;
			case'~':
				setBackgroundColor(BLUE);
				cout << lvl[i][j];
				break;
			case'#':
				setColor(YELLOW);
				cout << lvl[i][j];
				break;
			default:
				setBackgroundColor(BLACK);
				setColor(WHITE);
				cout << lvl[i][j];
			}
		}
		cout << endl;
	}
	//�P�_���a������
	//�P�_���a���I�]�Ǫ�
	locate(15, 33);
	cout << "Score:" << playerdata.getSocre();
	playerdata.bagShowMonsters();
	playerdata.showBadge();
}
//���a���ʮɶi�J
//�P�_�O�_�q�L�άO�_�i�J�԰��άO�i�J���_���q
void Map::move(int& x, int& y, int oldx, int oldy)
{
	char space, ahead, building;
	setColor(RED);
	if (lvl[y - 1][x - 1] == '~' || lvl[y - 1][x - 1] == ';'
		|| lvl[y - 1][x - 1] == '#' || lvl[y - 1][x - 1] == ' ')//�P�_���a�O�_�i�H�q�L
	{
		ahead = lvl[y - 1][x - 1];
		space = lvl[oldy - 1][oldx - 1];
		locate(oldx, oldy);
		setColor(WHITE);
		if (space == ';') { setBackgroundColor(GREEN); cout << space; }  //Grass
		else if (space == '~') { setBackgroundColor(BLUE); cout << space; }  //Water
		else if (space == '#') { setColor(YELLOW); cout << space; } //Entrance
		else { setBackgroundColor(BLACK); cout << space; }
		resetColor();
		if ((rand() % 9) == 1 && ahead != '#') {//�P�_���_
			CatchCheck(lvl[y - 1][x - 1]);
			draw();
		}
		if (ahead == '#') {//�i�J�D�]
			if (lvl[y - 1][x - 2] != ' ')
				building = lvl[y - 1][x - 2];
			else
				building = lvl[y - 1][x];
			try//Exception�P�_ �O�_�㦳�԰����
			{
				fight(building);
			}
			catch (WrongPlayerPokemonSize& e) {//Exception �P�w
				cls(); setColor(WHITE);
				rlutil::locate(35, 20);
				cout << e.what();
				anykey("(���U�������~��)");
			}		
			catch (WrongDokan& e) {//Exception �P�w
				cls(); setColor(WHITE);
				rlutil::locate(35, 20);
				cout << e.what();
				anykey("(���U�������~��)");
			}
			draw();
			x = oldx; y = oldy;
		}

		if (ahead == ';') { setBackgroundColor(GREEN); }  //Grass
		else if (ahead == '~') { setBackgroundColor(BLUE); }  //Water
		setColor(RED);
		locate(x, y);
		cout << "@";

	}
	else {
		x = oldx;
		y = oldy;
	}
}
//�N�g�L���a�ζǤJ�åB�P�_
void Map::CatchCheck(char space)
{
	int terrain = 0;
	if (space == ';') { terrain = 1; }  //Grass 
	else if (space == '~') { terrain = 2; } //Water

	playerdata.Catch(terrain);//�i�J���_
}
//�i�J�԰����q
//�Q�Φa�ΧP�_�i�J���ӹD�]
void Map::fight(char building)
{
	resetColor();
	int takeBuild = building - '0';
	if (takeBuild >= 5 && takeBuild < 10)
		takeBuild -= 1;
	else if (takeBuild > 9)
		takeBuild -= 8;
	if (playerdata.getSize() < 1)
		throw  WrongPlayerPokemonSize();

	if (playerdata.dokanExist(takeBuild))
		throw WrongDokan();

	playerdata.MakeCombatList();
	npcdata.MakeCombatList(takeBuild);
	int cnt = 1;
	cls();
	showState();
	rlutil::locate(40, 45);
	anykey("���@�U�԰��}�l!!!");
	string message;
	while (true) {
		cls();
		message.clear();
		LowerCheck(message);

		locate(23, 42);
		cout << message;
		locate(23, 43);
		//�P�_�O�_���H���r�Ψ㦳�v¡��O
		playerdata.getCurrentMonster()->heal();
		npcdata.getCurrentMonster()->heal();
		playerdata.getCurrentMonster()->Poison();
		npcdata.getCurrentMonster()->Poison();

		//�P�_�O�_���H���`
		if (playerdata.getCurrentMonster() == nullptr || npcdata.getCurrentMonster() == nullptr) {
			cls();
			locate(45, 20);
			if (playerdata.getCurrentMonster() != nullptr) {
				playerdata.addScore();
				playerdata.addFinishDokan(takeBuild);
				cout << "���a���";
			}
			else
				cout << "NPC���";

			playerdata.clearCombatlist();
			npcdata.clearCombatlist();
			anykey("(���@�U�~��)");
			return;
		}
		//�P�_�������� �t�ק֪����� �t�פ@�˴N�H���P�w
		int decide = 2;
		if (playerdata.getCurrentMonster()->getspeed() == npcdata.getCurrentMonster()->getspeed())
		{
			decide = rand() % 2;
		}
		if ((playerdata.getCurrentMonster()->getspeed() > npcdata.getCurrentMonster()->getspeed()) || decide == 0)
		{
			playerdata.getCurrentMonster()->attack(*npcdata.getCurrentMonster(), 44);
			if (npcdata.getCurrentMonster() != nullptr)
				npcdata.getCurrentMonster()->attack(*playerdata.getCurrentMonster(), 45);
		}
		else if ((playerdata.getCurrentMonster()->getspeed() < npcdata.getCurrentMonster()->getspeed()) || decide == 1)
		{
			npcdata.getCurrentMonster()->attack(*playerdata.getCurrentMonster(), 44);
			if (playerdata.getCurrentMonster() != nullptr)
				playerdata.getCurrentMonster()->attack(*npcdata.getCurrentMonster(), 45);

		}

		//�P�_�O�_���H���`
		if (playerdata.getCurrentMonster() == nullptr || npcdata.getCurrentMonster() == nullptr) {
			cls();
			locate(45, 20);
			if (playerdata.getCurrentMonster() != nullptr) {
				playerdata.addScore();
				playerdata.addFinishDokan(takeBuild);
				cout << "���a���!!!";
			}
			else
				cout << "NPC���!!!";
			playerdata.clearCombatlist();
			npcdata.clearCombatlist();
			anykey("(���@�U�~��)");
			return;
		}
		showState();
		anykey("");
	}
}
//��ܪ��a��NPC��Pokemon���A
//��ܪ��a��NPC��PPokemon�Ϥ�
void Map::showState()
{
	//--------------player detail-----------------------
	locate(15, 29);
	cout << "���a���d��:";
	locate(16, 30);
	cout << "�W�r: " << playerdata.getCurrentMonster()->getname();
	locate(16, 31);
	cout << "����: " << playerdata.getCurrentMonster()->gettype();
	locate(16, 32);
	cout << "��q: " << playerdata.getCurrentMonster()->gethp() << "/" << playerdata.getCurrentMonster()->getMaxHP();
	locate(16, 33);
	cout << "����: " << playerdata.getCurrentMonster()->getatk();
	locate(16, 34);
	cout << "���m: " << playerdata.getCurrentMonster()->getdef();
	locate(16, 35);
	cout << "�t��: " << playerdata.getCurrentMonster()->getspeed();
	locate(16, 36);
	cout << "��O: " << Ability[playerdata.getCurrentMonster()->getability()] << '\n';
	//--------------------playerdetail end--------------------

	//-------------------npcdetail----------------------------
	locate(62, 29);
	cout << "NPC���d��:";
	locate(63, 30);
	cout << "�W�r: " << npcdata.getCurrentMonster()->getname();
	locate(63, 31);
	cout << "����: " << npcdata.getCurrentMonster()->gettype();
	locate(63, 32);
	cout << "��q: " << npcdata.getCurrentMonster()->gethp() << "/" << npcdata.getCurrentMonster()->getMaxHP();
	locate(63, 33);
	cout << "����: " << npcdata.getCurrentMonster()->getatk();
	locate(63, 34);
	cout << "���m: " << npcdata.getCurrentMonster()->getdef();
	locate(63, 35);
	cout << "�t��: " << npcdata.getCurrentMonster()->getspeed() << '\n';
	locate(63, 36);
	cout << "��O: " << Ability[npcdata.getCurrentMonster()->getability()] << '\n';
	//--------------------npcdetail end--------------------
	locate(1, 37);
	for (int i = 0; i < 110; ++i)
		cout << "-";

	playerdata.showAliveMonsters();
	npcdata.showAliveMonsters();

	playerdata.loadImage();
	npcdata.loadImage();
}
//��O"���C��"�P�_
void Map::LowerCheck(string& message)
{
	//---------------------Lower Speed-----------------------------
	playerdata.getCurrentMonster()->LowerSpeedAffect(*npcdata.getCurrentMonster(),message);
	npcdata.getCurrentMonster()->LowerSpeedAffect(*playerdata.getCurrentMonster(), message);
	//---------------------Lower ATK-------------------------------
	npcdata.getCurrentMonster()->LowerAtkAffect(*playerdata.getCurrentMonster(), message);
	playerdata.getCurrentMonster()->LowerAtkAffect(*npcdata.getCurrentMonster(), message);
	//---------------------Lower Deffence--------------------------
	npcdata.getCurrentMonster()->LowerDeffenceAffect(*playerdata.getCurrentMonster(), message);
	playerdata.getCurrentMonster()->LowerDeffenceAffect(*npcdata.getCurrentMonster(), message);
}