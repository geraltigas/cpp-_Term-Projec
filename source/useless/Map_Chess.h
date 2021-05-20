#pragma once
#include "Vague.h"
#include "Advisor.h"
#include "Conon.h"
#include "Elephant.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Soldier.h"
#include "posi.h"
#include "change.h"
#include "macro.h"
#include "data_structure.h"
#include "posi.h"
#include "change.h"
#include <easy2d/easy2d.h>
class Map;

class Chess :public easy2d::Button
{
public:
	static Linked_list<utils::vector> move_v;
	Camp camp;
	posi position;
	easy2d::Sprite* pic;
	easy2d::Function<void()> call_back;// 在子类构造函数内传入lambda函数
	Type type;
	bool chess_is_selected;
	bool is_alive;
	Map* map;//  这个要在chinese chess 初始化时初始化
	friend struct change;
	Chess(
		Camp side,
		posi& positions,
		wchar_t* pics,
		Type types
	);

	Chess(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change& next() = 0;
	void set_map(Map* maps);
};



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

using easy2d::Scene;
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
	void meta_refresh(meta_change& meta_changes, change& changes);
	void refresh(change& changes);
	void meta_init(const space origin_map[9][10], unsigned int xx, unsigned int yy);
	void switchs(Camp& can_move);
	void switchs();
	void selected(posi& position);
	void dis_selected(posi& position);
	void appear(posi& position, Chess* froms);
	void dis_appear(posi& position);
	void move_to(Chess* from, posi& to_posi);
private:
	int meiruanyong;
};

Linked_list<change*> Map::change_list = Linked_list<change*>();
Linked_list<Chess*> Map::chess_list = Linked_list<Chess*>();
Linked_list<Vague*> Map::vague_list = Linked_list<Vague*>();

