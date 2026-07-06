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
	Piece(PieceType, Square*, bool);
	~Piece();
	void MoveTo(Square*);
	void Draw(sf::RenderWindow*);
	static const sf::Texture kPieceTextures[12];
private:
	sf::Sprite *body_;
	PieceType type_;
	bool is_black_;
	Square *position_;
	int kills_;
};
}
#endif
