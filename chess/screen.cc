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
	std::cout << "Starting graphics thread\n";

	sf::Color brown(88, 57, 39);

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

				// Clear, Redraw, Display
				window_->clear(brown);

				state_->Draw(window_);

				window_->display();
			}
		}
	}
}

void Screen::EventThread() {
	std::cout << "Starting event thread\n";

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

				// Poll for a user click
				if (event->is<sf::Event::MouseButtonPressed>()) {
					sf::Vector2i mouse_coords = sf::Mouse::getPosition(*window_);
					std::cout << "X: " << mouse_coords.x << "Y:" << mouse_coords.y << "\n";

					// Check it was in the window's area
					if ((mouse_coords.x >= 0) && (mouse_coords.x <= 800) &&
							(mouse_coords.y >= 0) && (mouse_coords.y <= 800)) {
						// send click to the board
						state_->HandleClick(mouse_coords);
					}
				}
			}
		}		
	}
}

void Screen::Start() {
	// load the board
	state_->Load();

	// launch threads
	graphics_thread_ = std::thread(&Chess::Screen::GraphicsThread, this);

	EventThread();

	// wait to complete
	graphics_thread_.join();
}

Screen::~Screen() {
	delete state_;

	if (window_ != nullptr) {
		delete window_;
	}
}
