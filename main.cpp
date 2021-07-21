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
	Monster monster;  //�إߩǪ���Ʈw
	Player player(monster); // �إߪ��a 
	NPC npc(monster); //�إ�NPC
	Map map(player, npc); //�Ыئa��
	//====================================
	int x =5 , y = 5;
	locate(x, y);
	hidecursor();
	setColor(RED);
	cout << '@';
	char k;
	int oldx = 0, oldy = 0;
	while (1)
	{   //�P�_�ҿ������V
		if (kbhit()) {
			k = getkey();
			oldx = x, oldy = y;
			if (k == 'w') { y--; map.move(x, y, oldx, oldy);}//�i�Jmove
			else if (k == 'a') { x--; map.move(x, y, oldx, oldy);}
			else if (k == 's') { y++; map.move(x, y, oldx, oldy);}
			else if (k == 'd') { x++; map.move(x, y, oldx, oldy);}
			else if (k == ' ')
			{
				if (quitMessage()) {//�P�_�O�_�h�X�C��
					cls();
					locate(43, 25);
					cout<<"�A����o������: " << player.getSocre();
					anykey("(���@�U�~��)");
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
	cout << "�O�_�����C��?";
	locate(48, 22);
	cout << "�O";
	locate(58, 22);
	cout << "�_";
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