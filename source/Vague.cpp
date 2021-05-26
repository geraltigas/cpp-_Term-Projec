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
	call_back = [&]()
	{
		change changes = change(this);
		changes.add(position.x,position.y,Trans::move_to);
		changes.add(position.x, position.y, Trans::dis_appear);
		map->refresh(changes);
		from->chess_is_selected = false;
	};
	this->setClickFunc(call_back);
};

Vague::~Vague()
{
	//delete pic;
};

change* Vague::next(Linked_list<posi>& posi_list)
{
	return (new change());
};
