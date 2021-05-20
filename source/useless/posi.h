#pragma once
#include "data_structure.h"
#include "pixel_posi.h"
#include "utils.h"

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
			if ((lz_x >= 0) && (lz_x <= 8) && (lz_y >=0) && ( lz_y <= 9))
			{
				list_posi.add(*(new posi(lz_x, lz_y, type)));
			};
		};
		return list_posi;
	};
};
