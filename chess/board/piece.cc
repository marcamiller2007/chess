#include <assert.h>

#include "./piece.h"
#include "./square.h"

using namespace Chess::Board;

Piece::Piece(PieceType piece_type, Square *initial_square, sf::Color color) : type_(piece_type) {
	kills_ = 0;
	position_ = nullptr;

	// Set body shape based on Piece type
	switch (type_) {
		case PieceType::kPawn:
			body_ = new sf::RectangleShape(sf::Vector2f(20, 20));
			body_->setOrigin(sf::Vector2f(0.5 * body_->getSize().x, 0.5 * body_->getSize().y));
			break;
		case PieceType::kKnight:
			body_ = new sf::RectangleShape(sf::Vector2f(20, 40));
			body_->setOrigin(sf::Vector2f(0.5 * body_->getSize().x, 0.5 * body_->getSize().y));
			break;
		case PieceType::kBishop:
			body_ = new sf::RectangleShape(sf::Vector2f(30, 30));
			body_->setOrigin(sf::Vector2f(0.5 * body_->getSize().x, 0.5 * body_->getSize().y));
			body_->setRotation(sf::Angle(sf::degrees(45)));
			break;
		case PieceType::kRook:
			body_ = new sf::RectangleShape(sf::Vector2f(30, 30));
			body_->setOrigin(sf::Vector2f(0.5 * body_->getSize().x, 0.5 * body_->getSize().y));
			break;
		case PieceType::kQueen:
			body_ = new sf::RectangleShape(sf::Vector2f(45, 45));
			body_->setOrigin(sf::Vector2f(0.5 * body_->getSize().x, 0.5 * body_->getSize().y));
			body_->setRotation(sf::Angle(sf::degrees(45)));
			break;
		case PieceType::kKing:
			body_ = new sf::RectangleShape(sf::Vector2f(40, 20));
			body_->setOrigin(sf::Vector2f(0.5 * body_->getSize().x, 0.5 * body_->getSize().y));
			break;
		default:
			assert(false);
	}

	// Set color
	if (color.toInteger() == sf::Color::White.toInteger()) {
		body_->setOutlineColor(sf::Color::Black);
	} else if (color.toInteger() == sf::Color::Black.toInteger()) {
		body_->setOutlineColor(sf::Color::White);
	}

	body_->setFillColor(color);
	body_->setOutlineThickness(1);

	MoveTo(initial_square);
}

/**
 * This function "moves" a piece to a new square, cleans up after itself by setting the piece pointer
 * of the square to null after it moves to the new one. If a piece already exists at the new location,
 * it will be deleted. No capture logic. Will also set position of the piece.
 */

void Piece::MoveTo(Square *to_square) {
	assert(to_square != nullptr);

	if (position_ != nullptr) {
		position_->SetPiece(nullptr);
	}

	position_ = to_square;
	to_square->SetPiece(this);

	// set position of body_
	body_->setPosition(to_square->GetCenter());
	return;
}

/**
 * This method draws the body of this piece onto the window.
 */

void Piece::Draw(sf::RenderWindow *window) {
	window->draw(*body_);
}

Piece::~Piece() {
	//delete position_;
	//position_ = nullptr;

	delete body_;
	body_ = nullptr;
}
