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

	// Knights
	Piece *wk1 = new Piece(PieceType::kKnight, board_[7][1], sf::Color::White);
	Piece *wk2 = new Piece(PieceType::kKnight, board_[7][6], sf::Color::White);

	Piece *bk1 = new Piece(PieceType::kKnight, board_[0][1], sf::Color::Black);
	Piece *bk2 = new Piece(PieceType::kKnight, board_[0][6], sf::Color::Black);

	active_pieces_->push_back(wk1);
	active_pieces_->push_back(wk2);
	active_pieces_->push_back(bk1);
	active_pieces_->push_back(bk2);

	// Knights
	Piece *wb1 = new Piece(PieceType::kBishop, board_[7][2], sf::Color::White);
	Piece *wb2 = new Piece(PieceType::kBishop, board_[7][5], sf::Color::White);

	Piece *bb1 = new Piece(PieceType::kBishop, board_[0][2], sf::Color::Black);
	Piece *bb2 = new Piece(PieceType::kBishop, board_[0][5], sf::Color::Black);

	active_pieces_->push_back(wb1);
	active_pieces_->push_back(wb2);
	active_pieces_->push_back(bb1);
	active_pieces_->push_back(bb2);

	// Rooks
	Piece *wr1 = new Piece(PieceType::kRook, board_[7][0], sf::Color::White);
	Piece *wr2 = new Piece(PieceType::kRook, board_[7][7], sf::Color::White);

	Piece *br1 = new Piece(PieceType::kRook, board_[0][0], sf::Color::Black);
	Piece *br2 = new Piece(PieceType::kRook, board_[0][7], sf::Color::Black);

	active_pieces_->push_back(wr1);
	active_pieces_->push_back(wr2);
	active_pieces_->push_back(br1);
	active_pieces_->push_back(br2);

	// kings	
	Piece *wk = new Piece(PieceType::kKing, board_[7][3], sf::Color::White);
	Piece *bk = new Piece(PieceType::kKing, board_[0][4], sf::Color::Black);

	active_pieces_->push_back(wk);
	active_pieces_->push_back(bk);

	// queens	
	Piece *wq = new Piece(PieceType::kQueen, board_[7][4], sf::Color::White);
	Piece *bq = new Piece(PieceType::kQueen, board_[0][3], sf::Color::Black);

	active_pieces_->push_back(wq);
	active_pieces_->push_back(bq);
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
