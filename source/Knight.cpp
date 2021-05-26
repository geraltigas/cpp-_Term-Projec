#include "ALL.h"

Linked_list<posi>& knight_filter(Linked_list<posi>& to_be, Map* map, Knight* owner)
{
	Chess* chess1 = nullptr;
	Chess* chess2 = nullptr;
	Chess* chess3 = nullptr;
	Chess* chess4 = nullptr;
	if (owner->position.x >= 1)
	{
		chess1 = map->now_map[owner->position.x - 1][owner->position.y].chess;
	}
	else 
	{
		chess1 = nullptr;
	}
	if (owner->position.x <= 7 )
	{
		chess2 = map->now_map[owner->position.x + 1][owner->position.y].chess;
	}
	else
	{
		chess2 = nullptr;
	}
	if (owner->position.y >= 1)
	{
		chess3 = map->now_map[owner->position.x][owner->position.y - 1].chess;
	}
	else
	{
		chess3 = nullptr;
	}
	if (owner->position.y <= 8)
	{
		chess4 = map->now_map[owner->position.x][owner->position.y + 1].chess;
	}
	else
	{
		chess4 = nullptr;
	}
	if ((chess1 == nullptr) && (chess2 == nullptr) && (chess3 == nullptr) && (chess4 == nullptr))
	{
		return to_be;
	}
	else
	{
		if (chess1 != nullptr)
		{
			for (int i = 0; i < to_be.scale; i++)
			{
				posi temp = to_be[i];
				if (temp.x - owner->position.x == -2)
				{
					to_be.pop_by_rank(i);
					i--;
				}
			}
		}
		if (chess2 != nullptr)
		{
			for (int i = 0; i < to_be.scale; i++)
			{
				posi temp = to_be[i];
				if (temp.x - owner->position.x == 2)
				{
					to_be.pop_by_rank(i);
					i--;
				}
			}
		}
		if (chess3 != nullptr)
		{
			for (int i = 0; i < to_be.scale; i++)
			{
				posi temp = to_be[i];
				if (temp.y - owner->position.y == -2)
				{
					to_be.pop_by_rank(i);
					i--;
				}
			}
		}
		if (chess4 != nullptr)
		{
			for (int i = 0; i < to_be.scale; i++)
			{
				posi temp = to_be[i];
				if (temp.y - owner->position.y == 2)
				{
					to_be.pop_by_rank(i);
					i--;
				}
			}
		}
		return to_be;
	}
};

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
			auto& posi_list = this->position.implement(Knight::move_v);
			Linked_list<posi>& temp = knight_filter(posi_list, map, this);
			change* changes = next(temp);
			// ÊÍ·Åposi_list
			map->refresh(*changes);
			chess_is_selected = true;
			map->enable_all(false);
			map->enable(this->position.x, this->position.y, true);
		}
	};
	this->setClickFunc(call_back);
};

change* Knight::next(Linked_list<posi>& posi_list)
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


Linked_list<utils::vector> Knight::move_v = Linked_list<utils::vector>();



