#include "ALL.h"

Vague::Vague(
	Chess* froms,
	Camp side,
	unsigned int xx,
	unsigned int yy,
	Type types,
	wchar_t* pics
) :
	Chess(side, xx, yy, types, pics), from(froms)
{
	call_back = []()
	{
		std::cout << "okkk" << std::endl;
	};
	this->setClickFunc(call_back);
};

change* Vague::next()
{
	return (new change());
};
