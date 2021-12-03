#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "menu_scene.h"
#include "../PopUp/PopUp.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../../Constants.h"
#include "difficulties_scene.h"


GameEvent DifficultiesScene::onMouseButtonReleased(const MouseActionType mouse_type) {
	slider_row.onMouseReleased(mouse_type);
	slider_col.onMouseReleased(mouse_type);

	auto game_event = this->Scene::onMouseButtonReleased(mouse_type);

	if (game_event == GameEvent::Unknown && !pop_up) {
		if (mouse_type != MouseActionType::LMB && mouse_type != MouseActionType::DoubleLMB) {
			return GameEvent::Unknown;
		}

		if (hovered_button == STR_BEGINNER_BUTTON) {
			slider_row.setSliderValue(BEGINNER_ROW);
			slider_col.setSliderValue(BEGINNER_COL);
			game_event = GameEvent::ChangesInScene;
		}
		if (hovered_button == STR_INTER_BUTTON) {
			slider_row.setSliderValue(INTERMEDIATE_ROW);
			slider_col.setSliderValue(INTERMEDIATE_COL);
			game_event = GameEvent::ChangesInScene;
		}
		if (hovered_button == STR_EXPERT_BUTTON) {
			slider_row.setSliderValue(EXPERT_ROW);
			slider_col.setSliderValue(EXPERT_COL);
			game_event = GameEvent::ChangesInScene;
		}
	}

	return game_event;
}


GameEvent DifficultiesScene::onMouseButtonPressed(const MouseActionType mouse_type) {
	bool change = false;

	change |= slider_row.onMousePressed(mouse_type);
	change |= slider_col.onMousePressed(mouse_type);

	return change ? GameEvent::ChangesInScene : GameEvent::Unknown;
}


bool DifficultiesScene::changeMousePosition(const sf::Vector2i& pos) {
	bool change = false;
	
	change |= this->Scene::changeMousePosition(pos);
	change |= slider_row.changeMousePosition(pos);
	change |= slider_col.changeMousePosition(pos);

	return change;
}


int DifficultiesScene::getCurrentRow() const {
	return slider_row.getSliderValue();
}


int DifficultiesScene::getCurrentCol() const {
	return slider_col.getSliderValue();
}


Scene::DrawableList DifficultiesScene::getDrawableList(const bool is_focusing, const int rank) {
	Scene::DrawableList list;

	list.append(slider_row.getDrawableList(is_focusing, rank));
	list.append(slider_col.getDrawableList(is_focusing, rank));

	list.append(this->Scene::getDrawableList(is_focusing, rank));

	return list;
}
