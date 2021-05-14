#include <iostream>
#include <string>
using std::cout;
using std::endl;
#include <easy2d\easy2d.h>
using namespace easy2d;

int main()
{
	int okkk = 100;
	if (Game::init())
	{
		auto text_test = gcnew Text(L"this is the 1");
		auto sence1 = gcnew Scene();
		sence1->addChild(text_test);
		std::wstring str;
		std::wstring head = (L"this is the ");
		int cout = 1;
		auto callback = [text_test,&str,&cout,&head]()
		{
			str = std::to_wstring(cout);
			text_test->setText(head+str);
			cout++;
		};
		Timer::add(callback,1.0f);
		SceneManager::enter(sence1);
		Game::start();
	}
	cout << okkk << endl;
	Game::destroy();


}