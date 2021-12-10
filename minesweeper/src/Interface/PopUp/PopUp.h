#pragma once

#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"
#include "../../Enums.h"
#include "../../Constants.h"
#include "../Button/Button.h"
#include "../Text/Text.h"


// A pop-up at the center of the screen that shows a message and offers Yes/No options.
class PopUp : public Scene {
private:
	const std::string STR_BOX = "box";
	const std::string STR_YES = "yes";
	const std::string STR_NO = "no";


	// Aligns all buttons and texts, including the pop-up, in their appropriate positions.
	void PositionPopUp(const sf::VideoMode& window_size);

public:
	PopUp(const GameEvent game_event = GameEvent::Unknown, const sf::VideoMode& window_size = sf::VideoMode(0, 0), const std::string& msg = "", const std::string& yes_msg = "YES", const std::string& no_msg = "NO");

	DrawableList getDrawableList(const bool is_focusing = false, const int rank = 0) override;
};