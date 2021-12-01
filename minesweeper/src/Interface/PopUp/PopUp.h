#pragma once

#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"
#include "../../Enums.h"
#include "../../Constants.h"
#include "../Button/Button.h"
#include "../Text/Text.h"


// A pop-up at the center of the screen that shows a message and offers Yes/No options.
class PopUp : public Scene {
	friend class Scene;

private:
	const std::string STR_BOX = "box";
	const std::string STR_YES = "yes";
	const std::string STR_NO = "no";


	// Aligns all buttons and texts, including the pop-up, in their appropriate positions.
	void PositionPopUp(const sf::VideoMode& window_size);


	// OVERRIDING METHODS

	// Call on a mouse button event.
	GameEvent handleMouseButtonEvent(const MouseActionType mouse_type) override;
	// Changes window graphics base on new mouse position.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos) override;

public:
	PopUp(const GameEvent game_event = GameEvent::Unknown, const sf::VideoMode& window_size = sf::VideoMode(0, 0), const std::string& msg = "", const std::string& yes_msg = "YES", const std::string& no_msg = "NO") {
		buttons_event[STR_YES] = game_event;
		buttons_event[STR_NO] = GameEvent::ClosePopUp;

		Button& box = buttons[STR_BOX];
		box.setImage(TextureType::ButtonDefault);
		box.label.setText(msg);

		Button& yes_button = buttons[STR_YES];
		yes_button.setImage(TextureType::ButtonDefault);
		yes_button.label.setText(yes_msg);
		yes_button.alignImageAndText();

		Button& no_button = buttons[STR_NO];
		no_button.setImage(TextureType::ButtonDefault);
		no_button.label.setText(no_msg);
		no_button.alignImageAndText();

		Button::equalizeButtonsSize(yes_button, no_button);
		PositionPopUp(window_size);
	}

	DrawableList getDrawableList(const bool isFocusing = false, const int rank = 0) override;
};