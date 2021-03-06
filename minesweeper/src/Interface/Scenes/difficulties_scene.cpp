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
			beginner_button.setImage(TextureType::DefaultButton);
			beginner_button.label.setText("Beginner");
			beginner_button.label.setFontSize(DEFAULT_NORMAL_FONT_SIZE);
			beginner_button.setTopLeftPosY(pos_y_diff_button);
			beginner_button.alignImageAndText();

			Button& inter_button = buttons[STR_INTER_BUTTON];
			inter_button.setImage(TextureType::DefaultButton);
			inter_button.label.setText("Intermediate");
			inter_button.label.setFontSize(DEFAULT_NORMAL_FONT_SIZE);
			inter_button.setTopLeftPosY(pos_y_diff_button);
			inter_button.alignImageAndText();

			Button& expert_button = buttons[STR_EXPERT_BUTTON];
			expert_button.setImage(TextureType::DefaultButton);
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

			float space_x = this->window_size.width / (float)30;
			beginner_button.setTopLeftPosX(inter_button.getPosTopLeft().x - space_x - beginner_button.getSize().x);
			beginner_button.centerTextInButton();
			expert_button.setTopLeftPosX(inter_button.getPosTopLeft().x + inter_button.getSize().x + space_x);
			expert_button.centerTextInButton();
		}

		Button& continue_button = buttons[STR_CONTINUE_BUTTON];
		continue_button.setImage(TextureType::DefaultButton);
		continue_button.label.setText("Continue");
		continue_button.setTopLeftPosY(pos_y_continue_button);
		continue_button.alignImageAndText();
		continue_button.centerButtonHorizontally(this->window_size.width);

		Button& return_button = buttons[STR_RETURN_BUTTON];
		return_button.setImage(TextureType::ReturnButton);
		return_button.setSize(sf::Vector2f(buttons[STR_BEGINNER_BUTTON].getSize().y, buttons[STR_BEGINNER_BUTTON].getSize().y));
		return_button.setTopLeftPosY(buttons[STR_BEGINNER_BUTTON].getPosTopLeft().y);
		return_button.setTopLeftPosX(buttons[STR_BEGINNER_BUTTON].getPosTopLeft().x - return_button.getSize().x - (return_button.getSize().x / (float)2));
	}

	// Sliders
	{
		float pos_y_slider_row = this->window_size.height * POS_Y_COEF_SLIDER_ROW;
		float pos_y_slider_col = this->window_size.height * POS_Y_COEF_SLIDER_COL;
        float slider_width = this->window_size.width * WIDTH_COEF_SLIDER;
        float slider_height = this->window_size.height * HEIGHT_COEF_SLIDER;

		slider_row = std::make_shared<Slider>(Slider(MIN_ROW, MAX_ROW, MIN_ROW, sf::Vector2f(0, pos_y_slider_row), slider_width, slider_height));
		slider_col = std::make_shared<Slider>(Slider(MIN_COLUMN, MAX_COLUMN, MIN_COLUMN, sf::Vector2f(0, pos_y_slider_col), slider_width, slider_height));

		slider_row->centerSliderHorizontally(this->window_size.width);
		slider_col->centerSliderHorizontally(this->window_size.width);
	}
}


GameEvent DifficultiesScene::onMouseButtonReleased(const MouseActionType mouse_type) {
	slider_row->onMouseButtonReleased(mouse_type);
	slider_col->onMouseButtonReleased(mouse_type);

	auto game_event = this->Scene::onMouseButtonReleased(mouse_type);

	if (game_event == GameEvent::ChangesInScene && !pop_up) {
		if (mouse_type != MouseActionType::FirstLMB) {
			return GameEvent::Unknown;
		}

		if (hovered_button == STR_BEGINNER_BUTTON) {
			slider_row->setSliderValue(BEGINNER_ROW);
			slider_col->setSliderValue(BEGINNER_COL);
		}
		if (hovered_button == STR_INTER_BUTTON) {
			slider_row->setSliderValue(INTERMEDIATE_ROW);
			slider_col->setSliderValue(INTERMEDIATE_COL);
		}
		if (hovered_button == STR_EXPERT_BUTTON) {
			slider_row->setSliderValue(EXPERT_ROW);
			slider_col->setSliderValue(EXPERT_COL);
		}
	}

	return game_event;
}


GameEvent DifficultiesScene::onMouseButtonPressed(const MouseActionType mouse_type) {
	auto game_event = Scene::onMouseButtonPressed(mouse_type);

	if (game_event == GameEvent::Unknown && !pop_up) {
		bool change = false;
		change |= slider_row->onMouseButtonPressed(mouse_type);
		change |= slider_col->onMouseButtonPressed(mouse_type);

		game_event = change ? GameEvent::ChangesInScene : GameEvent::Unknown;
	}

	return game_event;
}


bool DifficultiesScene::changeMousePosition(const sf::Vector2i& pos) {
	bool change = false;
	
	change |= this->Scene::changeMousePosition(pos);
	change |= slider_row->changeMousePosition(pos);
	change |= slider_col->changeMousePosition(pos);

	return change;
}


int DifficultiesScene::getCurrentRow() const {
	return slider_row->getSliderValue();
}


int DifficultiesScene::getCurrentCol() const {
	return slider_col->getSliderValue();
}


void DifficultiesScene::draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing) {
	slider_row->draw(renderer, is_focusing);
	slider_col->draw(renderer, is_focusing);

	Scene::draw(renderer, is_focusing);
}