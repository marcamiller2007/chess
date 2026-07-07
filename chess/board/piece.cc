#include <assert.h>

#include "./piece.h"
#include "./square.h"

using namespace Chess::Board;

const std::string Piece::kPieceTextures[12] = {
	"./chess/chess_models/Chess_plt60.png",
	"./chess/chess_models/Chess_pdt60.png",
	"./chess/chess_models/Chess_blt60.png",
	"./chess/chess_models/Chess_bdt60.png",
	"./chess/chess_models/Chess_nlt60.png",
	"./chess/chess_models/Chess_ndt60.png",
	"./chess/chess_models/Chess_rlt60.png",
	"./chess/chess_models/Chess_rdt60.png",
	"./chess/chess_models/Chess_qlt60.png",
	"./chess/chess_models/Chess_qdt60.png",
	"./chess/chess_models/Chess_klt60.png",
	"./chess/chess_models/Chess_kdt60.png"
};

Piece::Piece(PieceType piece_type, Square *initial_square, bool is_black) : type_(piece_type), is_black_(is_black) {
	kills_ = 0;
	position_ = nullptr;

	texture_ = new sf::Texture((std::filesystem::path) kPieceTextures[(int) type_ * 2 + (int) is_black_]);

	body_ = new sf::Sprite(*texture_);
	body_->setOrigin(body_->getGlobalBounds().getCenter());
	
	if (is_black_) {
		body_->setColor(sf::Color(255, 255, 255));
	}
	
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

	delete texture_;
	texture_ = nullptr;
}
