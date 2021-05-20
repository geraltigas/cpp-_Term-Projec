#include "ALL.h"
using std::cout;
using std::endl;


space::space(space& copy) :
	posi(copy.x, copy.y, copy.type),
	chess(copy.chess),
	vague(copy.vague),
	camp(copy.camp)
{
};

space::space() :posi(0, 0, Type::Null), chess(nullptr), vague(nullptr),camp(Camp::null){};

space::space(unsigned int xx, unsigned int yy, Type types, Chess* chesss, Vague* vagues, Camp camps) :
	posi(xx, yy, types),
	chess(chesss),
	vague(vagues),
	camp(camps)
{

};

const space origin_map[9][10] = {
		{{0,0,Type::Rook,nullptr,nullptr,Camp::jiang}    ,{0,1,Type::Null,nullptr,nullptr,Camp::null},{0,2,Type::Null,nullptr,nullptr,Camp::null}  ,{0,3,Type::Soldier,nullptr,nullptr,Camp::jiang},{0,4,Type::Null,nullptr,nullptr,Camp::null},{0,5,Type::Null,nullptr,nullptr,Camp::null},{0,6,Type::Soldier,nullptr,nullptr,Camp::shuai},{0,7,Type::Null,nullptr,nullptr,Camp::null}  ,{0,8,Type::Null,nullptr,nullptr,Camp::null},{0,9,Type::Rook,nullptr,nullptr,Camp::shuai}},
		{{1,0,Type::Knight,nullptr,nullptr,Camp::jiang}  ,{1,1,Type::Null,nullptr,nullptr,Camp::null},{1,2,Type::Conon,nullptr,nullptr,Camp::jiang},{1,3,Type::Null,nullptr,nullptr,Camp::null}   ,{1,4,Type::Null,nullptr,nullptr,Camp::null},{1,5,Type::Null,nullptr,nullptr,Camp::null},{1,6,Type::Null,nullptr,nullptr,Camp::null}   ,{1,7,Type::Conon,nullptr,nullptr,Camp::shuai},{1,8,Type::Null,nullptr,nullptr,Camp::null},{1,9,Type::Knight,nullptr,nullptr,Camp::shuai}},
		{{2,0,Type::Elephant,nullptr,nullptr,Camp::jiang},{2,1,Type::Null,nullptr,nullptr,Camp::null},{2,2,Type::Null,nullptr,nullptr,Camp::null}  ,{2,3,Type::Soldier,nullptr,nullptr,Camp::jiang},{2,4,Type::Null,nullptr,nullptr,Camp::null},{2,5,Type::Null,nullptr,nullptr,Camp::null},{2,6,Type::Soldier,nullptr,nullptr,Camp::shuai},{2,7,Type::Null,nullptr,nullptr,Camp::null}  ,{2,8,Type::Null,nullptr,nullptr,Camp::null},{2,9,Type::Elephant,nullptr,nullptr,Camp::shuai}},
		{{3,0,Type::Advisor,nullptr,nullptr,Camp::jiang} ,{3,1,Type::Null,nullptr,nullptr,Camp::null},{3,2,Type::Null,nullptr,nullptr,Camp::null}  ,{3,3,Type::Null,nullptr,nullptr,Camp::null}   ,{3,4,Type::Null,nullptr,nullptr,Camp::null},{3,5,Type::Null,nullptr,nullptr,Camp::null},{3,6,Type::Null,nullptr,nullptr,Camp::null}   ,{3,7,Type::Null,nullptr,nullptr,Camp::null}  ,{3,8,Type::Null,nullptr,nullptr,Camp::null},{3,9,Type::Advisor,nullptr,nullptr,Camp::shuai}},
		{{4,0,Type::King,nullptr,nullptr,Camp::jiang}    ,{4,1,Type::Null,nullptr,nullptr,Camp::null},{4,2,Type::Null,nullptr,nullptr,Camp::null}  ,{4,3,Type::Soldier,nullptr,nullptr,Camp::jiang},{4,4,Type::Null,nullptr,nullptr,Camp::null},{4,5,Type::Null,nullptr,nullptr,Camp::null},{4,6,Type::Soldier,nullptr,nullptr,Camp::shuai},{4,7,Type::Null,nullptr,nullptr,Camp::null}  ,{4,8,Type::Null,nullptr,nullptr,Camp::null},{4,9,Type::King,nullptr,nullptr,Camp::shuai}},
		{{5,0,Type::Advisor,nullptr,nullptr,Camp::jiang} ,{5,1,Type::Null,nullptr,nullptr,Camp::null},{5,2,Type::Null,nullptr,nullptr,Camp::null}  ,{5,3,Type::Null,nullptr,nullptr,Camp::null}   ,{5,4,Type::Null,nullptr,nullptr,Camp::null},{5,5,Type::Null,nullptr,nullptr,Camp::null},{5,6,Type::Null,nullptr,nullptr,Camp::null}   ,{5,7,Type::Null,nullptr,nullptr,Camp::null}  ,{5,8,Type::Null,nullptr,nullptr,Camp::null},{5,9,Type::Advisor,nullptr,nullptr,Camp::shuai}},
		{{6,0,Type::Elephant,nullptr,nullptr,Camp::jiang},{6,1,Type::Null,nullptr,nullptr,Camp::null},{6,2,Type::Null,nullptr,nullptr,Camp::null}  ,{6,3,Type::Soldier,nullptr,nullptr,Camp::jiang},{6,4,Type::Null,nullptr,nullptr,Camp::null},{6,5,Type::Null,nullptr,nullptr,Camp::null},{6,6,Type::Soldier,nullptr,nullptr,Camp::shuai},{6,7,Type::Null,nullptr,nullptr,Camp::null}  ,{6,8,Type::Null,nullptr,nullptr,Camp::null},{6,9,Type::Elephant,nullptr,nullptr,Camp::shuai}},
		{{7,0,Type::Knight,nullptr,nullptr,Camp::jiang}  ,{7,1,Type::Null,nullptr,nullptr,Camp::null},{7,2,Type::Conon,nullptr,nullptr,Camp::jiang},{7,3,Type::Null,nullptr,nullptr,Camp::null}   ,{7,4,Type::Null,nullptr,nullptr,Camp::null},{7,5,Type::Null,nullptr,nullptr,Camp::null},{7,6,Type::Null,nullptr,nullptr,Camp::null}   ,{7,7,Type::Conon,nullptr,nullptr,Camp::shuai},{7,8,Type::Null,nullptr,nullptr,Camp::null},{7,9,Type::Knight,nullptr,nullptr,Camp::shuai}},
		{{8,0,Type::Rook,nullptr,nullptr,Camp::jiang}    ,{8,1,Type::Null,nullptr,nullptr,Camp::null},{8,2,Type::Null,nullptr,nullptr,Camp::null}  ,{8,3,Type::Soldier,nullptr,nullptr,Camp::jiang},{8,4,Type::Null,nullptr,nullptr,Camp::null},{8,5,Type::Null,nullptr,nullptr,Camp::null},{8,6,Type::Soldier,nullptr,nullptr,Camp::shuai},{8,7,Type::Null,nullptr,nullptr,Camp::null}  ,{8,8,Type::Null,nullptr,nullptr,Camp::null},{8,9,Type::Rook,nullptr,nullptr,Camp::shuai}}
};



