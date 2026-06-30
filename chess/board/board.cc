#include <iostream>

#include "./board.h"

using namespace Chess::Board;

Board::Board(){
	board_ = nullptr;
	active_pieces_ = new std::vector<Piece*>();
	graveyard_ = new std::vector<Piece*>();

	std::cout << "Board init\n";
}

/**
 * This method will create the board, an 8x8, and create all Square objects
 * and all Piece objects (which will also be added to the board).
 */

void Board::Load() {
	std::cout << "creating Board\n";

	// Create 2D array first
	board_ = new Square**[8];

	for (int i = 0; i < 8; i++) {
		board_[i] = new Square*[8];
	}

	// init all squares
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			sf::Vector2f position(80 + (j * Square::kSquareWidth), 80 + (i * Square::kSquareWidth));
			if ((i + j) % 2 == 0) {
				board_[i][j] = new Square(sf::Color::Black, position);
			} else {
				board_[i][j] = new Square(sf::Color::White, position);
			}
		}
	}

	// init all Pieces
	// Pawns
	for (int i = 0; i < 8; i++) {
		Piece *w_pawn = new Piece(PieceType::kPawn, board_[6][i], sf::Color::White);
		Piece *b_pawn = new Piece(PieceType::kPawn, board_[1][i], sf::Color::Black);
		
		active_pieces_->push_back(w_pawn);
		active_pieces_->push_back(b_pawn);
	}

	// others
}

/**
 * Same operations as the overloaded method Load but this will load into a game
 * from a file
 */

int Board::Load(std::string file) {
	return 0;
}

/**
 * This method will take an sf::RenderWindow and will draw the board and all pieces on
 * squares, not all in graveyard.
 */

void Board::Draw(sf::RenderWindow *window) {
	// Draw all squares and pieces
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board_[i][j]->Draw(window);
		}
	}
}

Board::~Board() {
	delete graveyard_;
	std::cout << "Board destruct\n";
}
