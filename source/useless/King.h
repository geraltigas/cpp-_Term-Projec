#pragma once
#include "Chess.h"
#include "data_structure.h"
#include "Map.h"
#include "posi.h"
class Map;
class King :public Chess
{
public:
	static Linked_list<utils::vector> move_v;
	King(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);

	virtual change& next();
};

Linked_list<utils::vector> King::move_v = Linked_list<utils::vector>();
