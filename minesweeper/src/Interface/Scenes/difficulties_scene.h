#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"
#include "../Slider/Slider.h"


class DifficultiesScene : public Scene {
	friend class Window;

private:
	const std::string STR_BEGINNER_BUTTON = "beginner";
	const std::string STR_EXPERT_BUTTON = "expert";
	const std::string STR_INTER_BUTTON = "inter";
	const std::string STR_CONTINUE_BUTTON = "continue";
	const std::string STR_RETURN_BUTTON = "return";

	Slider slider_row;
	Slider slider_col;


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
	DifficultiesScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode()) : Scene(SceneType::Difficulties) {
		next_scene[GameEvent::NewGame] = SceneType::Playing;
		next_scene[GameEvent::QuitToMenu] = SceneType::Menu;

		buttons_event[STR_CONTINUE_BUTTON] = GameEvent::NewGame;
		buttons_event[STR_RETURN_BUTTON] = GameEvent::QuitToMenu;

		this->window_size = window_size;

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
					auto j = i; j++;
					for (; j != buttons.end(); j++) {
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

	int getCurrentRow() const;
	int getCurrentCol() const;

	DrawableList getDrawableList(const bool is_focusing = false, const int rank = 0) override;
};