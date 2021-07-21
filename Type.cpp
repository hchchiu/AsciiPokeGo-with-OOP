#include "Type.h"

//�I�sloadTypeFile;
Type::Type()
{
	loadTypeFile();
}
//�N�۫g�ݩʪ��Ǫ��C��Ū�J
//�åB�s��data member��
void Type::loadTypeFile()
{
	ifstream inFile("type.csv");
	string space;
	stringstream ss;
	stringstream sn;
	int row = 0, col = 0;
	while (getline(inFile, space, '\n'))
	{
		ss.str("");
		ss.clear();
		ss << space;
		col = 0;
		while (getline(ss, space, ',')) {
			sn.str("");
			sn.clear();
			sn << space;
			sn >> type[row][col];
			col++;
		}
  		row++;
	}
}
//�N�ݩ�string�নint
//�åB�P�_��m
double Type::getAtkMult(string attack, string beattacked)
{
	int atkpos = getTypenum(attack);
	int beatkpos = getTypenum(beattacked);
	return type[atkpos][beatkpos];
}
//�^���ݩʬ۹�����int
int Type::getTypenum(string transfer)
{
	if (transfer == "Normal") { return 0; }
	else if (transfer == "Fire") { return 1; }
	else if (transfer == "Water") { return 2; }
	else if (transfer == "Electric") { return 3; }
	else if (transfer == "Grass") { return 4; }
	else if (transfer == "Poison") { return 7; }
	else if (transfer == "Ground") { return 8; }
	else if (transfer == "Flying") { return 9; }
	else if (transfer == "Bug") { return 11; }

}