#include <iostream>
#include <random>

#include "./board.h"
#include "./square.h"
#include "./piece.h"

using namespace Chess::Board;

Board::Board(){
	board_ = nullptr;
	active_pieces_ = new std::vector<Piece*>();
	graveyard_ = new std::vector<Piece*>();
	selected_squares_ = new std::vector<Square*>();
	selected_piece_ = nullptr;
	update_ = false;
	white_turn_ = true;

	std::cout << "Board init\n";

	// pick what rows black and white will be
	std::random_device seed;

	std::mt19937 engine(seed());

	std::uniform_int_distribution<int> distribution(0, 99);

	int num = distribution(engine);

	std::cout << num << "\n";

	player_is_black_ = num % 2 == 0;

	// if player is black then the bottom row will be black.
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
			if ((i + j) % 2 == 1) {
				board_[i][j] = new Square(true, position, this);
			} else {
				board_[i][j] = new Square(false, position, this);
			}
		}
	}

	// rows for piece assignment

	int bpawns = player_is_black_ ? 6 : 1;
	int bpieces = player_is_black_ ? 7 : 0;

	int wpawns = 7 - bpawns;
	int wpieces = 7 - bpieces;

	// init all Pieces
	// Pawns
	for (int i = 0; i < 8; i++) {
		Piece *w_pawn = new Piece(PieceType::kPawn, board_[wpawns][i], false);
		Piece *b_pawn = new Piece(PieceType::kPawn, board_[bpawns][i], true);
		
		active_pieces_->push_back(w_pawn);
		active_pieces_->push_back(b_pawn);
	}

	// Knights
	Piece *wk1 = new Piece(PieceType::kKnight, board_[wpieces][1], false);
	Piece *wk2 = new Piece(PieceType::kKnight, board_[wpieces][6], false);

	Piece *bk1 = new Piece(PieceType::kKnight, board_[bpieces][1], true);
	Piece *bk2 = new Piece(PieceType::kKnight, board_[bpieces][6], true);

	active_pieces_->push_back(wk1);
	active_pieces_->push_back(wk2);
	active_pieces_->push_back(bk1);
	active_pieces_->push_back(bk2);

	// Knights
	Piece *wb1 = new Piece(PieceType::kBishop, board_[wpieces][2], false);
	Piece *wb2 = new Piece(PieceType::kBishop, board_[wpieces][5], false);

	Piece *bb1 = new Piece(PieceType::kBishop, board_[bpieces][2], true);
	Piece *bb2 = new Piece(PieceType::kBishop, board_[bpieces][5], true);

	active_pieces_->push_back(wb1);
	active_pieces_->push_back(wb2);
	active_pieces_->push_back(bb1);
	active_pieces_->push_back(bb2);

	// Rooks
	Piece *wr1 = new Piece(PieceType::kRook, board_[wpieces][0], false);
	Piece *wr2 = new Piece(PieceType::kRook, board_[wpieces][7], false);

	Piece *br1 = new Piece(PieceType::kRook, board_[bpieces][0], true);
	Piece *br2 = new Piece(PieceType::kRook, board_[bpieces][7], true);

	active_pieces_->push_back(wr1);
	active_pieces_->push_back(wr2);
	active_pieces_->push_back(br1);
	active_pieces_->push_back(br2);

	int queen_column = (board_[bpieces][3]->square_is_black_) ? 3 : 4;
	int king_column = 7 - queen_column;

	// kings	
	Piece *wk = new Piece(PieceType::kKing, board_[wpieces][king_column], false);
	Piece *bk = new Piece(PieceType::kKing, board_[bpieces][king_column], true);

	active_pieces_->push_back(wk);
	active_pieces_->push_back(bk);

	// queens	
	Piece *wq = new Piece(PieceType::kQueen, board_[wpieces][queen_column], false);
	Piece *bq = new Piece(PieceType::kQueen, board_[bpieces][queen_column], true);

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

				// A move is initiated
				if ((selected_piece_ != nullptr) && (selected_piece_->CanMoveTo(board_[i][j]))) {
					selected_piece_->MoveTo(board_[i][j]);

					// Alternate turn
					white_turn_ = !white_turn_;
				
					// Deselect Piece
					selected_piece_ = nullptr;
				} else {
					selected_piece_ = board_[i][j]->GetPiece(); // MAY BE NULLPTR


					update_ = true;
				}
				
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

/**
 * This method will handle a move and decide if it is a legal move (returns true) or
 * an illegal one (returns false). This will evaluate checks, and all move types.
 * Takes a Move struct as an argument.
 */

bool Board::TryMove(Move move) {
	return true;	
}

/* Destructor */

Board::~Board() {
	delete graveyard_;
	delete board_;
	delete active_pieces_;
	delete selected_squares_;
	std::cout << "Board destruct\n";
}
