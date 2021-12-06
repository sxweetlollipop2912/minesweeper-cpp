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


GameEvent Scene::onMouseButtonReleased(const MouseActionType mouse_type) {
	auto game_event = GameEvent::Unknown;

	// If pop-up already exists.
	if (pop_up) {
		game_event = pop_up->onMouseButtonReleased(mouse_type);
		if (game_event != GameEvent::Unknown) {
			pop_up = nullptr;
			changeMousePosition(pos_mouse);
		}
	}
	// Otherwise,
	else {
		if (mouse_type != MouseActionType::LMB && mouse_type != MouseActionType::DoubleLMB) {
			return GameEvent::Unknown;
		}

		if (buttons_event.find(hovered_button) != buttons_event.end()) {
			game_event = buttons_event.at(hovered_button);
		}

		// If pop-up is successfully created.
		if (scene_type != SceneType::PopUp && spawnPopUp(game_event)) game_event = GameEvent::OpenPopUp;
	}

	if (game_event == GameEvent::OpenPopUp || game_event == GameEvent::ClosePopUp) {
		game_event = GameEvent::ChangesInScene;
	}

	return game_event;
}


GameEvent Scene::onMouseButtonPressed(const MouseActionType mouse_type) {
	return GameEvent::Unknown;
}


bool Scene::changeMousePosition(const sf::Vector2i& mouse_position) {
	pos_mouse = mouse_position;

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
		if (scene_type == SceneType::Playing) {
			PopUp pu(game_event, window_size, "Do you want to quit to menu?\nCurrent game will be saved.");
			auto ptr = std::make_shared<PopUp>(pu);

			pop_up = std::static_pointer_cast<Scene>(ptr);
		}

		break;
	}
	default:
		pop_up = nullptr;

		break;
	}

	return pop_up != nullptr;
}


SceneType Scene::getNextScene(const GameEvent game_event) const {
	if (next_scene.find(game_event) != next_scene.end()) {
		return next_scene.at(game_event);
	}
	return SceneType::Unkown;
}


Scene::DrawableList Scene::getDrawableList(const bool is_focusing, const int rank) {
	DrawableList list;

	bool is_focusing_on_current = is_focusing;
	if (pop_up)
		is_focusing_on_current = false;

	for (auto e : buttons) {
		if (is_focusing_on_current && e.first == hovered_button) {
			list.sprites.push_back(DrawableList::DrawableSprite(std::make_shared<sf::Sprite>(e.second.getHoveredSprite()), rank));
		}
		else {
			list.sprites.push_back(DrawableList::DrawableSprite(std::make_shared<sf::Sprite>(e.second.getDefaultSprite()), rank));
		}
		list.texts.push_back(DrawableList::DrawableText(std::make_shared<sf::Text>(e.second.label.getSfText()), rank));
	}

	for (auto e : texts) {
		list.texts.push_back(DrawableList::DrawableText(std::make_shared<sf::Text>(e.second.getSfText()), rank));
	}

	// Pop-up drawable objects will overwrite those of current scene.
	if (pop_up) {
		list.append(pop_up->getDrawableList(is_focusing, rank + 1));
	}

	return list;
}
