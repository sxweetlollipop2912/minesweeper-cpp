#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "../../Constants.h"
#include "../../Enums.h"


class MenuScene : public Scene {
private:
	const std::string STR_LOAD_GAME = "load_game";
	const std::string STR_NEW_GAME = "new_game";
	const std::string STR_LEADERBOARD = "leaderboard";
	const std::string STR_QUIT_GAME = "quit_game";

public:
	MenuScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode());
};