Map::Map(easy2d::Scene* scene)
{
	meiruanyong = 0;
	host_scene = scene;
	cout << (int)host_scene << endl;
	change_list = *(new Linked_list<change*>());
	chess_list = *(new Linked_list<Chess*>());
	now_can_move = Camp::shuai;
};

Camp Map::who_win()
{
	static Linked_list<Chess*> king_list = Linked_list<Chess*>();
	if (king_list.scale == 0)
	{
		for (int i = 0; i < chess_list.scale; i++)
		{
			if (chess_list[i]->type == Type::King)
			{
				king_list.add(chess_list[i]);
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (king_list[i]->is_alive == false)
		{
			return (king_list[i]->camp == Camp::jiang ? Camp::shuai : Camp::jiang);
		}
	}
};

void Map::selected(posi& position)
{
	auto scale_to = easy2d::gcnew easy2d::ScaleTo(0.1, 1.15f);
	Chess* chess_to = (now_map[position.x][position.y]).chess;
	chess_to->runAction(scale_to);
	chess_to->chess_is_selected = 1;
};

void Map::dis_selected(posi& position)
{
	auto scale_back = easy2d::gcnew easy2d::ScaleTo(0.1, 1.0f);
	Chess* chess_back = (now_map[position.x][position.y]).chess;
	chess_back->runAction(scale_back);
	chess_back->chess_is_selected = 0;
};

void Map::appear(posi& position, Chess* froms)
{
	Vague* vague = new Vague(froms, froms->camp, position.x, position.y, Type::vague, VAGUE);
	Chess* chess_behind = now_map[position.x][position.y].chess;
	now_map[position.x][position.y].vague = vague;
	host_scene->removeChild(chess_behind);
	host_scene->addChild((easy2d::Button*)vague);
	host_scene->addChild(chess_behind);
	vague_list.add(vague);
};

void Map::dis_appear(posi& position)
{
	Vague* vague_to = now_map[position.x][position.y].vague;
	cout << (int)vague_to << endl;
	now_map[position.x][position.y].vague = nullptr;
	host_scene->removeChild(vague_to);
	delete vague_to;
};

void Map::move_to(Chess* from, posi& to_posi)
{
	for (; vague_list.scale != 0;)
	{
		Vague& vague_to = *vague_list[vague_list.scale - 1];
		host_scene->removeChild(&vague_to);
		now_map[vague_to.position.x][vague_to.position.y].vague = nullptr;
		delete& vague_to;
	};
	space& from_space = now_map[from->position.x][from->position.y];
	space& to_space = now_map[to_posi.x][to_posi.y];
	if (to_space.chess == nullptr)
	{
		to_space.chess = from_space.chess;
		from_space.chess = nullptr;
		auto scale_back = easy2d::gcnew easy2d::ScaleTo(0.2f, 1.0f);
		auto move = easy2d::gcnew easy2d::MoveTo(0.2f, easy2d::Point(to_posi.xy_to_pixel().x, to_posi.xy_to_pixel().y));
		auto spawn = easy2d::gcnew easy2d::Spawn({ scale_back,move });
		to_space.chess->runAction(spawn);
	}
	else
	{
		to_space.chess->is_alive = 0;
		Chess* temp = to_space.chess;
		to_space.chess = from_space.chess;
		from_space.chess = nullptr;
		auto scale_back = easy2d::gcnew easy2d::ScaleTo(0.2f, 1.0f);
		auto move = easy2d::gcnew easy2d::MoveTo(0.2f, easy2d::Point(to_posi.xy_to_pixel().x, to_posi.xy_to_pixel().y));
		auto spawn = easy2d::gcnew easy2d::Spawn({ scale_back,move });
		auto call_back = easy2d::gcnew easy2d::CallFunc([&]() {
			host_scene->removeChild(temp);
			});
		auto sequence = easy2d::gcnew easy2d::Sequence({ spawn , call_back });
		to_space.chess->runAction(sequence);
	};
};

void Map::enable_all(bool control)
{
	for (int i = 0; i < chess_list.scale ; i++)
	{
		if (chess_list[i] == nullptr)
		{
			chess_list[i]->setEnable(false);
		}
	}
};

void Map::enable(unsigned int xx, unsigned int yy, bool control)
{
	now_map[xx][yy].chess->setEnable(control);
};

void Map::enable_half(Camp camp,bool control)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = (camp == Camp::jiang) ? 0 : 5; j < ((camp == Camp::shuai) ? 5 : 10); j++)
		{
			enable(i,j,control);
		}
	}
};

