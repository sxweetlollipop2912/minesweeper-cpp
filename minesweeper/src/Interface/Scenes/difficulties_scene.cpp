#include <iostream>

#include "difficulties_scene.h"


DifficultiesScene::DifficultiesScene(const sf::VideoMode& window_size) : Scene(window_size, SceneType::Difficulties) {
	next_scene[GameEvent::NewGame] = SceneType::Playing;
	next_scene[GameEvent::QuitToMenu] = SceneType::Menu;

	buttons_event[STR_CONTINUE_BUTTON] = GameEvent::NewGame;
	buttons_event[STR_RETURN_BUTTON] = GameEvent::QuitToMenu;
	buttons_event[STR_BEGINNER_BUTTON] = GameEvent::ChangesInScene;
	buttons_event[STR_INTER_BUTTON] = GameEvent::ChangesInScene;
	buttons_event[STR_EXPERT_BUTTON] = GameEvent::ChangesInScene;

	// Buttons
	{
		float pos_y_diff_button = this->window_size.height * POS_Y_COEF_DIFF_BUTTON;
		float pos_y_continue_button = this->window_size.height * POS_Y_COEF_CONTINUE_BUTTON;

		// Difficulty buttons
		{
			Button& beginner_button = buttons[STR_BEGINNER_BUTTON];
			beginner_button.setImage(TextureType::ButtonDefault);
			beginner_button.label.setText("Beginner");
			beginner_button.label.setFontSize(DEFAULT_NORMAL_FONT_SIZE);
			beginner_button.setTopLeftPosY(pos_y_diff_button);
			beginner_button.alignImageAndText();

			Button& inter_button = buttons[STR_INTER_BUTTON];
			inter_button.setImage(TextureType::ButtonDefault);
			inter_button.label.setText("Intermediate");
			inter_button.label.setFontSize(DEFAULT_NORMAL_FONT_SIZE);
			inter_button.setTopLeftPosY(pos_y_diff_button);
			inter_button.alignImageAndText();

			Button& expert_button = buttons[STR_EXPERT_BUTTON];
			expert_button.setImage(TextureType::ButtonDefault);
			expert_button.label.setText("Expert");
			expert_button.label.setFontSize(DEFAULT_NORMAL_FONT_SIZE);
			expert_button.setTopLeftPosY(pos_y_diff_button);
			expert_button.alignImageAndText();

			for (auto i = buttons.begin(); i != buttons.end(); i++) {
				if (i->first != STR_BEGINNER_BUTTON && i->first != STR_INTER_BUTTON && i->first != STR_EXPERT_BUTTON)
					continue;

				auto j = i; j++;
				for (; j != buttons.end(); j++) {
					if (j->first != STR_BEGINNER_BUTTON && j->first != STR_INTER_BUTTON && j->first != STR_EXPERT_BUTTON)
						continue;

					Button::equalizeButtonsSize(i->second, j->second);
				}
			}

			inter_button.centerButtonHorizontally(this->window_size.width);

			float padding_x = this->window_size.width / (float)4;
			beginner_button.setTopLeftPosX(padding_x);
			beginner_button.centerTextInButton();
			expert_button.setTopLeftPosX(this->window_size.width - padding_x - expert_button.getSize().x);
			expert_button.centerTextInButton();
		}

		Button& continue_button = buttons[STR_CONTINUE_BUTTON];
		continue_button.setImage(TextureType::ButtonDefault);
		continue_button.label.setText("Continue");
		continue_button.setTopLeftPosY(pos_y_continue_button);
		continue_button.alignImageAndText();
		continue_button.centerButtonHorizontally(this->window_size.width);

		Button& return_button = buttons[STR_RETURN_BUTTON];
		return_button.setImage(TextureType::ButtonDefault);
		return_button.setPadding(sf::Vector2f(DEFAULT_PADDING_SIZE.x / 2, DEFAULT_PADDING_SIZE.y / 2));
		return_button.label.setText("Back to Menu");
		return_button.label.setFontSize(DEFAULT_SMALL_FONT_SIZE);
		return_button.alignImageAndText();
	}

	// Sliders
	{
		float pos_y_slider_row = this->window_size.height * POS_Y_COEF_SLIDER_ROW;
		float pos_y_slider_col = this->window_size.height * POS_Y_COEF_SLODER_COL;

		slider_row = Slider(MIN_ROW, MAX_ROW, sf::Vector2f(0, pos_y_slider_row));
		slider_col = Slider(MIN_COLUMN, MAX_COLUMN, sf::Vector2f(0, pos_y_slider_col));

		slider_row.centerSliderHorizontally(this->window_size.width);
		slider_col.centerSliderHorizontally(this->window_size.width);
	}
}


GameEvent DifficultiesScene::onMouseButtonReleased(const MouseActionType mouse_type) {
	slider_row.onMouseReleased(mouse_type);
	slider_col.onMouseReleased(mouse_type);

	auto game_event = this->Scene::onMouseButtonReleased(mouse_type);

	if (game_event == GameEvent::ChangesInScene && !pop_up) {
		if (mouse_type != MouseActionType::LMB && mouse_type != MouseActionType::DoubleLMB) {
			return GameEvent::Unknown;
		}

		if (hovered_button == STR_BEGINNER_BUTTON) {
			slider_row.setSliderValue(BEGINNER_ROW);
			slider_col.setSliderValue(BEGINNER_COL);
		}
		if (hovered_button == STR_INTER_BUTTON) {
			slider_row.setSliderValue(INTERMEDIATE_ROW);
			slider_col.setSliderValue(INTERMEDIATE_COL);
		}
		if (hovered_button == STR_EXPERT_BUTTON) {
			slider_row.setSliderValue(EXPERT_ROW);
			slider_col.setSliderValue(EXPERT_COL);
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


DrawableList DifficultiesScene::getDrawableList(const bool is_focusing, const int rank) {
	DrawableList list;

	list.append(slider_row.getDrawableList(is_focusing, rank));
	list.append(slider_col.getDrawableList(is_focusing, rank));

	list.append(this->Scene::getDrawableList(is_focusing, rank));

	return list;
}
