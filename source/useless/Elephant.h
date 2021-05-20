#pragma once
#include "Chess.h"

class Elephant :public Chess
{
public:
	static Linked_list<utils::vector> move_v;//在map中初始化
	Elephant(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change& next();
};

Linked_list<utils::vector> Elephant::move_v = Linked_list<utils::vector>();