#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>

namespace Chess::Board {
	
class Piece;

class Square {
public:
	Square(sf::Color, sf::Vector2f);
	~Square();
	void Draw(sf::RenderWindow*);
	void SetPiece(Piece*);
	sf::Vector2f GetCenter();
	const static int kSquareWidth = 80;
private:
	Piece *piece_;
	sf::RectangleShape *body_;
};
}
#endif
