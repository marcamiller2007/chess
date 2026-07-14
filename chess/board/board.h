#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

//#include "../ruleset/ruleset.h"

namespace Chess {

// Forward def
namespace Ruleset {

class Ruleset;

}

namespace Board {

// Forward def
class Piece;
class Square;

enum MoveType : int {
	kPositioning = 0,
	kCapture = 1,
	kCastle = 2,
};

struct Move {
	MoveType type_;
	Square *from_square_;
	Square *to_square_;
	Ruleset::Ruleset *ruleset_;
};

class Board {
public:
	Board();
	~Board();

	void Load();
	int Load(std::string);
	void Draw(sf::RenderWindow*);
	Square *FindSquare(sf::Vector2i);
	sf::Vector2i FindSquare(Square*);
	void HandleClick(sf::Vector2i);
	bool ShouldUpdate();
	void SetUpdateFalse();
	void PushSelected(Square*);
	bool TryMove(Move);

	bool white_turn_;
	bool player_is_black_;
	Piece *selected_piece_;
private:
	Square ***board_;
	std::vector<Piece*> *active_pieces_;
	std::vector<Piece*> *graveyard_;
	std::vector<Square*> *selected_squares_;
	bool update_;
};
} /* namespace Board */
} /* namespace Chess */

#endif
