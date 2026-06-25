#ifndef PIECE_H
#define PIECE_H

#include <string>

class Square;

namespace Board {

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
	Piece(PieceType);
	~Piece();
private:
	std::string name_;
	PieceType type_;
	Square *position_;
	int kills_;
};
}
#endif
