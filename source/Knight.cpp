#include "ALL.h"

Knight::Knight(
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

change* Knight::next()
{
	return (new change());
};


Linked_list<utils::vector> Knight::move_v = Linked_list<utils::vector>();
