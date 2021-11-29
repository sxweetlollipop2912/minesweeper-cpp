#pragma once

#include <SFML/Graphics.hpp>

#include "../Enums.h"
#include "../Constants.h"
#include "../Button/Button.h"
#include "../Text/Text.h"


// A pop-up at the center of the screen that shows a message and offers Yes/No options.
class PopUp : public Button {
private:
	Button yes_button;
	Button no_button;



	// Aligns all buttons, including the pop-up, in their appropriate positions.
	void alignButtonsPosition();

public:
	PopUp(const std::string& msg = "", const std::string& yes_msg = "YES", const std::string& no_msg = "NO") {
		this->label.setText(msg);
		this->label.setFontSize(DEFAULT_TITLE_FONT_SIZE);
		this->centerTextInButton();

		yes_button.setImage(TextureType::ButtonDefault);
		yes_button.label.setText(yes_msg);
		yes_button.alignImageAndText();

		no_button.setImage(TextureType::ButtonDefault);
		no_button.label.setText(no_msg);
		no_button.setTopLeftPosition(sf::Vector2f(0, pos_y_load_game_button));
		no_button.alignImageAndText();

		Button::equalizeButtonsSize(yes_button, no_button);
		alignButtonsPosition();
	}


	bool inMouse
};