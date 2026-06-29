//#include <iostream>

#include <SFML/Graphics.hpp>

#include "./chess/screen.h"

using namespace Chess;

int main() {
	Screen *game = new Screen();

	game->Start();

	delete game;

	return 0;
}
