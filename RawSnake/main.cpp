#include "GameWindow.h"
#include "Game.h"

int main(int argc,char* argv[])
{
    GAMEWINDOW.setup(GAME_NAME, GAME_WIDTH, GAME_HEIGHT, GAME_BPP, GAME_FULLSCREEN);
    GAMEWINDOW.show(new Game);
	return 0;
}
