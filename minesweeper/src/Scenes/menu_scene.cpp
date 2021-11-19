#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "menu_scene.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Constants.h"


void MenuScene::initialize(const sf::Vector2u& window_size) {
	this->Scene::Scene();

	next_scene[ButtonType::Start] = SceneType::Playing;
	next_scene[ButtonType::Quit] = SceneType::Closing;

	this->window_size = window_size;

	float pos_y_title = window_size.y * POS_Y_COEF_TITLE;
	float pos_y_start_button = window_size.y * POS_Y_COEF_START_BUTTON;
	float pos_y_quit_button = window_size.y * pos_Y_COEF_QUIT_BUTTON;

	Text& title = map_text[TITLE];
	title.setText(TITLE, DEFAULT_TITLE_FONT_SIZE);
	title.setTopLeftPosition(sf::Vector2f(0, pos_y_title));
	title.centerTextHorizontally(window_size.x);

	Button& start_button = map_button[ButtonType::Start];
	start_button.setButtonType(ButtonType::Start);
	start_button.setImage(BLUE_BG_PATH, sf::Vector2f(0, pos_y_start_button));
	start_button.label.setText("START");
	start_button.alignImageAndText();

	Button& quit_button = map_button[ButtonType::Quit];
	quit_button.setButtonType(ButtonType::Quit);
	quit_button.setImage(BLUE_BG_PATH, sf::Vector2f(0, pos_y_quit_button));
	quit_button.label.setText("QUIT");
	quit_button.alignImageAndText();

	Button::equalizeButtonsSize(start_button, quit_button);
	quit_button.centerButtonHorizontally(window_size.x);
	start_button.centerButtonHorizontally(window_size.x);
}
