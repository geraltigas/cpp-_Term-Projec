#include "ALL.h"

void update(Linked_list<int>& to_be, int rank)
{
	for (int i = rank + 1; i < to_be.scale; i++)
	{
		to_be[i]--;
	}
};

Linked_list<posi>& conon_filter(Linked_list<posi>& to_be, Map* map, Conon* owner)
{
	Linked_list<int> head_rank = Linked_list<int>();
	for (int i = 0; i < to_be.scale; i++)
	{
		posi temp = to_be[i];
		Conon& chess = *owner;
		if (temp.x - chess.position.x == 1 || temp.x - chess.position.x == -1 || temp.y - chess.position.y == -1 || temp.y - chess.position.y == 1)
		{
			head_rank.add(i);
		}
	}
	for (int j = 0; j < head_rank.scale; j++)
	{
		int begin_rank = head_rank[j];
		std::cout << begin_rank << std::endl;
		int end_rank = (j == head_rank.scale - 1) ? to_be.scale-1: head_rank[j+1]-1;
		bool to_delete = false;
		int how_much = 0;
		for (int i = begin_rank; i <= end_rank; i++)
		{
			if (to_delete == false && map->now_map[to_be[i].x][to_be[i].y].chess != nullptr)
			{
				to_delete = true;
				how_much = 1;
				to_be.pop_by_rank(i);
				i--;
				end_rank--;
				update(head_rank, j);
				continue;
			}
			if (to_delete)
			{
				if (map->now_map[to_be[i].x][to_be[i].y].chess == nullptr)
				{
					to_be.pop_by_rank(i);
					i--;
					end_rank--;
					update(head_rank, j);
				}
				else {
					if ((map->now_map[to_be[i].x][to_be[i].y].chess->camp == ((owner->camp == Camp::jiang) ? Camp::shuai : Camp::jiang)) && how_much < 2)
					{
					}
					else
					{
						to_be.pop_by_rank(i);
						i--;
						end_rank--;
						update(head_rank, j);
					}
					how_much++;
				}
			}
		}
	}
	return to_be;
}

/*
posi temp = to_be[i];
Conon& chess = *owner;
if (temp.x - chess.position.x == 1 || temp.x - chess.position.x == -1 || temp.y - chess.position.y == -1 || temp.y - chess.position.y == 1)
{
	head_rank = i;
	head = temp;
}
if ((temp.x - head.x) * (temp.y - head.y) == 0)
{

}
*/

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
			auto& posi_list = this->position.implement(Conon::move_v);
			Linked_list<posi>& temp_to = conon_filter(posi_list,map,this);
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

change* Conon::next(Linked_list<posi>& posi_list)
{
	change* changes = new change(this);
	posi temp = posi_list[0];
	changes->add(position.x, position.y, Trans::selected);
	for (int i = 0; i < posi_list.scale; i++)
	{
		temp = posi_list[i];
		if (map->now_map[temp.x][temp.y].camp == camp)
		{
			posi_list.pop_by_rank(i);
			i--;
		};
	};
	for (int i = 0; i < posi_list.scale; i++)
	{
		temp = posi_list[i];
		changes->add(temp.x, temp.y, Trans::appear);
	};
	return changes;
};

Linked_list<utils::vector> Conon::move_v = Linked_list<utils::vector>();
