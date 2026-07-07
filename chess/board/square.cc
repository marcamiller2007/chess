#include <assert.h>

#include "./piece.h"
#include "./square.h"

using namespace Chess::Board;

Square::Square(sf::Color color, sf::Vector2f position) {
	bool is_black_or_white = (color.toInteger() == sf::Color::Black.toInteger())
		|| (color.toInteger() == sf::Color::White.toInteger());
	assert(is_black_or_white);

	piece_ = nullptr;

	// Graphics for board piece
	body_ = new sf::RectangleShape(sf::Vector2f(kSquareWidth, kSquareWidth));
	body_->setFillColor(color);
	body_->setPosition(position);
}

/**
 * This method will set the piece object which currently resides on this Square.
 * Overwrites the old piece. Sets new piece's position.
 */

void Square::SetPiece(Piece *new_piece) {
	piece_ = new_piece;
}

/**
 * This method will return true iff there is currently a piece at this Square.
 */

bool Square::IsPiece() {
	return !(piece_ == nullptr);
}

/**
 * This method will draw the square and the piece which resides on it, in
 * that order!
 */

void Square::Draw(sf::RenderWindow *window) {
	window->draw(*body_);

	if (piece_ != nullptr) {
		piece_->Draw(window);
	}
}

/**
 * This method will find and return the center of this Square in vector form.
 */

sf::Vector2f Square::GetCenter() {
	sf::Vector2f top_left = body_->getPosition();

	return sf::Vector2f(top_left.x + (kSquareWidth / 2.f), top_left.y + (kSquareWidth / 2.f));
}

Square::~Square() {
	if (piece_ != nullptr) {
		delete piece_;
		piece_ = nullptr;
	}

	delete body_;
	body_ = nullptr;
}
