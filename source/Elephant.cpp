#include "ALL.h"

Elephant::Elephant(
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

change* Elephant::next()
{
	return (new change());
};

Linked_list<utils::vector> Elephant::move_v = Linked_list<utils::vector>();
