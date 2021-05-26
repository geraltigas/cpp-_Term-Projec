#pragma once
#include <easy2d/easy2d.h>
#include "macro.h"
#include <iostream>
class Chess;
class Advisor;
class Chinese_chess;
class Conon;
class Elephant;
class King;
class Knight;
class Map;
struct meta_change;
struct pixel_posi;
struct posi;
struct change;
class Rook;
class Soldier;
class Vague;


namespace utils
{
	struct vector
	{
	public:
		int delta_x;
		int delta_y;
		vector(int x, int y) :delta_x(x), delta_y(y)
		{
		};
	};
}


//----------- 类型
enum class Type
{
	King,
	Knight,
	Rook,
	Elephant,
	Advisor,
	Conon,
	Soldier,
	vague,
	Null
};

//-----------  阵营
enum class Camp
{
	jiang,
	shuai,
	null
};

//----------- 变换
enum class Trans
{
	selected,
	dis_selected,
	appear,
	dis_appear,
	move_to,
	move_from
};

//-----------  链表容器
template<typename T>
class Node
{
public:
	Node<T>* pre;
	Node<T>* succ;
	T data;
	Node(Node<T>* pres, Node<T>* succs, T& data) :pre(pres), succ(succs), data(data)
	{
	};
	Node(T& datas) :data(datas), pre(nullptr), succ(nullptr)
	{
	};
};


template<typename T>
class Linked_list
{
public:
	unsigned int scale;
	Node<T>* begin;
	Node<T>* end;
	Node<T>* now_at;
	int now_rank;
	Linked_list() :scale(0), begin(nullptr), end(nullptr), now_at(nullptr), now_rank(-1)
	{
	};
	void add(T& data)
	{
		if (scale)
		{
			end->succ = new Node<T>(end, nullptr, data);
			end = end->succ;
			data.~T();
			detect();
		}
		else
		{
			begin = new Node<T>(nullptr, nullptr, data);
			end = begin;
			now_at = begin;
			now_rank = 0;
			data.~T();
		}
		scale++;
	};
	T& next()
	{
		if (now_at->succ)
		{
			now_at = now_at->succ;
			now_rank++;
			return now_at->data;
		}
	};
	T& ahead()
	{
		if (now_at->pre)
		{
			now_at = now_at->pre;
			now_rank--;
			return now_at->data;
		}
	};
	T& operator[](int rank)
	{
		if (rank >= scale)
		{
			return end->data;
		}
		else
		{
			if (rank == now_rank)
			{
				return now_at->data;
			}
			else if (rank > now_rank)
			{
				while (rank != now_rank)
				{
					next();
				}
				return now_at->data;
			}
			else
			{
				while (rank != now_rank)
				{
					ahead();
				}
				return now_at->data;
			}
		}
	};
	void insert_after(int rank, const T& data)
	{
		(*this)[rank];
		Node<T>* temp = now_at->succ;
		now_at->succ = new Node<T>(const_cast<T&>(data));
		now_at->succ->pre = now_at;
		now_at->succ->succ = temp;
		if (temp != nullptr)
		{
			temp->pre = now_at->succ;
		}
		else
		{
			end = now_at->succ;
		}
		scale++;
	};
	void detect()
	{
		if (now_rank >= scale)
		{
			now_at = end;
			now_rank = scale - 1;
		};
	};
	T pop()
	{
		if (scale > 0)
		{
			(*this)[scale - 1];
			T temp = now_at->data;
			Node<T>* temps = now_at;
			now_at = now_at->pre;
			now_rank--;
			scale--;
			delete temps;
			return temp;
		}
		else
		{
			return *(T*)(nullptr);
		}
	};
	void pop_by_rank(int rank)
	{
		(*this)[rank];
		if (now_at->succ == nullptr)
		{
			pop();
		}
		else if (now_at->pre == nullptr)
		{
			begin = begin->succ;
			scale--;
			begin->pre = nullptr;
			delete now_at;
			now_at = begin;
		}
		else
		{
			Node<T>* temp1 = now_at->pre;
			Node<T>* temp2 = now_at->succ;
			delete now_at;
			temp1->succ = temp2;
			temp2->pre = temp1;
			scale--;
			now_at = temp2;
		}
	};
};





struct pixel_posi
{
public:
	int x;
	int y;
	unsigned int raw_x;
	unsigned int raw_y;
	// constructing
	pixel_posi(unsigned int raw_xx, unsigned int raw_yy) :raw_x(raw_xx), raw_y(raw_yy)
	{
		x = raw_xx * 68 + 86;
		y = raw_yy * 67 + (raw_yy <= 4 ? 46 : 62);

	};
	// end
	~pixel_posi()
	{

	};
};


