#include <iostream>
#include <filesystem>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Constants.h"


GameEvent Scene::handleMouseButtonEvent(const MouseActionType mouse_type) {
	return GameEvent::Unknown;
}


bool Scene::changeMousePosition(const sf::Vector2i& mouse_position) {
	GameEvent last_hovered = hovered_button;
	hovered_button = GameEvent::Unknown;
	
	for (auto i = map_button.begin(); i != map_button.end(); i++) {
		if (!(i->second.isMouseHovering(mouse_position))) continue;
		hovered_button = i->first;
		break;
	}

	return hovered_button != last_hovered;
}
