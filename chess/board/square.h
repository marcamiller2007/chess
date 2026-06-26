#ifndef SQUARE_H
#define SQUARE_H

#include <string>

namespace Board {
	
class Piece;

class Square {
public:
	Square(int);
	~Square();
private:
	int position_;
	Piece *piece_;
	std::string body_;
};
}
#endif
