#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>

#include "./screen.h"

using namespace Chess;

Screen::Screen() {
	state_ = new Board::Board();

	window_ = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(kWindowSize, kWindowSize)), "Chess");
}

void Screen::GraphicsThread() {
	while (true) {		
		// Board Lock
		{
			std::lock_guard<std::mutex> board_guard(board_lock_);

			// Window Lock
			{
				std::lock_guard<std::mutex> window_guard(window_lock_);

				// Check if window is still open
				if (!window_->isOpen()){
					return;
				}
			}
		}
	}
}

void Screen::EventThread() {
	while (true) {
		// Board Logic
		{
			std::lock_guard<std::mutex> guard(board_lock_);

			// Do things here
		}

		// Poll for events
		{
			std::lock_guard<std::mutex> guard(window_lock_);
			
			while(const std::optional event = window_->pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window_->close();
					return;
				}
			}
		}
		
		std::cout << "LogicThread";
	}
}

void Screen::Start() {
	graphics_thread_ = std::thread(&Chess::Screen::GraphicsThread);
	event_thread_ = std::thread(&Chess::Screen::EventThread);

	// wait to complete
	graphics_thread_.join();
	event_thread_.join();
}

Screen::~Screen() {
	delete state_;

	if (window_ != nullptr) {
		delete window_;
	}
}
