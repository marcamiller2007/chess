#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>

namespace Board {
	
class Piece;

class Square {
public:
	Square(sf::Color, sf::Vector2f);
	void SetPiece(Piece*);
	~Square();
	const int kSquareWidth = 80;
private:
	Piece *piece_;
	sf::RectangleShape *body_;
};
}
#endif
