#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "./piece.h"
#include "./square.h"

namespace Chess::Board {

class Board {
public:
	Board();
	~Board();
	void Load();
	int Load(std::string);
	void Draw(sf::RenderWindow*);
	Square *FindSquare(sf::Vector2i);
	sf::Vector2i FindSquare(Square*);
	void HandleClick(sf::Vector2i);
private:
	Square ***board_;
	std::vector<Piece*> *active_pieces_;
	std::vector<Piece*> *graveyard_;
};
}
#endif
