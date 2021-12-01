#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "menu_scene.h"
#include "../PopUp/PopUp.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../../Constants.h"


GameEvent MenuScene::handleMouseButtonEvent(const MouseActionType mouse_type) {
	auto game_event = GameEvent::Unknown;

	// If pop-up already exists.
	if (pop_up) {
		game_event = pop_up->handleMouseButtonEvent(mouse_type);
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
		if (spawnPopUp(game_event)) game_event = GameEvent::OpenPopUp;
	}

	
	switch (game_event) {
		case GameEvent::OpenPopUp:
		{
			return GameEvent::OpenPopUp;
		}
		case GameEvent::ClosePopUp:
		{
			pop_up = nullptr;

			return GameEvent::ClosePopUp;
		}
		case GameEvent::QuitGame:
		{
			return GameEvent::QuitGame;
		}
		case GameEvent::NewGame:
		{
			return GameEvent::NewGame;
		}
		case GameEvent::LoadGame:
		{
			return GameEvent::LoadGame;
		}
		case GameEvent::ShowLeaderboard:
		{
			return GameEvent::ShowLeaderboard;
		}
	}

	return GameEvent::Unknown;
}