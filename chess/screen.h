#ifndef SCREEN_H
#define SCREEN_H

#include <atomic>
#include <shared_mutex>
#include <thread>

#include <SFML/Graphics.hpp>

#include "./board/board.h"

namespace Chess {

class Screen {
public:
	Screen();
	void Start();
	~Screen();
	
	const uint16_t kWindowSize = 800;
private:
	sf::RenderWindow *window_;
	Board::Board *state_;

	// Thread things
	void LogicThread();
	void WindowThread();

	mutable std::shared_mutex board_lock_;
	std::atomic<bool> stop_;

	std::thread *logic_thread_;
};
}
#endif
