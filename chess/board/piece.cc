#include "./piece.h"

using namespace Board;

Piece::Piece(PieceType piece_type) : type_(piece_type) {
	name_ = "This is the name of the piece";
	position_ = nullptr;
	kills_ = 0;
}

Piece::~Piece() {
	delete position_;
	position_ = nullptr;	
}
