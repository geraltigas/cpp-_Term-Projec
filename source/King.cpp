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
		if (chess_is_selected)
		{
			change* changes = new change(this);
			changes->add(position.x,position.y, Trans::dis_selected);
			Vague* temp = map->vague_list[0];
			for (int i = map->vague_list.scale; i > 0; i--)
			{
				temp = map->vague_list[map->vague_list.scale-1];
				changes->add(temp->position.x, temp->position.y, Trans::dis_appear);
			};
			map->refresh(*changes);
			chess_is_selected = false;
			map->switchs(map->now_can_move);
		}
		else
		{
			auto& posi_list = this->position.implement(King::move_v);
			if (camp == Camp::jiang)
			{
				for (int i = 0; i < posi_list.scale; i++)
				{
					if (posi_list[i].x < 3 || posi_list[i].x > 5 || posi_list[i].y > 2)
					{
						posi_list.pop_by_rank(i);
						i--;
					}
				}
			}
			else 
			{
				for (int i = 0; i < posi_list.scale; i++)
				{
					posi& temp = posi_list[i];
					if (posi_list[i].x < 3 || posi_list[i].x > 5 || posi_list[i].y < 7)
					{
						posi_list.pop_by_rank(i);
						i--;
					}
				}
			}
			change* changes = next(posi_list);
			// ÊÍ·Åposi_list
			map->refresh(*changes);
			chess_is_selected = true;
			map->enable_all(false);
			map->enable(this->position.x, this->position.y, true);
		}
	};
	this->setClickFunc(call_back);
};
change* King::next(Linked_list<posi>& posi_list)
{
	change* changes = new change(this);
	posi temp = posi_list[0];
	changes->add(position.x, position.y, Trans::selected);
	for (int i = 0; i < posi_list.scale; i++)
	{
		temp = posi_list[i];
		if (map->now_map[temp.x][temp.y].camp == camp)
		{
			std::cout << "pop" << std::endl;
			posi_list.pop_by_rank(i);
			i--;
		};
	};
	for (int i = 0; i < posi_list.scale; i++)
	{
		temp = posi_list[i];
		changes->add(temp.x,temp.y,Trans::appear);
	};
	return changes;
};

Linked_list<utils::vector> King::move_v = Linked_list<utils::vector>();



