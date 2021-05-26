#include "ALL.h"
using namespace easy2d;
using std::cout;
using std::endl;
Chinese_chess::Chinese_chess()
{
	scene_two = gcnew Scene();
	scene_three = gcnew Scene();
	map = new Map(scene_two,this);
	cout << "scene_two: " << (int)scene_two << endl;
	background = new Sprite(BACKGROUNDS);
	button_again = new Sprite(BUTTONAG);
	button_back = new Sprite(BUTTONBA);
	text = new Text();
	button_ag = new Button(button_again);
	button_ba = new Button(button_back);
};

void Chinese_chess::win_enter()
{
	auto scene_three = new Scene();
	auto background = new Sprite(BACKGROUNDS);
	auto button_again = new Sprite(BUTTONAG);
	auto button_back = new Sprite(BUTTONBA);
	auto text = new Text();
	auto button_ag = new Button(button_again);
	auto button_ba = new Button(button_back);
	Font font = Font();
	font.family = L"宋体";
	font.size = 80;
	font.weight = Font::Weight::Bold;
	background->setPos(0, 0);
	auto style = Text::Style();
	text->setFont(font);

	text->setPos(200, 140);
	auto call_bcak = [&]()
	{
		map->back_to_game();
	};
	auto call_back1 = [&]()
	{
		map->fupan();
	};
	button_ag->setClickFunc(call_bcak);
	button_ba->setClickFunc(call_back1);
	button_ag->setScale(0.4f);
	button_ag->setPos(263, 280);
	if (map->who_win == Camp::jiang)
	{
		text->setText(L"黑方");
		style.color = Color::Black;
	}
	else if (map->who_win == Camp::shuai)
	{
		text->setText(L"红方");
		style.color = Color::Red;
	}
	else
	{
		text->setText(L"测试");
	}
	text->setStyle(style);
	scene_three->addChild(background);
	scene_three->addChild(button_ag);
	scene_three->addChild(text);
	SceneManager::enter(scene_three);
}

void Chinese_chess::preload_source() const {

};

void Chinese_chess::init_window() const
{
	Window::setTitle(L"中国象棋-cpp_term_project");
	Window::setSize(700, 712);
	cout << "windows initialed successfully" << endl;
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
	init_scene_two();
	init_scene_three();
};

void Chinese_chess::begin()
{
	SceneManager::enter(scene_two);
};
