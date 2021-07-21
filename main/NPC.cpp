#include "NPC.h"
char monsterImage[35][10] = { "","001.txt","002.txt","003.txt","004.txt","005.txt","006.txt","007.txt","008.txt","009.txt","010.txt",
							 "011.txt","012.txt","013.txt","014.txt","015.txt","016.txt","017.txt","018.txt","019.txt","020.txt",
							 "021.txt","022.txt","023.txt","024.txt","025.txt","026.txt","027.txt","028.txt","029.txt",
							 "030.txt","031.txt","032.txt","033.txt","034.txt" };
//��l��NPC���Ǫ�
//�I�sgetMonster
NPC::NPC(Monster& tomonsterdatabase_)
	:monsterdatabase(tomonsterdatabase_)
{
	getMonster();
}
//�H���ƨåB�qdatabase���X�Ǫ�
void NPC::getMonster()
{
	int pos = 0;
	for (int i = 1; i < 13; ++i) {
		for (int j = 0; j < 3; ++j) {
			pos = rand() % 34;
			NpcMonsterlist[i][j] = monsterdatabase.getNPCMonster(pos);//for debugging
		}
	}
}
//�N�쥻�Odetail���A���Ǫ��C���૬
//�԰����ন����
//�ί�O���ΦU�ت���
void NPC::MakeCombatList(int terrain)
{
	for (int i = 0; i < 3; ++i) {
		switch (NpcMonsterlist[terrain][i].ability) {
		case 0: {NpcCombatlist.push_back(new Normal(NpcMonsterlist[terrain][i])); break; }
		case 1: {NpcCombatlist.push_back(new Heal(NpcMonsterlist[terrain][i])); break; }
		case 2: {NpcCombatlist.push_back(new Burning(NpcMonsterlist[terrain][i])); break; }
		case 3: {NpcCombatlist.push_back(new CounterAttack(NpcMonsterlist[terrain][i])); break; }
		case 4: {NpcCombatlist.push_back(new Immunology(NpcMonsterlist[terrain][i])); break; }
		case 5: {NpcCombatlist.push_back(new LeechLife(NpcMonsterlist[terrain][i])); break; }
		case 6: {NpcCombatlist.push_back(new Avoid(NpcMonsterlist[terrain][i])); break; }
		case 7: {NpcCombatlist.push_back(new DoubleAttack(NpcMonsterlist[terrain][i])); break; }
		case 8: {NpcCombatlist.push_back(new Poison(NpcMonsterlist[terrain][i])); break; }
		case 9: {NpcCombatlist.push_back(new LowerSpeed(NpcMonsterlist[terrain][i])); break; }
		case 10: {NpcCombatlist.push_back(new RockSkin(NpcMonsterlist[terrain][i])); break; }
		case 11: {NpcCombatlist.push_back(new LowerDefence(NpcMonsterlist[terrain][i])); break; }
		case 12: {NpcCombatlist.push_back(new LowerAttack(NpcMonsterlist[terrain][i])); break; }
		}
	}
}
//�^�Ƿ�e�٬��۪��Ǫ�
AbilityPtr* NPC::getCurrentMonster()
{
	for (int i = 0; i < 3; i++)
		if (NpcCombatlist[i]->gethp() > 0)
			return NpcCombatlist[i];

	return nullptr;
}
//Ū���Ǫ����Ϥ�
//��ȮɩI�s
void NPC::loadImage()
{
	string file="color/";
	string image;
	file += monsterImage[getCurrentMonster()->getNo()];
	int locpos = 2;
	ifstream infile(file);
	while (getline(infile, image, '\n')) {
		locate(50, locpos);
		locpos++;
		cout << image;
	}
	infile.close();
}
//��ԮɩI�s
//���NPC�I�]�̪��T���Ǫ�
void NPC::showAliveMonsters()
{
	resetColor();
	locate(63, 38);
	cout << "NPC��Pokemon�M��:";
	int pos = 39;
	for (int i = 0; i < 3; ++i)
	{
		locate(63, pos++);
		cout<<i+1<<"." << NpcCombatlist[i]->getname();
	}
}
//�M�Ź�ԭI�]
void NPC::clearCombatlist()
{
	NpcCombatlist.clear();
}