#include <SFML/Graphics.hpp>

#include "./screen.h"

using namespace Chess;

Screen::Screen() {
	state_ = new Board::Board();

	window_ = nullptr;
}

void Screen::Start() {
	window_ = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(kWindowSize, kWindowSize)), "Chess");

	while (window_->isOpen()) {
		while(const std::optional event = window_->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window_->close();
			}
		}
	}
}

Screen::~Screen() {
	delete state_;

	if (window_ != nullptr) {
		delete window_;
	}
}
