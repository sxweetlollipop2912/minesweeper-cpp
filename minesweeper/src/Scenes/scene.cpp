#include <iostream>
#include <filesystem>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Constants.h"


bool Scene::changeMousePosition(const sf::Vector2i& mouse_position) {
	ButtonType last_hovered = hoveredButton;
	hoveredButton = ButtonType::Unknown;
	
	for (auto i = map_button.begin(); i != map_button.end(); i++) {
		if (!(i->second.isMouseHovering(mouse_position))) continue;
		hoveredButton = i->first;
		break;
	}

	return hoveredButton != last_hovered;
}


void Scene::undrawScene() {
	isDrawing = false;

	for (auto i = map_button.begin(); i != map_button.end(); i++)
		i->second.isDrawing = false;

	for (auto i = map_text.begin(); i != map_text.end(); i++)
		i->second.isDrawing = false;
}
