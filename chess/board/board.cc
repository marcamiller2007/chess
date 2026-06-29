#include <iostream>

#include "./board.h"

using namespace Chess::Board;

Board::Board(){
	board_ = nullptr;
	pieces_ = new std::vector<Piece>();

	std::cout << "Board init";
}

void Board::Load() {
	std::cout << "TODO";
}

int Board::Load(std::string str) {
	return 0;
}

Board::~Board() {
	delete pieces_;
	std::cout << "Board destruct";
}
