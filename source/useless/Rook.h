#pragma once
#include "Chess.h"

class Rook :public Chess
{
public:
	static Linked_list<utils::vector> move_v;//��map�г�ʼ��
	Rook(
		Camp side,
		unsigned int xx,
		unsigned int yy,
		Type types,
		wchar_t* pics
	);
	virtual change& next();
};

Linked_list<utils::vector> Rook::move_v = Linked_list<utils::vector>();
