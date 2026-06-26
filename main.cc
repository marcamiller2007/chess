#include <iostream>

#include <SFML/Graphics.hpp>

int main() {
	std::cout << "Hello World!";

	sf::RenderWindow window(sf::VideoMode({80, 80}), "Test Window");

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
	}

	return 0;
}
