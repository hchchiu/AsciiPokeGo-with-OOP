#include"Map.h"
#include<string>
string Ability[14] = {"Normal","Heal","Burning","Counter Attack","Immunology","LeechLife","Avoid","DoubleAttack",
					  "Poison","LowerSpeed","RockSkin","LowerDefence","LowerAttack" };
//初始化data member
Map::Map(Player& toplayerdata, NPC& tonpcdata)
	: playerdata(toplayerdata), npcdata(tonpcdata), mapLength(0)
{
	mapWidth[32] = {};

	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 150; j++)
			lvl[i][j] = ' ';
	loadMap();
}
//讀取地圖檔案
//將檔案存到lvl裡面
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
//將地圖畫出來
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
	//判斷玩家的分數
	//判斷玩家的背包怪物
	locate(15, 33);
	cout << "Score:" << playerdata.getSocre();
	playerdata.bagShowMonsters();
	playerdata.showBadge();
}
//玩家移動時進入
//判斷是否通過及是否進入戰鬥或是進入抓寶階段
void Map::move(int& x, int& y, int oldx, int oldy)
{
	char space, ahead, building;
	setColor(RED);
	if (lvl[y - 1][x - 1] == '~' || lvl[y - 1][x - 1] == ';'
		|| lvl[y - 1][x - 1] == '#' || lvl[y - 1][x - 1] == ' ')//判斷玩家是否可以通過
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
		if ((rand() % 9) == 1 && ahead != '#') {//判斷抓寶
			CatchCheck(lvl[y - 1][x - 1]);
			draw();
		}
		if (ahead == '#') {//進入道館
			if (lvl[y - 1][x - 2] != ' ')
				building = lvl[y - 1][x - 2];
			else
				building = lvl[y - 1][x];
			try//Exception判斷 是否具有戰鬥資格
			{
				fight(building);
			}
			catch (WrongPlayerPokemonSize& e) {//Exception 判定
				cls(); setColor(WHITE);
				rlutil::locate(35, 20);
				cout << e.what();
				anykey("(按下任何鍵繼續)");
			}		
			catch (WrongDokan& e) {//Exception 判定
				cls(); setColor(WHITE);
				rlutil::locate(35, 20);
				cout << e.what();
				anykey("(按下任何鍵繼續)");
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
//將經過的地形傳入並且判斷
void Map::CatchCheck(char space)
{
	int terrain = 0;
	if (space == ';') { terrain = 1; }  //Grass 
	else if (space == '~') { terrain = 2; } //Water

	playerdata.Catch(terrain);//進入抓寶
}
//進入戰鬥階段
//利用地形判斷進入哪個道館
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
	anykey("按一下戰鬥開始!!!");
	string message;
	while (true) {
		cls();
		message.clear();
		LowerCheck(message);

		locate(23, 42);
		cout << message;
		locate(23, 43);
		//判斷是否有人中毒及具有治癒能力
		playerdata.getCurrentMonster()->heal();
		npcdata.getCurrentMonster()->heal();
		playerdata.getCurrentMonster()->Poison();
		npcdata.getCurrentMonster()->Poison();

		//判斷是否有人死亡
		if (playerdata.getCurrentMonster() == nullptr || npcdata.getCurrentMonster() == nullptr) {
			cls();
			locate(45, 20);
			if (playerdata.getCurrentMonster() != nullptr) {
				playerdata.addScore();
				playerdata.addFinishDokan(takeBuild);
				cout << "玩家獲勝";
			}
			else
				cout << "NPC獲勝";

			playerdata.clearCombatlist();
			npcdata.clearCombatlist();
			anykey("(按一下繼續)");
			return;
		}
		//判斷攻擊順序 速度快的先攻 速度一樣就隨機判定
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

		//判斷是否有人死亡
		if (playerdata.getCurrentMonster() == nullptr || npcdata.getCurrentMonster() == nullptr) {
			cls();
			locate(45, 20);
			if (playerdata.getCurrentMonster() != nullptr) {
				playerdata.addScore();
				playerdata.addFinishDokan(takeBuild);
				cout << "玩家獲勝!!!";
			}
			else
				cout << "NPC獲勝!!!";
			playerdata.clearCombatlist();
			npcdata.clearCombatlist();
			anykey("(按一下繼續)");
			return;
		}
		showState();
		anykey("");
	}
}
//顯示玩家及NPC的Pokemon狀態
//顯示玩家及NPC的PPokemon圖片
void Map::showState()
{
	//--------------player detail-----------------------
	locate(15, 29);
	cout << "玩家的寵物:";
	locate(16, 30);
	cout << "名字: " << playerdata.getCurrentMonster()->getname();
	locate(16, 31);
	cout << "種類: " << playerdata.getCurrentMonster()->gettype();
	locate(16, 32);
	cout << "血量: " << playerdata.getCurrentMonster()->gethp() << "/" << playerdata.getCurrentMonster()->getMaxHP();
	locate(16, 33);
	cout << "攻擊: " << playerdata.getCurrentMonster()->getatk();
	locate(16, 34);
	cout << "防禦: " << playerdata.getCurrentMonster()->getdef();
	locate(16, 35);
	cout << "速度: " << playerdata.getCurrentMonster()->getspeed();
	locate(16, 36);
	cout << "能力: " << Ability[playerdata.getCurrentMonster()->getability()] << '\n';
	//--------------------playerdetail end--------------------

	//-------------------npcdetail----------------------------
	locate(62, 29);
	cout << "NPC的寵物:";
	locate(63, 30);
	cout << "名字: " << npcdata.getCurrentMonster()->getname();
	locate(63, 31);
	cout << "種類: " << npcdata.getCurrentMonster()->gettype();
	locate(63, 32);
	cout << "血量: " << npcdata.getCurrentMonster()->gethp() << "/" << npcdata.getCurrentMonster()->getMaxHP();
	locate(63, 33);
	cout << "攻擊: " << npcdata.getCurrentMonster()->getatk();
	locate(63, 34);
	cout << "防禦: " << npcdata.getCurrentMonster()->getdef();
	locate(63, 35);
	cout << "速度: " << npcdata.getCurrentMonster()->getspeed() << '\n';
	locate(63, 36);
	cout << "能力: " << Ability[npcdata.getCurrentMonster()->getability()] << '\n';
	//--------------------npcdetail end--------------------
	locate(1, 37);
	for (int i = 0; i < 110; ++i)
		cout << "-";

	playerdata.showAliveMonsters();
	npcdata.showAliveMonsters();

	playerdata.loadImage();
	npcdata.loadImage();
}
//能力"降低型"判斷
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