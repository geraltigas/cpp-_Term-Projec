#include "ALL.h"

Linked_list<posi>& soldier_filter(Linked_list<posi>& to_be, Map* map, Soldier* owner)
{
	if(owner->camp == Camp::jiang)
	{
		for (int i = 0; i < to_be.scale; i++)
		{
			posi temp = to_be[i];
			if (temp.y - owner->position.y == -1)
			{
				to_be.pop_by_rank(i);
				i--;
				continue;
			}
			if (owner->position.y <= 4)
			{
				if (temp.x - owner->position.x != 0)
				{
					to_be.pop_by_rank(i);
					i--;
					continue;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < to_be.scale; i++)
		{
			posi temp = to_be[i];
			if (temp.y - owner->position.y == 1)
			{
				to_be.pop_by_rank(i);
				i--;
				continue;
			}
			if (owner->position.y >= 5)
			{
				if (temp.x - owner->position.x != 0)
				{
					to_be.pop_by_rank(i);
					i--;
					continue;
				}
			}
		}
	}
	return to_be;
};

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
		if (chess_is_selected)
		{
			change* changes = new change(this);
			changes->add(position.x, position.y, Trans::dis_selected);
			Vague* temp = map->vague_list[0];
			for (int i = map->vague_list.scale; i > 0; i--)
			{
				temp = map->vague_list[map->vague_list.scale - 1];
				changes->add(temp->position.x, temp->position.y, Trans::dis_appear);
			};
			map->refresh(*changes);
			chess_is_selected = false;
			map->switchs(map->now_can_move);
		}
		else
		{
			auto& posi_list = this->position.implement(Soldier::move_v);
			Linked_list<posi>& temp_to = soldier_filter(posi_list,map,this);
			change* changes = next(temp_to);
			// ÊÍ·Åposi_list
			map->refresh(*changes);
			chess_is_selected = true;
			map->enable_all(false);
			map->enable(this->position.x, this->position.y, true);
		}
	};
	this->setClickFunc(call_back);
};

change* Soldier::next(Linked_list<posi>& posi_list)
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
	for (int i = posi_list.scale - 1; i >= 0; i--)
	{
		std::cout << posi_list[i].x << " " << posi_list[i].y << std::endl;
	}
	for (int i = 0; i < posi_list.scale; i++)
	{
		temp = posi_list[i];
		changes->add(temp.x, temp.y, Trans::appear);
	};
	return changes;
};

Linked_list<utils::vector> Soldier::move_v = Linked_list<utils::vector>();
