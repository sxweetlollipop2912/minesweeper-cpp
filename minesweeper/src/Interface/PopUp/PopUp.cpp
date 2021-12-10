#include "PopUp.h"


PopUp::PopUp(const GameEvent game_event, const sf::VideoMode& window_size, const std::string& msg, const std::string& yes_msg, const std::string& no_msg) : Scene(SceneType::PopUp) {
	buttons_event[STR_YES] = game_event;
	buttons_event[STR_NO] = GameEvent::ClosePopUp;

	Button& box = buttons[STR_BOX];
	box.setImage(TextureType::ButtonDefault);
	box.label.setText(msg);
	box.setTransparent();

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


Scene::DrawableList PopUp::getDrawableList(const bool is_focusing, const int rank) {
	DrawableList list;

	for (auto e : buttons) {
		if (is_focusing && hovered_button != STR_BOX && e.first == hovered_button) {
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

	return list;
}
