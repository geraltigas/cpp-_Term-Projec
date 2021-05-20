#include "ALL.h"

Conon::Conon(
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

change* Conon::next()
{
	return (new change());
};

Linked_list<utils::vector> Conon::move_v = Linked_list<utils::vector>();
