#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>

#include "./screen.h"

using namespace Chess;

Screen::Screen() {
	state_ = new Board::Board();

	window_ = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(kWindowSize, kWindowSize)), "Chess");

	stop_.store(true);
}

void Screen::LogicThread() {
	std::cout << "Starting logic thread\n";

	while (!stop_.load()) {
		std::this_thread::sleep_for(std::chrono::seconds(1));

		std::cout << "LT\n";
	}
}

void Screen::WindowThread() {
	std::cout << "Starting window thread\n";

	sf::Color brown(88, 57, 39);

	while (window_->isOpen()) {	
		//std::cout << "WT\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		while(const std::optional event = window_->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window_->close();
				stop_.store(true);
				return;
			}

			// Poll for a user click
			if (event->is<sf::Event::MouseButtonPressed>()) {
				sf::Vector2i mouse_coords = sf::Mouse::getPosition(*window_);
				std::cout << "X: " << mouse_coords.x << " Y: " << mouse_coords.y << "\n";

				// Check it was in the window's area
				if ((mouse_coords.x >= 0) && (mouse_coords.x <= 800) &&
					(mouse_coords.y >= 0) && (mouse_coords.y <= 800)) {
					std::unique_lock<std::shared_mutex> board_guard(board_lock_);

					// send click to the board
					state_->HandleClick(mouse_coords);
				}
			}

		}

		// Clear, Redraw, Display
		window_->clear(brown);

		// Board Lock
		{
			std::unique_lock<std::shared_mutex> board_guard(board_lock_);

			state_->Draw(window_);

			state_->SetUpdateFalse();
		}

		window_->display();

	}
}

void Screen::Start() {
	// Thread shouldn't stop
	stop_.store(false);

	// load the board
	state_->Load();

	// launch threads
	logic_thread_ = new std::thread(&Chess::Screen::LogicThread, this);
	logic_thread_->detach();

	WindowThread();
}

Screen::~Screen() {
	delete logic_thread_;

	delete state_;

	if (window_ != nullptr) {
		delete window_;
	}
}
