#pragma once
#include <iostream>
using namespace std;
#include "posi.h"
#include "data_structure.h"

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
	meta_change(meta_change& changes):position(changes.position),transform(changes.transform)
	{
		changes.~meta_change();
	};
	~meta_change()
	{
		this->position.~posi();
	};
};
