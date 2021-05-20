#include "ALL.h"
using namespace easy2d;
using std::cout;
using std::endl;
Chinese_chess::Chinese_chess()
{
	scene_one = gcnew Scene();
	scene_two = gcnew Scene();
	scene_three = gcnew Scene();
	map = new Map(scene_two);
	cout << "scene_two: " << (int)scene_two << endl;
};

void Chinese_chess::preload_source() const {

};

void Chinese_chess::init_window() const
{
	Window::setTitle(L"ÖÐ¹úÏóÆå-cpp_term_project");
	Window::setSize(700, 712);
	cout << "windows initialed successfully" << endl;
};

void Chinese_chess::init_scene_one() const
{
	//background
	//button for begin
};

void Chinese_chess::init_scene_two() const
{
	auto background = new Sprite(BACKGROUND);
	map->host_scene->addChild(background);
	map->init();
};

void Chinese_chess::init_scene_three() const
{

};

void Chinese_chess::init() const
{
	preload_source();
	cout << "enter the windows init " << endl;
	init_window();
	init_scene_one();
	init_scene_two();
	init_scene_three();
};

void Chinese_chess::begin()
{
	SceneManager::enter(scene_two);
};
