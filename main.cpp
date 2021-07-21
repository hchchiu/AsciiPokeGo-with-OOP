//1071512 Final Project
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rlutil.h"
#include "Map.h"
#include "Monster.h"
#include "Player.h"
#include "NPC.h"
#define waitkey rlutil::anykey("");
bool quitMessage();

int main()
{
	system("mode con cols=110 lines=50");
	srand(time(NULL));
	Monster monster;  //建立怪物資料庫
	Player player(monster); // 建立玩家 
	NPC npc(monster); //建立NPC
	Map map(player, npc); //創建地圖
	//====================================
	int x =5 , y = 5;
	locate(x, y);
	hidecursor();
	setColor(RED);
	cout << '@';
	char k;
	int oldx = 0, oldy = 0;
	while (1)
	{   //判斷所選取的方向
		if (kbhit()) {
			k = getkey();
			oldx = x, oldy = y;
			if (k == 'w') { y--; map.move(x, y, oldx, oldy);}//進入move
			else if (k == 'a') { x--; map.move(x, y, oldx, oldy);}
			else if (k == 's') { y++; map.move(x, y, oldx, oldy);}
			else if (k == 'd') { x++; map.move(x, y, oldx, oldy);}
			else if (k == ' ')
			{
				if (quitMessage()) {//判斷是否退出遊戲
					cls();
					locate(43, 25);
					cout<<"你所獲得的分數: " << player.getSocre();
					anykey("(按一下繼續)");
					break;
				}
				else {
					map.draw();
					locate(x, y);
					setColor(RED);
					cout << "@";
				}
			}
			
		}
	}
	cls();
	//system("pause");
}
bool quitMessage()
{
	resetColor();
	cls();
	locate(46, 19);
	for (int i = 0; i < 16; ++i)
		cout << "*";
	for (int j = 0; j < 4; ++j) {
		locate(46,20+j);
		cout << setw(15) << left << "*" << right << "*";
	}
	locate(46,24);
	for (int i = 0; i < 16; ++i)
		cout << "*";
	locate(48, 20);
	cout << "是否結束遊戲?";
	locate(48, 22);
	cout << "是";
	locate(58, 22);
	cout << "否";
	locate(47, 22);
	cout << ">";
	int answer = 1;
	char quit;
	while (quit = getch())
	{
		if (quit == 'a') {
			locate(47, 22);
			cout << ">";
			locate(57, 22);
			cout << " ";
			answer = 1;
		}
		else if (quit == 'd') {
			locate(57, 22);
			cout << ">";
			locate(47, 22);
			cout << " ";
			answer = 0;
		}
		else if (quit == ' ')
			break;
	}
	if (answer == 1) 
		return true;
	else
		return false;
}