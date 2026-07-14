#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

namespace Chess {

namespace Ruleset {

class Ruleset;

}

namespace Board {

class Square;

enum class PieceType : int {
	kPawn = 0,
	kKnight = 1,
	kBishop = 2,
	kRook = 3,
	kQueen = 4,
	kKing = 5
};

class Piece {
public:
	Piece(PieceType, Square*, bool);
	~Piece();
	
	void MoveTo(Square*);
	void Draw(sf::RenderWindow*);
	void HandleClick();
	bool CanMoveTo(Square*);

	static const std::string kPieceTextures[12];
	const bool kIsBlack;
	bool has_moved_;
private:
	bool IsCastle(Square*);

	sf::Sprite *body_;
	sf::Texture *texture_;
	PieceType type_;
	Square *position_;
	Chess::Ruleset::Ruleset *ruleset_;
	int kills_;
};

}
}
#endif
