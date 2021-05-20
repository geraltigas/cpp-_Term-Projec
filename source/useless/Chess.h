#pragma once
#include "Map_Chess.h"
#include "data_structure.h"
#include "posi.h"
#include "Map.h"
#include "change.h"
#include <easy2d/easy2d.h>
class Chess :public easy2d::Button
{
public:
	static Linked_list<utils::vector> move_v;
	Camp camp;
	posi position;
	easy2d::Sprite* pic;
	easy2d::Function<void()> call_back;// �����๹�캯���ڴ���lambda����
	Type type;
	bool chess_is_selected;
	bool is_alive;
	Map* map;//  ���Ҫ��chinese chess ��ʼ��ʱ��ʼ��
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
