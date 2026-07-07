#include <assert.h>

#include "./piece.h"
#include "./square.h"

using namespace Chess::Board;

Square::Square(bool is_black, sf::Vector2f position) {
	piece_ = nullptr;

	// Graphics for board piece
	body_ = new sf::RectangleShape(sf::Vector2f(kSquareWidth, kSquareWidth));
	body_->setPosition(position);

	if (is_black) {
		body_->setFillColor(sf::Color(100, 100, 100));
	}
	else {
		body_->setFillColor(sf::Color(200, 200, 200));
	}
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
