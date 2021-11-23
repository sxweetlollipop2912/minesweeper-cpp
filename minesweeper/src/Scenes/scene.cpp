#include <iostream>
#include <filesystem>
#include <thread>
#include <mutex>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Constants.h"


void Scene::setWindowSize(const sf::VideoMode window_size) {
	this->window_size = window_size;
}


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


Scene::DrawableList Scene::getDrawableList() {
	DrawableList list;
	std::mutex listLock;

	auto t1 = std::thread([&]() {
		for (auto e : map_button) {
			if (e.first == hovered_button) {
				list.sprites.push_back(std::make_shared<sf::Sprite>(e.second.getHoveredSprite()));
			}
			else {
				list.sprites.push_back(std::make_shared<sf::Sprite>(e.second.getDefaultSprite()));
			}

			std::unique_lock<std::mutex>(listLock);
			list.texts.push_back(std::make_shared<sf::Text>(e.second.label.getSfText()));
		}
	});

	auto t2 = std::thread([&]() {
		for (auto e : map_text) {
			std::unique_lock<std::mutex>(listLock);
			list.texts.push_back(std::make_shared<sf::Text>(e.second.getSfText()));
		}
	});

	t1.join();
	t2.join();

	return list;
}
