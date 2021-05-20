#include "ALL.h"

Rook::Rook(
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

change* Rook::next()
{
	return (new change());
};

Linked_list<utils::vector> Rook::move_v = Linked_list<utils::vector>();
