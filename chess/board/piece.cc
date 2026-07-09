#include <assert.h>

#include "./piece.h"
#include "./square.h"
#include "../ruleset/ruleset.h"

using namespace Chess::Board;

const std::string Piece::kPieceTextures[12] = {
	"./chess/chess_models/Chess_plt60.png",
	"./chess/chess_models/Chess_pdt60.png",
	"./chess/chess_models/Chess_nlt60.png",
	"./chess/chess_models/Chess_ndt60.png",
	"./chess/chess_models/Chess_blt60.png",
	"./chess/chess_models/Chess_bdt60.png",
	"./chess/chess_models/Chess_rlt60.png",
	"./chess/chess_models/Chess_rdt60.png",
	"./chess/chess_models/Chess_qlt60.png",
	"./chess/chess_models/Chess_qdt60.png",
	"./chess/chess_models/Chess_klt60.png",
	"./chess/chess_models/Chess_kdt60.png"
};

Piece::Piece(PieceType piece_type, Square *initial_square, bool is_black) : kIsBlack(is_black), type_(piece_type) {
	kills_ = 0;
	position_ = nullptr;

	texture_ = new sf::Texture((std::filesystem::path) kPieceTextures[(int) type_ * 2 + (int) kIsBlack]);

	body_ = new sf::Sprite(*texture_);
	body_->setOrigin(body_->getGlobalBounds().getCenter());
	
	if (kIsBlack) {
		body_->setColor(sf::Color(255, 255, 255));
	}
	
	MoveTo(initial_square);

	assert(position_ != nullptr);
	ruleset_ = new Chess::Ruleset::Ruleset(type_, position_, kIsBlack);
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
 * This function will handle all necessary Piece-level events when this piece is selected for a move.
 */

void Piece::HandleClick() {
	// Updates ruleset
	ruleset_->CreateRuleset(position_);
	ruleset_->DisplayMoves();
}

/**
 * This method will check if a given square is a valid move.
 */

bool Piece::CanMoveTo(Square *square) {
	return ruleset_->IsPossible(square);
}

/**
 * This method draws the body of this piece onto the window.
 */

void Piece::Draw(sf::RenderWindow *window) {
	window->draw(*body_);
}

Piece::~Piece() {
	delete body_;
	body_ = nullptr;

	delete texture_;
	texture_ = nullptr;
}
