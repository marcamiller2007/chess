#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>

namespace Chess::Board {

class Board;
class Piece;

class Square {
public:
	Square(bool, sf::Vector2f, Board*);
	~Square();

	void Draw(sf::RenderWindow*);
	void SetPiece(Piece*);
	Piece *GetPiece();
	sf::Vector2f GetCenter();
	bool IsPiece();
	void Select();
	void Unselect();
	sf::Vector2i GetLocation();
	Square *FindNeighbor(sf::Vector2i);
	bool HandleClick(sf::Vector2i);
	bool PlayerIsBlack();

	const static int kSquareWidth = 80;
	const static sf::Color kWhite;
	const static sf::Color kBlack;
	const static sf::Color kSelected;
private:
	Piece *piece_;
	sf::RectangleShape *body_;
	sf::CircleShape *highlight_;
	Board *global_state_;
	bool selected_;
	bool is_black_;
};
}
#endif