void Map::switchs(Camp& can_move)
{
	for (int i = 0; i < chess_list.scale; i++)
	{
		Chess* ref = chess_list[i];
		if (ref != nullptr)
		{
			if (ref->camp != can_move)
			{
				ref->setEnable(false);
			}
			else
			{
				ref->setEnable(true);
			}
		}
	};
};
void Map::switchs()
{
	now_can_move = (now_can_move == Camp::jiang) ? Camp::shuai : Camp::jiang;
	switchs(now_can_move);
	cout << "switch" << endl;
};

Chess* create_chess(space const& spaces) //without vague and Null
{
	if (spaces.camp == Camp::jiang)
	{
		if (spaces.type == Type::King) return new King(Camp::jiang, spaces.x, spaces.y, Type::King, JIANG_KING);
		else if (spaces.type == Type::Knight) return new Knight(Camp::jiang, spaces.x, spaces.y, Type::Knight, JIANG_KNIGHT);
		else if (spaces.type == Type::Rook)return new Rook
		(Camp::jiang, spaces.x, spaces.y, Type::Rook, JIANG_ROOK);
		else if (spaces.type == Type::Elephant)return new Elephant(Camp::jiang, spaces.x, spaces.y, Type::Elephant, JIANG_ELEPHANT);
		else if (spaces.type == Type::Advisor)return new Advisor
		(Camp::jiang, spaces.x, spaces.y, Type::Advisor, JIANG_ADVISOR);
		else if (spaces.type == Type::Conon)return new Conon
		(Camp::jiang, spaces.x, spaces.y, Type::Conon, JIANG_CONON);
		else if (spaces.type == Type::Soldier)return new Soldier(Camp::jiang, spaces.x, spaces.y, Type::Soldier, JIANG_SOLDIER);
		else return nullptr;
	}
	else if (spaces.camp == Camp::shuai)
	{
		if (spaces.type == Type::King) return new King(Camp::shuai, spaces.x, spaces.y, Type::King, SHUAI_KING);
		else if (spaces.type == Type::Knight) return new Knight(Camp::shuai, spaces.x, spaces.y, Type::Knight, SHUAI_KNIGHT);
		else if (spaces.type == Type::Rook)return new Rook
		(Camp::shuai, spaces.x, spaces.y, Type::Rook, SHUAI_ROOK);
		else if (spaces.type == Type::Elephant)return new Elephant(Camp::shuai, spaces.x, spaces.y, Type::Elephant, SHUAI_ELEPHANT);
		else if (spaces.type == Type::Advisor)return new Advisor
		(Camp::shuai, spaces.x, spaces.y, Type::Advisor, SHUAI_ADVISOR);
		else if (spaces.type == Type::Conon)return new Conon
		(Camp::shuai, spaces.x, spaces.y, Type::Conon, SHUAI_CONON);
		else if (spaces.type == Type::Soldier)return new Soldier(Camp::shuai, spaces.x, spaces.y, Type::Soldier, SHUAI_SOLDIER);
		else return nullptr;
	}
	else
	{
		return nullptr;
	}
	//return (new Chess(spaces.camp,spaces.x,spaces.y,spaces.type,get_pic(spaces.camp,spaces.type)));
};


