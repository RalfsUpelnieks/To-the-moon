#include "Include.h"
#include "Game.h"

int main() {
	srand(static_cast<unsigned>(time(0)));

	Game game;

	while (game.running())
	{
		game.Events();
		game.render();
		game.update();
	}

    //End of application
    return 0;
}