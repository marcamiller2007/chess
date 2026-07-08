#ifndef RULESET_H
#define RULESET_H

#include "../board/board.h"

namespace Chess::Ruleset {

class Ruleset {
public:
	Ruleset(Board::PieceType, Board::Square*, bool);
	~Ruleset();
	void ChangeType(Board::PieceType);
	void CreateRuleset(Board::Square*);
	void DisplayMoves();
private:
	void ForPawn();
	void ForKnight();
	void ForBishop();
	void ForRook();
	void ForQueen();
	void ForKing();
	Board::Square *current_square_;
	std::vector<Board::Square*> *possible_moves_;
	Board::PieceType piece_type_;
	bool is_black_;
};

}

#endif
