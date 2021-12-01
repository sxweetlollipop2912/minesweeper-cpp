#include <iostream>
#include <filesystem>
#include <thread>
#include <mutex>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../../Constants.h"
#include "../PopUp/PopUp.h"


void Scene::setWindowSize(const sf::VideoMode window_size) {
	this->window_size = window_size;
}


GameEvent Scene::handleMouseButtonEvent(const MouseActionType mouse_type) {
	return GameEvent::Unknown;
}


bool Scene::changeMousePosition(const sf::Vector2i& mouse_position) {
	if (pop_up) {
		return pop_up->changeMousePosition(mouse_position);
	}

	std::string last_hovered = hovered_button;
	hovered_button = STR_UNKNOWN;
	
	for (auto i = buttons.begin(); i != buttons.end(); i++) {
		if (!(i->second.isMouseHovering(mouse_position))) continue;
		hovered_button = i->first;
		break;
	}

	return hovered_button != last_hovered;
}


bool Scene::spawnPopUp(const GameEvent game_event) {
	if (pop_up) {
		return false;
	}

	switch (game_event) {
	case GameEvent::QuitGame:
	{
		PopUp pu(game_event, window_size, "You are about to quit the game.\nAre you sure?");
		auto ptr = std::make_shared<PopUp>(pu);

		pop_up = std::static_pointer_cast<Scene>(ptr);

		break;
	}
	case GameEvent::NewGame:
	{
		PopUp pu(game_event, window_size, "Do you want to create new game?\nCurrent save game will be lost.");
		auto ptr = std::make_shared<PopUp>(pu);

		pop_up = std::static_pointer_cast<Scene>(ptr);

		break;
	}
	case GameEvent::QuitToMenu:
	{
		PopUp pu(game_event, window_size, "Do you want to quit to menu?\nCurrent game will be saved.");
		auto ptr = std::make_shared<PopUp>(pu);

		pop_up = std::static_pointer_cast<Scene>(ptr);

		break;
	}
	default:
		pop_up = nullptr;

		break;
	}

	return pop_up != nullptr;
}


Scene::DrawableList Scene::getDrawableList(const bool isFocusing, const int rank) {
	DrawableList list;
	std::mutex listLock;

	bool isFocusingOnCurrent = isFocusing;
	if (pop_up) 
		isFocusingOnCurrent = false;

	auto t1 = std::thread([&]() {
		for (auto e : buttons) {
			if (isFocusingOnCurrent && e.first == hovered_button) {
				list.sprites.push_back(DrawableList::DrawableSprite(std::make_shared<sf::Sprite>(e.second.getHoveredSprite()), rank));
			}
			else {
				list.sprites.push_back(DrawableList::DrawableSprite(std::make_shared<sf::Sprite>(e.second.getDefaultSprite()), rank));
			}

			std::unique_lock<std::mutex>(listLock);
			list.texts.push_back(DrawableList::DrawableText(std::make_shared<sf::Text>(e.second.label.getSfText()), rank));
		}
	});

	auto t2 = std::thread([&]() {
		for (auto e : texts) {
			std::unique_lock<std::mutex>(listLock);
			list.texts.push_back(DrawableList::DrawableText(std::make_shared<sf::Text>(e.second.getSfText()), rank));
		}
	});

	t1.join();
	t2.join();

	// Pop-up drawable objects will overwrite those of current scene.
	if (pop_up) {
		list.append(pop_up->getDrawableList(isFocusing, rank + 1));
	}

	return list;
}
