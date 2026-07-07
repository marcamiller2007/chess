#include <assert.h>

#include "./piece.h"
#include "./square.h"

using namespace Chess::Board;

const sf::Color Square::kBlack(100, 100, 100);
const sf::Color Square::kWhite(200, 200, 200);
const sf::Color Square::kSelected(255, 127, 0);

Square::Square(bool is_black, sf::Vector2f position) : is_black_(is_black) {
	piece_ = nullptr;

	// Graphics for board piece
	body_ = new sf::RectangleShape(sf::Vector2f(kSquareWidth, kSquareWidth));
	body_->setPosition(position);
	body_->setFillColor(is_black_ ? kBlack : kWhite);
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

/**
 * This method will "highlight" this Square. Will change the fill Color of this
 * Square so a possible move will be visible.
 */

void Square::Select() {
	body_->setFillColor(kSelected);
}

/**
 * This method will do the functional opposite of the above method. It will revert
 * the fill color of this Square.
 */

void Square::Unselect() {
	body_->setFillColor(is_black_ ? kBlack : kWhite);
}

Square::~Square() {
	if (piece_ != nullptr) {
		delete piece_;
		piece_ = nullptr;
	}

	delete body_;
	body_ = nullptr;
}
