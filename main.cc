//#include <iostream>

#include <SFML/Graphics.hpp>

#include "./chess/screen.h"

using namespace Chess;

int main() {
	Screen *game = new Screen();

	game->Start();

	delete game;


	/*sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 800)), "Test");

	sf::Texture texture;
	if (!texture.loadFromFile("./chess_models/Chess_kdt60.png")) {
		return -1;
	}

	sf::Sprite sprite(texture);

	sprite.setPosition({400, 400});

	while (window.isOpen()) {
		while(const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
				return 1;
			}
		}

		window.clear(sf::Color::Black);

		window.draw(sprite);

		window.display();

	}*/

	return 0;
}
