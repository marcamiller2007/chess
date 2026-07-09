#include "./ruleset.h"

using namespace Chess::Ruleset;

Ruleset::Ruleset(Board::PieceType piece_type, Board::Square *current_square,
								 bool is_black): current_square_(current_square),
								 piece_type_(piece_type), is_black_(is_black) {
	possible_moves_ = new std::vector<Board::Square*>();

	CreateRuleset(current_square_);
}

/**
 * This method only exists because of pawn promotion.
 */

void Ruleset::ChangeType(Board::PieceType new_type) {
	piece_type_ = new_type;
}

/**
 * This method will create or edit a ruleset based on the given Board Square.
 */

void Ruleset::CreateRuleset(Board::Square *square) {
	possible_moves_->clear();

	if (current_square_ != square) {
		current_square_ = square;
	}

	switch (piece_type_) {
		case Board::PieceType::kPawn:
			ForPawn();
			break;
		case Board::PieceType::kKnight:
			ForKnight();
			break;
		case Board::PieceType::kBishop:
			ForBishop();
			break;
		case Board::PieceType::kRook:
			ForRook();
			break;
		case Board::PieceType::kQueen:
			ForQueen();
			break;
		case Board::PieceType::kKing:
			ForKing();
			break;
		default:
			assert(false);
	}
}

void Ruleset::DisplayMoves() {
	for (int i = 0; i < possible_moves_->size(); i++) {
		possible_moves_->at(i)->Select();
	}
}

/**
 * These are the methods that will add legal moves for each piece to the possible_moves_
 * vector, each returns void.
 */

void Ruleset::ForPawn() {
	sf::Vector2i initial_position = current_square_->GetLocation();

	// can move 1 or 2 squares forward
	for (int i = 1; i <= 2; i++) {
		Board::Square *square;

		if (is_black_) {
			square = current_square_->FindNeighbor({initial_position.x + i, initial_position.y});
		} else {
			square = current_square_->FindNeighbor({initial_position.x - i, initial_position.y});
		}

		if (square != nullptr) {
			possible_moves_->push_back(square);
		}
	}
}

void Ruleset::ForKnight() {
	sf::Vector2i initial_position = current_square_->GetLocation();

	Board::Square *square_to_add;

	square_to_add = (current_square_->FindNeighbor({initial_position.x + 1, initial_position.y + 2}));

	if (square_to_add != nullptr) {
		possible_moves_->push_back(square_to_add);
	}

	square_to_add = (current_square_->FindNeighbor({initial_position.x + 1, initial_position.y - 2}));

	if (square_to_add != nullptr) {
		possible_moves_->push_back(square_to_add);
	}

	square_to_add = (current_square_->FindNeighbor({initial_position.x - 1, initial_position.y + 2}));

	if (square_to_add != nullptr) {
		possible_moves_->push_back(square_to_add);
	}

	square_to_add = (current_square_->FindNeighbor({initial_position.x - 1, initial_position.y - 2}));

	if (square_to_add != nullptr) {
		possible_moves_->push_back(square_to_add);
	}

	square_to_add = (current_square_->FindNeighbor({initial_position.x + 2, initial_position.y + 1}));

	if (square_to_add != nullptr) {
		possible_moves_->push_back(square_to_add);
	}

	square_to_add = (current_square_->FindNeighbor({initial_position.x + 2, initial_position.y - 1}));

	if (square_to_add != nullptr) {
		possible_moves_->push_back(square_to_add);
	}

	square_to_add = (current_square_->FindNeighbor({initial_position.x - 2, initial_position.y + 1}));

	if (square_to_add != nullptr) {
		possible_moves_->push_back(square_to_add);
	}

	square_to_add = (current_square_->FindNeighbor({initial_position.x - 2, initial_position.y - 1}));

	if (square_to_add != nullptr) {
		possible_moves_->push_back(square_to_add);
	}
}

void Ruleset::ForBishop() {
	sf::Vector2i initial_position = current_square_->GetLocation();

	for (int i = 1; i < 8; i++) {
		Board::Square *square_to_add = current_square_->FindNeighbor(
			{initial_position.x + i, initial_position.y + i}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}

		square_to_add = current_square_->FindNeighbor(
			{initial_position.x - i, initial_position.y - i}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}
	}

	for (int i = 1; i < 8; i++) {
		Board::Square *square_to_add = current_square_->FindNeighbor(
			{initial_position.x + i, initial_position.y - i}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}

		square_to_add = current_square_->FindNeighbor(
			{initial_position.x - i, initial_position.y + i}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}
	}
}
void Ruleset::ForRook() {
	sf::Vector2i initial_position = current_square_->GetLocation();

	for (int i = 1; i < 8; i++) {
		Board::Square *square_to_add = current_square_->FindNeighbor(
			{initial_position.x, initial_position.y + i}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}

		square_to_add = current_square_->FindNeighbor(
			{initial_position.x, initial_position.y - i}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}
	}

	for (int i = 1; i < 8; i++) {
		Board::Square *square_to_add = current_square_->FindNeighbor(
			{initial_position.x + i, initial_position.y}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}

		square_to_add = current_square_->FindNeighbor(
			{initial_position.x - i, initial_position.y}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}
	}
}
void Ruleset::ForQueen() {
	ForBishop();
	ForRook();
}
void Ruleset::ForKing() {
	sf::Vector2i initial_position = current_square_->GetLocation();

	for (int i = 0; i < 4; i++) {
		Board::Square *square_to_add;
		sf::Vector2i direction = {(i < 2 ? i : 1), (i == 0 ? (- 1) : (i - 2))};

		square_to_add = current_square_->FindNeighbor(
			{initial_position.x + direction.x, initial_position.y + direction.y}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}
		
		square_to_add = current_square_->FindNeighbor(
			{initial_position.x - direction.x, initial_position.y - direction.y}
		);

		if (square_to_add != nullptr) {
			possible_moves_->push_back(square_to_add);
		}
	}
}

Ruleset::~Ruleset() {
	delete possible_moves_;
}
