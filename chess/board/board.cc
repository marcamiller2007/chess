#include <iostream>

#include "./board.h"

using namespace Chess::Board;

Board::Board(){
	board_ = nullptr;
	active_pieces_ = new std::vector<Piece*>();
	graveyard_ = new std::vector<Piece*>();
	selected_squares_ = new std::vector<Square*>();
	update_ = false;

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
				board_[i][j] = new Square(true, position, this);
			} else {
				board_[i][j] = new Square(false, position, this);
			}
		}
	}

	// init all Pieces
	// Pawns
	for (int i = 0; i < 8; i++) {
		Piece *w_pawn = new Piece(PieceType::kPawn, board_[6][i], false);
		Piece *b_pawn = new Piece(PieceType::kPawn, board_[1][i], true);
		
		active_pieces_->push_back(w_pawn);
		active_pieces_->push_back(b_pawn);
	}

	// Knights
	Piece *wk1 = new Piece(PieceType::kKnight, board_[7][1], false);
	Piece *wk2 = new Piece(PieceType::kKnight, board_[7][6], false);

	Piece *bk1 = new Piece(PieceType::kKnight, board_[0][1], true);
	Piece *bk2 = new Piece(PieceType::kKnight, board_[0][6], true);

	active_pieces_->push_back(wk1);
	active_pieces_->push_back(wk2);
	active_pieces_->push_back(bk1);
	active_pieces_->push_back(bk2);

	// Knights
	Piece *wb1 = new Piece(PieceType::kBishop, board_[7][2], false);
	Piece *wb2 = new Piece(PieceType::kBishop, board_[7][5], false);

	Piece *bb1 = new Piece(PieceType::kBishop, board_[0][2], true);
	Piece *bb2 = new Piece(PieceType::kBishop, board_[0][5], true);

	active_pieces_->push_back(wb1);
	active_pieces_->push_back(wb2);
	active_pieces_->push_back(bb1);
	active_pieces_->push_back(bb2);

	// Rooks
	Piece *wr1 = new Piece(PieceType::kRook, board_[7][0], false);
	Piece *wr2 = new Piece(PieceType::kRook, board_[7][7], false);

	Piece *br1 = new Piece(PieceType::kRook, board_[0][0], true);
	Piece *br2 = new Piece(PieceType::kRook, board_[0][7], true);

	active_pieces_->push_back(wr1);
	active_pieces_->push_back(wr2);
	active_pieces_->push_back(br1);
	active_pieces_->push_back(br2);

	// kings	
	Piece *wk = new Piece(PieceType::kKing, board_[7][3], false);
	Piece *bk = new Piece(PieceType::kKing, board_[0][4], true);

	active_pieces_->push_back(wk);
	active_pieces_->push_back(bk);

	// queens	
	Piece *wq = new Piece(PieceType::kQueen, board_[7][4], false);
	Piece *bq = new Piece(PieceType::kQueen, board_[0][3], true);

	active_pieces_->push_back(wq);
	active_pieces_->push_back(bq);

	update_ = true;
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

/**
 * This function will return the Square corresponding to the vector form coordinates given.
 * NOTE: x corresponds to row, and y to column.
 */

Square *Board::FindSquare(sf::Vector2i coords) {
	if ((coords.x < 0) || (coords.x >= 8) ||
			(coords.y < 0) || (coords.y >= 8)) {
		return nullptr;// out of bounds
	}

	return board_[coords.x][coords.y];
}

/**
 * This function will return the vector form coordinates corresponding to the given Square.
 */

sf::Vector2i Board::FindSquare(Square *square) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board_[i][j] == square) {
				return {i, j};
			}
		}
	}

	return {-1, -1}; // Something is desperately wrong if this returns
}

/**
 * THis method will handle all functionality associated with the given click coordinates.
 * Will also pass the click to Squares and pieces.
 */

void Board::HandleClick(sf::Vector2i click) {
	// First: Clear the board of all selections
	while (!selected_squares_->empty()) {
		selected_squares_->back()->Unselect();
		selected_squares_->pop_back();
	}
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//std::cout << "Checking Square " << i << ", " << j << "\n";
			if (board_[i][j]->HandleClick(click)) {
				std::cout << "Click at Square " << i << ", " << j << "\n";
				
				update_ = true;
				// the click applies to this square
				
				return;
			}
		}
	}
}

bool Board::ShouldUpdate() {
	return update_;
}

void Board::SetUpdateFalse() {
	update_ = false;
}

/**
 * This method will push a selected Square (given) onto the selected squares vector
 */

void Board::PushSelected(Square *square) {
	selected_squares_->push_back(square);
}

/* Destructor */

Board::~Board() {
	delete graveyard_;
	delete board_;
	delete active_pieces_;
	delete selected_squares_;
	std::cout << "Board destruct\n";
}
