#include "./piece.h"
#include "./square.h"

using namespace Board;

Square::Square(int position) : position_(position) {
	piece_ = nullptr;
	body_ = "This is where the sfml object will go.";	
}

Square::~Square() {
	delete piece_;
	piece_ = nullptr;
}
