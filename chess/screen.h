#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

#include "./board/board.h"

namespace Chess {

class Screen {
public:
	Screen();
	void Start();
	~Screen();
private:
	sf::RenderWindow window_;
	Board::Board state_;
};
}
#endif
