#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"


class MenuScene : public Scene {
private:
	sf::Vector2u window_size;

public:
	MenuScene() {
		int width = sf::VideoMode::getDesktopMode().width;
		int height = sf::VideoMode::getDesktopMode().height;

		initialize(window_size);
	}

	MenuScene(const sf::Vector2u& window_size) {
		initialize(window_size);
	}

	
	// Initializes MenuScene object.
	void initialize(const sf::Vector2u& window_size);
};