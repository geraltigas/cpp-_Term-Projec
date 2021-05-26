#include "ALL.h"
using namespace easy2d;
using std::cout;
using std::endl;
int main()
{
	if (Game::init())
	{
		Chinese_chess chess_game = Chinese_chess();
		chess_game.init();
		chess_game.begin();
		Game::start();
	}
	Game::destroy();
}



//int main(){};


 