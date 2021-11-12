#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Window/Window.h"
#include "../Scenes/scene.h"


class MenuScene : public Scene {
private:
	const std::string title_str = "minesweeper";

	const float pos_y_coef_title = 1 / (float)3;
	const float pos_y_coef_start_button = 1 / (float)2;
	const float pos_y_coef_quit_button = 5 / (float)8;

	sf::Vector2u window_size;

public:
	MenuScene(const sf::Vector2u& window_size) {
		map_button.clear();
		map_text.clear();
		texture_path.clear();

		this->window_size = window_size;

		float pos_y_title = window_size.y * pos_y_coef_title;
		float pos_y_start_button = window_size.y * pos_y_coef_start_button;
		float pos_y_quit_button = window_size.y * pos_y_coef_quit_button;

		Text title;
		title.setText(title_str, DEFAULT_FONT_SIZE * 2);
		title.setTopLeftPosition(sf::Vector2f(0, pos_y_title));
		title.centerTextHorizontally(window_size.x);

		map_text[title_str] = title;

		Button start_button;
		start_button.setButtonType(ButtonType::Start);
		start_button.setImage(BLUE_BG_PATH, sf::Vector2f(0, pos_y_start_button));
		start_button.label.setText("START");
		start_button.alignImageAndText();

		Button quit_button;
		quit_button.setButtonType(ButtonType::Quit);
		quit_button.setImage(BLUE_BG_PATH, sf::Vector2f(0, pos_y_quit_button));
		quit_button.label.setText("QUIT");
		quit_button.alignImageAndText();

		Button::equalizeButtonsSize(start_button, quit_button);
		quit_button.centerButtonHorizontally(window_size.x);
		start_button.centerButtonHorizontally(window_size.x);

		map_button[start_button.getButtonType()] = start_button;
		map_button[quit_button.getButtonType()] = quit_button;
	}
};