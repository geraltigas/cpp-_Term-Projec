#pragma once
#include "posi.h"
#include "change.h"
#include "Map_Chess.h"
#include "Vague.h"
#include "Advisor.h"
#include "Conon.h"
#include "Elephant.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Soldier.h"
#include "macro.h"
#include <easy2d/easy2d.h>
/*#include "change.h"
#include "macro.h"
#include "data_structure.h"
#include "Vague.h"
*/

struct space :public posi
{
public:
	Chess* chess;
	Vague* vague;
	Camp camp;
	space(unsigned int xx, unsigned int yy, Type types, Chess* chesss, Vague* vagues, Camp camps);
	space();
	space(space& copy);
};


class Map
{
public:
	static Linked_list<change*> change_list; // 每进行变化就加入链表，游戏后统一释放内存 也可用来复盘
	static Linked_list<Chess*> chess_list;
	static Linked_list<Vague*> vague_list;
	space now_map[9][10];
	Scene* host_scene;
	Camp now_can_move;
	Map(Scene* scene);
	void init();
	void meta_refresh(meta_change& meta_changes,change& changes);
	void refresh(change& changes);
	void meta_init(const space origin_map[9][10], unsigned int xx, unsigned int yy);
	void switchs(Camp& can_move);
	void switchs();
	void selected(posi& position);
	void dis_selected(posi& position);
	void appear(posi& position,Chess* froms);
	void dis_appear(posi& position);
	void move_to(Chess* from, posi& to_posi);
private:
	int meiruanyong;
};

Linked_list<change*> Map::change_list = Linked_list<change*>();
Linked_list<Chess*> Map::chess_list = Linked_list<Chess*>();
Linked_list<Vague*> Map::vague_list = Linked_list<Vague*>();




/*
#pragma once
#include "data_structure.h"
#include "posi.h"
#include "change.h"
#include "Map.h"
#include "macro.h"
#include <easy2d/easy2d.h>
class change;
class Map;
*/

