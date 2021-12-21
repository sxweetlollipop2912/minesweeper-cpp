#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "../Slider/Slider.h"
#include "../PopUp/PopUp.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../../Constants.h"
#include "../../Enums.h"
#include "../../Structs.h"


class DifficultiesScene : public Scene {
private:
	const std::string STR_BEGINNER_BUTTON = "beginner";
	const std::string STR_EXPERT_BUTTON = "expert";
	const std::string STR_INTER_BUTTON = "inter";
	const std::string STR_CONTINUE_BUTTON = "continue";
	const std::string STR_RETURN_BUTTON = "return";

	std::shared_ptr<Slider> slider_row;
	std::shared_ptr<Slider> slider_col;


	// Call on a mouse button released event.
	// Returns corresponding GameEvent.
	GameEvent onMouseButtonReleased(const MouseActionType mouse_type) override;
	// Call on a mouse button pressed event.
	// Returns corresponding GameEvent.
	GameEvent onMouseButtonPressed(const MouseActionType mouse_type) override;
	// Changes window graphics base on new mouse position.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos) override;

public:
	DifficultiesScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode());

	int getCurrentRow() const;
	int getCurrentCol() const;

	// Draws all textures and texts in the scene on an sf::RenderTarget object
	void draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing = true) override;
};