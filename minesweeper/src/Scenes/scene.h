#pragma once

#include <iostream>
#include <algorithm>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Constants.h"


class Scene : public GraphicsObject {
	friend class Window;

protected:
	std::map <std::string, std::string> texture_path;
	std::map <ButtonType, Button> map_button;
	std::map <std::string, Text> map_text;

	std::map <ButtonType, SceneType> next_scene;
	ButtonType hoveredButton;

public:
	Scene() {
		texture_path.clear();
		map_button.clear();
		map_text.clear();
		next_scene.clear();

		hoveredButton = ButtonType::Unknown;
	}

	// Adds an texture path to scene data.
	// > Returns Result::failure if path cannot be found,
	// > otherwise, returns Result::success.
	Result registerTexturePath(const std::string& texture_name, const std::string& texture_path);

	// Call on a mouse button event.
	// This method is empty.
	Result handleMouseButtonEvent(const sf::Event::MouseButtonEvent mouse_event);
	// Changes window graphics base on new mouse position.
	void changeMousePosition(const sf::Vector2i& pos);

	// Cleans up after undrawing the scene.
	void undrawScene();
};