#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "menu_scene.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Constants.h"


GameEvent MenuScene::handleMouseButtonEvent(const MouseActionType mouse_type) {
	if (mouse_type != MouseActionType::LMB && mouse_type != MouseActionType::DoubleLMB) {
		return GameEvent::Unknown;
	}

	switch (hovered_button) {
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