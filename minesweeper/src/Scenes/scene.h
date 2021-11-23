#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

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


	struct DrawableList {
		std::vector <std::shared_ptr<sf::Sprite>> sprites;
		std::vector <std::shared_ptr<sf::Text>> texts;

		DrawableList() {
			sprites.clear();
			texts.clear();
		}

		void add(const DrawableList& list) {
			for (auto e : list.sprites) {
				sprites.push_back(e);
			}
			for (auto e : list.texts) {
				texts.push_back(e);
			}
		}
	};
	
	// Gets a DrawableList object that contains all sprites and texts in the scene.
	virtual DrawableList getDrawableList();
};