#include <iostream>
using std::cout;
using std::endl;
enum Type
{
	King,
	Knight,
	Rook,
	Elephant,
	Advisor,
	Conon,
	Soldier,
	vague
};

int main()
{
	cout << Type::King << endl;
};