void Map::meta_init(const space origin_map[9][10], unsigned int xx, unsigned int yy)
{
	const space& temp = origin_map[xx][yy];
	Chess* temps = create_chess(temp);
	if (temps != nullptr)
	{
		cout << "the posi of temp(space): " << xx << " " << yy << endl;
		cout << "the posi of temps(chess*)" << temps->position.x << " " << temps->position.y << endl;
	}
	now_map[xx][yy] = space(xx, yy, temp.type, temps, nullptr, temp.camp);
	cout << xx << " " << yy << " " << (int)now_map[xx][yy].type << " " << temps << " " << (int)nullptr << " " << (int)now_map[xx][yy].camp << endl;
	Map::chess_list.add(temps);
};


void Map::init()
{
	for (unsigned int x = 0; x <= 8; x++)
	{
		for (unsigned int y = 0; y <= 9; y++)
		{
			meta_init(origin_map, x, y);
		}
	}
	for (int i = 0; i < chess_list.scale; i++)
	{
		if (chess_list[i] != nullptr)
		{
			host_scene->addChild(chess_list[i]);
			chess_list[i]->map = this;
		}
	}
	cout << "map init done" << endl;
};

void Map::meta_refresh(meta_change& meta_changes, change& changes)
{
	switch (meta_changes.transform)
	{
	case Trans::selected: selected(meta_changes.position); break;
	case Trans::dis_selected: dis_selected(meta_changes.position); break;
	case Trans::dis_appear: dis_appear(meta_changes.position); break;
	case Trans::appear: appear(meta_changes.position, changes.from); break;
	case Trans::move_from: break;
	case Trans::move_to: move_to(changes.from, meta_changes.position);
	}

};

void Map::refresh(change& changes)
{
	for (int i = 0; i < changes.change_list.scale; i++)
	{
		meta_change& ref = changes.change_list[i];
		meta_refresh(ref, changes);
	};
};


Linked_list<change*> Map::change_list = Linked_list<change*>();
Linked_list<Chess*> Map::chess_list = Linked_list<Chess*>();
Linked_list<Vague*> Map::vague_list = Linked_list<Vague*>();





