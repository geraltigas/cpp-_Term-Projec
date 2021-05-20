#pragma once
#include "Map_Chess.h"

class Vague :public Chess
{
public:
	Chess* from;
	Vague(
		Chess* froms,
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change& next() override;
};
