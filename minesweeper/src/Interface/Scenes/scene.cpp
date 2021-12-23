#include <iostream>

#include "scene.h"
#include "../PopUp/PopUp.h"


Scene::Scene(const sf::VideoMode& window_size, const SceneType scene_type) {
	this->scene_type = scene_type;
	this->window_size = window_size;

	pop_up = nullptr;
	buttons.clear();
	texts.clear();
	next_scene.clear();

	buttons_event[STR_UNKNOWN] = GameEvent::Unknown;
	hovered_button = STR_UNKNOWN;
	pos_mouse = sf::Vector2i(-1, -1);
}


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
		if (mouse_type != MouseActionType::FirstLMB) {
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
		if (buttons_event.find(i->first) == buttons_event.end()) continue;
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
	return SceneType::Unknown;
}


void Scene::draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing) {
	bool is_focusing_on_current = is_focusing;
	if (pop_up)
		is_focusing_on_current = false;

	for (auto e : buttons) {
		if (is_focusing_on_current && e.first == hovered_button) {
			e.second.getHoveredSprite(sprite);
			renderer->draw(sprite);
		}
		else {
			e.second.getDefaultSprite(sprite);
			renderer->draw(sprite);
		}
		e.second.label.getSfText(text);
		renderer->draw(text);
	}

	for (auto e : texts) {
		e.second.getSfText(text);
		renderer->draw(text);
	}

	// Pop-up drawable objects will overwrite those of current scene.
	if (pop_up) {
		pop_up->draw(renderer, is_focusing);
	}
}