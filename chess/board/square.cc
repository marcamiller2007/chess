#include <assert.h>

#include "./piece.h"
#include "./square.h"

using namespace Board;

Square::Square(sf::Color color, sf::Vector2f position) {
	bool is_black_or_white = (color.toInteger() == sf::Color::Black.toInteger())
		|| (color.toInteger() == sf::Color::White.toInteger());
	assert(is_black_or_white);

	piece_ = nullptr;

	// Graphics for board piece
	body_ = new sf::RectangleShape(sf::Vector2f(kSquareWidth, kSquareWidth));
	body_->setFillColor(color);
}

void Square::SetPiece(Piece *new_piece) {
	if (piece_ != nullptr) {
		// for now we will simply delete a piece that is captured
		delete piece_;
	}

	piece_ = new_piece;
}

Square::~Square() {
	if (piece_ != nullptr) {
		delete piece_;
		piece_ = nullptr;
	}

	delete body_;
	body_ = nullptr;
}
