#include "ALL.h"

King::King(
	Camp side,
	unsigned int xx,
	unsigned int yy,
	Type types,
	wchar_t* pics
) :
	Chess(side, xx, yy, types, pics)
{
	call_back = [&]()
	{
		//appear 实例代码
		
		static int i = 0;
		if (i == 0)
		{
			change bian = change(this);
			bian.add(4, 0, Trans::appear);
			map->refresh(bian);
			i = 1;
		}
		else
		{
			change bian1 = change(this);
			bian1.add(4, 0, Trans::dis_appear);
			map->refresh(bian1);
			i = 0;
		}
		

		//selected 实例代码
		/*
		static int i = 0;
		if (i == 0)
		{
			change bian = change(this);
			bian.add(4, 9, Trans::selected);
			map->refresh(bian);
			i = 1;
		}
		else
		{
			change bian1 = change(this);
			bian1.add(4, 9, Trans::dis_selected);
			map->refresh(bian1);
			i = 0;
		}
		*/

		//move_to
		/*
		change bian = change(this);
		bian.add(4,0,Trans::move_to);
		map->refresh(bian);
		*/
		std::cout << "111" << std::endl;
	};
	this->setClickFunc(call_back);
};
change* King::next()
{
	if (!chess_is_selected)
	{
		chess_is_selected = !chess_is_selected;
		auto posis_trival = position.implement(move_v);
		if (position.x == 0 && position.y == 0)
		{
		}
		else if (position.x * position.y * position.x * position.y == 1)
		{
		}
		else
		{
		}
	}
	else
	{
		chess_is_selected = !chess_is_selected;
		auto posis_trival = position.implement(move_v);
		return (new change(this, posis_trival));
	}
};


Linked_list<utils::vector> King::move_v = Linked_list<utils::vector>();

