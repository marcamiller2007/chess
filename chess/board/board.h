#include <string>
#include <vector>

#include "./piece.h"
#include "./square.h"

#ifndef BOARD_H
#define BOARD_H

namespace Board {

class Board {
public:
	Board();
	~Board();
	void Load();
	int Load(std::string);
private:
	Square **board_;
	std::vector<Piece> pieces_;
};
}

#endif