struct posi
{
public:
	unsigned int x;
	unsigned int y;
	Type type;
	posi(unsigned int xx, unsigned int yy, Type types) :x(xx), y(yy), type(types)
	{
	};
	posi(posi& script)
	{
		x = script.x;
		y = script.y;
		type = script.type;
		script.~posi();
	};
	~posi()
	{
	};
	pixel_posi& xy_to_pixel() const
	{
		return *(new pixel_posi(x, y));
	};
	// 将向量组作用在初始位置并返回posi的组，只筛选了超越棋盘的posi
	Linked_list<posi>& implement(Linked_list<utils::vector>& delta)
	{
		Linked_list<posi>& list_posi = *(new Linked_list<posi>());
		for (int i = 0; i < delta.scale; i++)
		{
			int lz_x = x + delta[i].delta_x;
			int lz_y = y + delta[i].delta_y;
			if ((lz_x >= 0) && (lz_x <= 8) && (lz_y >= 0) && (lz_y <= 9))
			{
				list_posi.add(*(new posi(lz_x, lz_y, type)));
			};
		};
		return list_posi;
	};
};

class Chess :public easy2d::Button
{
public:
	static Linked_list<utils::vector> move_v;
	Camp camp;
	posi position;
	posi raw_posi;
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
	virtual change* next(Linked_list<posi>& posi_list) = 0;
	void set_map(Map* maps);
	void back_to_origin();
};

class Vague :public Chess
{
public:
	Chess* from;
	Vague(
		Chess* froms,
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	~Vague();
	virtual change* next(Linked_list<posi>& posi_list) override;
};

class Soldier :public Chess
{
public:
	static Linked_list<utils::vector> move_v;//在map中初始化
	Soldier(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change* next(Linked_list<posi>& posi_list);
};





class Rook :public Chess
{
public:
	static Linked_list<utils::vector> move_v;//在map中初始化
	Rook(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change* next(Linked_list<posi>& posi_list);
};








struct meta_change
{
public:
	posi position;
	//x
	//y
	//type
	Trans transform;
	// selected
	// dis_selected
	// appear
	// dis_appear
	// move_to
	// move_from
/*
space:
posi
chess*
vague*
camp
*/
	meta_change(posi& positions, Trans trans) :position(positions), transform(trans)
	{
	};
	meta_change(meta_change& changes) :position(changes.position), transform(changes.transform)
	{
		changes.~meta_change();
	};
	~meta_change()
	{
		this->position.~posi();
	};
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


class Map
{
public:
	static Linked_list<change*> change_list; // 每进行变化就加入链表，游戏后统一释放内存 也可用来复盘
	static Linked_list<Chess*> chess_list;
	static Linked_list<Vague*> vague_list;
	static Linked_list<King*> king_list;
	Chinese_chess* chess_game;
	space now_map[9][10];
	easy2d::Scene* host_scene;
	Camp now_can_move;
	Camp who_win;
	Map(easy2d::Scene* scene,Chinese_chess* chess_ga);
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
	void enable_all(bool control);
	void enable(unsigned int xx, unsigned int yy, bool control);
	void enable_half(Camp side,bool control);
	void detect_win();
	void clear_change_list();
	void back_to_game();
	void back_map(Map* th);
	void fupan();
private:
	int meiruanyong;
};






class Knight :public Chess
{
public:
	static Linked_list<utils::vector> move_v;//在map中初始化
	Knight(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change* next(Linked_list<posi>& posi_list);
};



class King :public Chess
{
public:
	static Linked_list<utils::vector> move_v;
	King(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);

	virtual change* next(Linked_list<posi>& posi_list);
};





class Elephant :public Chess
{
public:
	static Linked_list<utils::vector> move_v;//在map中初始化
	Elephant(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change* next(Linked_list<posi>& posi_list);
};


class Conon :public Chess
{
public:
	static Linked_list<utils::vector> move_v;//在map中初始化
	Conon(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change* next(Linked_list<posi>& posi_list);
};


class Chinese_chess
{
public:
	easy2d::Scene* scene_two;
	easy2d::Scene* scene_three;
	easy2d::Sprite* background;
	easy2d::Sprite* button_again;
	easy2d::Sprite* button_back;
	easy2d::Text* text;
	easy2d::Button* button_ag;
	easy2d::Button* button_ba;
	Map* map;
	Chinese_chess();
	void preload_source() const;
	void init_window() const;
	void init_scene_two() const;
	void init_scene_three() const;
	void init() const;
	void begin();
	void win_enter();
};

class Advisor :public Chess
{
public:
	static Linked_list<utils::vector> move_v;//在map中初始化
	Advisor(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change* next(Linked_list<posi>& posi_list);
};



struct change
{
public:
	Linked_list<meta_change> change_list;
	Chess* from;
	change() :from(nullptr) {};
	change(Chess* froms) :change_list(), from(froms)
	{
	};
	change(Chess* froms, Linked_list<posi>& trival) :from(froms)
	{
	};
	void add(meta_change& meta_change_to_add)
	{
		change_list.add(meta_change_to_add);
	};
	void add(unsigned int xx,
		unsigned int yy,
		Trans transforms)
	{
		add(*(new meta_change(*(new posi(xx, yy, Type::Null)), transforms)));
	};
	meta_change& operator[](int rank)
	{
		return this->change_list[rank];
	};
};


