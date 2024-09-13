#include "events.hpp"

void handle_events(sf::Window &window) {
	sf::Event ev;
	while (window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed) {
			window.close();
		} else if (ev.type == sf::Event::KeyPressed) {
			switch (ev.key.code) {
				case sf::Keyboard::Escape: {
					window.close();
					break;
				}
				default: break;
			}
		}
	}
}
