#include "PopUp.h"


void PopUp::PositionPopUp(const sf::VideoMode& window_size) {
	Button& box = buttons[STR_BOX];
	Button& yes_button = buttons[STR_YES];
	Button& no_button = buttons[STR_NO];

	box.setSize(sf::Vector2f(window_size.width / 2.5, window_size.height / 2.5));
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


GameEvent PopUp::handleMouseButtonEvent(const MouseActionType mouse_type) {
	if (mouse_type != MouseActionType::LMB && mouse_type != MouseActionType::DoubleLMB) {
		return GameEvent::Unknown;
	}

	if (buttons_event.find(hovered_button) != buttons_event.end()) {
		return buttons_event.at(hovered_button);
	}

	return GameEvent::Unknown;
}


bool PopUp::changeMousePosition(const sf::Vector2i& pos) {
	std::string last_hovered = hovered_button;
	hovered_button = STR_UNKNOWN;

	for (auto i = buttons.begin(); i != buttons.end(); i++) {
		if (i->first != STR_BOX && i->second.isMouseHovering(pos)) {
			hovered_button = i->first;
			break;
		}
	}

	return hovered_button != last_hovered;
}


std::shared_ptr<Scene> PopUp::createPopUp(const GameEvent game_event, const sf::VideoMode window_size) {
	switch (game_event) {
	case GameEvent::QuitGame:
	{
		PopUp pop_up(game_event, window_size, "You are about to quit the game.\nAre you sure?");
		auto ptr = std::make_shared<PopUp>(pop_up);

		return std::static_pointer_cast<Scene>(ptr);
	}
	case GameEvent::NewGame:
	{
		PopUp pop_up(game_event, window_size, "Do you want to create new game?\nCurrent save game will be lost.");
		auto ptr = std::make_shared<PopUp>(pop_up);

		return std::static_pointer_cast<Scene>(ptr);
	}
	case GameEvent::QuitToMenu:
	{
		PopUp pop_up(game_event, window_size, "Do you want to quit to menu?\nCurrent game will be saved.");
		auto ptr = std::make_shared<PopUp>(pop_up);

		return std::static_pointer_cast<Scene>(ptr);
	}
	default:
		break;
	}

	return nullptr;
}


Scene::DrawableList PopUp::getDrawableList(const bool isFocusing, const int rank) {
	DrawableList list;

	for (auto e : buttons) {
		if (isFocusing && hovered_button != STR_BOX && e.first == hovered_button) {
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
