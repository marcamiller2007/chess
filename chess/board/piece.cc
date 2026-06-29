#include <assert.h>

#include "./piece.h"
#include "./square.h"

using namespace Chess::Board;

Piece::Piece(PieceType piece_type, Square *initial_square) : type_(piece_type) {
	kills_ = 0;
	position_ = nullptr;

	// Set body shape based on Piece type
	switch (type_) {
		case PieceType::kPawn:
			body_ = new sf::RectangleShape(sf::Vector2f(20, 20));
			break;
		case PieceType::kKnight:
			body_ = new sf::RectangleShape(sf::Vector2f(20, 40));
			break;
		case PieceType::kBishop:
			body_ = new sf::RectangleShape(sf::Vector2f(30, 30));
			body_->setRotation(sf::Angle(sf::radians(45)));
			break;
		case PieceType::kRook:
			body_ = new sf::RectangleShape(sf::Vector2f(30, 30));
			break;
		case PieceType::kQueen:
			body_ = new sf::RectangleShape(sf::Vector2f(45, 45));
			body_->setRotation(sf::Angle(sf::radians(45)));
			break;
		case PieceType::kKing:
			body_ = new sf::RectangleShape(sf::Vector2f(40, 20));
			break;
		default:
			assert(false);
	}

	MoveTo(initial_square);
}

/**
 * This function "moves" a piece to a new square, cleans up after itself by setting the piece pointer
 * of the square to null after it moves to the new one. If a piece already exists at the new location,
 * it will be deleted. No capture logic.
 */
void Piece::MoveTo(Square *to_square) {
	assert(to_square != nullptr);

	if (position_ != nullptr) {
		position_->SetPiece(nullptr);
	}

	position_ = to_square;
	to_square->SetPiece(this);
	return;
}

Piece::~Piece() {
	delete position_;
	position_ = nullptr;

	delete body_;
	body_ = nullptr;
}
