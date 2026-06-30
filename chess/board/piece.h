#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

namespace Chess::Board {

class Square;

enum class PieceType : int {
	kPawn = 0,
	kKnight = 1,
	kBishop = 2,
	kRook = 3,
	kQueen = 4,
	kKing = 5
};

class Piece {
public:
	Piece(PieceType, Square*, sf::Color);
	~Piece();
	void MoveTo(Square*);
	void Draw(sf::RenderWindow*);
private:
	sf::RectangleShape *body_;
	PieceType type_;
	Square *position_;
	int kills_;
};
}
#endif
