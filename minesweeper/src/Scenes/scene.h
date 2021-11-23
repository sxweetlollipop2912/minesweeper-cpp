#pragma once

#include <iostream>
#include <algorithm>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Constants.h"


class Scene {
	friend class Window;

protected:
	sf::VideoMode window_size;

	std::map <GameEvent, Button> map_button;
	std::map <std::string, Text> map_text;

	std::map <GameEvent, SceneType> next_scene;
	GameEvent hovered_button;


	void setWindowSize(const sf::VideoMode window_size);

	// Call on a mouse button event.
	virtual GameEvent handleMouseButtonEvent(const MouseActionType mouse_type);
	// Changes window graphics base on new mouse position.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	virtual bool changeMousePosition(const sf::Vector2i& pos);

public:
	Scene() {
		map_button.clear();
		map_text.clear();
		next_scene.clear();

		hovered_button = GameEvent::Unknown;
	}
};