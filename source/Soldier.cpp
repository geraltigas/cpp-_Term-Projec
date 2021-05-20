#include "ALL.h"

Soldier::Soldier(
	Camp side,
	unsigned int xx,
	unsigned int yy,
	Type types,
	wchar_t* pics
) :
	Chess(side, xx, yy, types, pics)
{
	call_back = [this]()
	{

	};
};

change* Soldier::next()
{
	return (new change());
};

Linked_list<utils::vector> Soldier::move_v = Linked_list<utils::vector>();
