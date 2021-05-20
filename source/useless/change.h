#pragma once
#include "data_structure.h"
#include "meta_change.h"
#include "Chess.h"
class Chess;
struct change
{
public:
	Linked_list<meta_change> change_list;
	Chess* from;
	change():from(nullptr) {};
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