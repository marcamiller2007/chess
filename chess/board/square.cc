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

Square::~Square() {
	delete piece_;
	piece_ = nullptr;

	delete body_;
	body_ = nullptr;
}
