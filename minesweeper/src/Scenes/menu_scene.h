#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"


class MenuScene : public Scene {
	friend class Window;

private:
	sf::Vector2u window_size;


	// Initializes MenuScene object.
	void initialize(const sf::Vector2u& window_size);

	// Call on a mouse button event.
	GameEvent handleMouseButtonEvent(const MouseActionType mouse_type) override;

public:
	MenuScene() {
		int width = sf::VideoMode::getDesktopMode().width;
		int height = sf::VideoMode::getDesktopMode().height;
		window_size.x = width;
		window_size.y = height;

		initialize(window_size);
	}

	MenuScene(const sf::Vector2u& window_size) {
		initialize(window_size);
	}	
};