#ifndef TYPE_H 
#define TYPE_H
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
class Type
{
public:
	Type();
	void loadTypeFile();
	double getAtkMult(string,string);
	int getTypenum(string);
private:
	double type[25][25];
};


#endif // !Type.h 


