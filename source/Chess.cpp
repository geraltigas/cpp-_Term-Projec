#include "ALL.h"

Chess::Chess(
	Camp side,
	posi& positions,
	wchar_t* pics,
	Type types
) :
	camp(side),
	position(positions),
	pic(new easy2d::Sprite(pics)),
	easy2d::Button(),
	type(types),
	chess_is_selected(0),
	is_alive(1)
{
};

Chess::Chess(
	Camp side,
	unsigned int xx,
	unsigned int yy,
	Type types,
	wchar_t* pics
) :
	camp(side),
	position(xx, yy, types),
	pic(new easy2d::Sprite(pics)),
	easy2d::Button(pic),
	type(types),
	chess_is_selected(0),
	is_alive(1)
{
	setAnchor(0.5f, 0.5f);
	setNormal(pic);
	std::cout << position.xy_to_pixel().x << " " << position.xy_to_pixel().y << std::endl;
	setPos(position.xy_to_pixel().x, position.xy_to_pixel().y);
};
void Chess::set_map(Map* maps)
{
	map = maps;
};
