#include "PopUp.h"


PopUp::PopUp(const GameEvent yes_game_event, const GameEvent no_game_event, const sf::VideoMode& window_size, bool use_double_lmb, const std::string& msg, const std::string& yes_msg, const std::string& no_msg) : Scene(window_size, SceneType::PopUp, use_double_lmb) {
	buttons_event[STR_YES] = yes_game_event;
	buttons_event[STR_NO] = no_game_event;

	Button& box = buttons[STR_BOX];
	box.setImage(TextureType::PopUpBackground);
	box.label.setText(msg);
	box.setTransparent();

	Button& yes_button = buttons[STR_YES];
	yes_button.setImage(TextureType::YesNoButton);
	yes_button.setPadding(sf::Vector2f(DEFAULT_PADDING_SIZE.x / 2, DEFAULT_PADDING_SIZE.y));
	yes_button.label.setText(yes_msg);
	yes_button.alignImageAndText();

	Button& no_button = buttons[STR_NO];
	no_button.setImage(TextureType::YesNoButton);
	yes_button.setPadding(sf::Vector2f(DEFAULT_PADDING_SIZE.x / 2, DEFAULT_PADDING_SIZE.y));
	no_button.label.setText(no_msg);
	no_button.alignImageAndText();

	Button::equalizeButtonsSize(yes_button, no_button);
	PositionPopUp(window_size);
}


void PopUp::PositionPopUp(const sf::VideoMode& window_size) {
	Button& box = buttons[STR_BOX];
	Button& yes_button = buttons[STR_YES];
	Button& no_button = buttons[STR_NO];

	box.setSize(sf::Vector2f(window_size.width / 2.8, window_size.height / 3));
	box.centerButtonHorizontally(window_size.width);
	box.centerButtonVertically(window_size.height);

	yes_button.alignImageAndText();
	no_button.alignImageAndText();
	Button::equalizeButtonsSize(yes_button, no_button);

	sf::Vector2f popup_size = box.getSize();

	// X-axis
	{
		box.centerTextInButton();
		int d = (popup_size.x - (yes_button.getSize().x + no_button.getSize().x)) / 3;
		yes_button.setTopLeftPosX(box.getPosTopLeft().x + d);
		no_button.setTopLeftPosX(yes_button.getPosRightDown().x + d);
	}

	// Y-axis
	{
		float text_height = box.label.getHeight();
		int d = (popup_size.y - (text_height + yes_button.getSize().y)) / 4;
		box.label.setTopLeftPosY(box.getPosTopLeft().y + d);
		yes_button.setTopLeftPosY(box.label.getPosRightDown().y + 2 * d);
		no_button.setTopLeftPosY(box.label.getPosRightDown().y + 2 * d);
	}

	yes_button.centerTextInButton();
	no_button.centerTextInButton();
}