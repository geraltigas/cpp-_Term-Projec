#pragma once
#include <easy2d/easy2d.h>
#include "Map.h"
using namespace easy2d;

class Chinese_chess
{
public:
	Scene* scene_one;
	Scene* scene_two;
	Scene* scene_three;
	Map* map;
	Chinese_chess();
	void preload_source() const;
	void init_window() const;
	void init_scene_one() const;
	void init_scene_two() const;
	void init_scene_three() const;
	void init() const;
	void begin();
};
