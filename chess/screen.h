#ifndef SCREEN_H
#define SCREEN_H

#include <mutex>
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
	void GraphicsThread();
	void EventThread();

	mutable std::mutex board_lock_;
	mutable std::mutex window_lock_;

	std::thread graphics_thread_;
	std::thread event_thread_;
};
}
#endif
