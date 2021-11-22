#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "menu_scene.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Constants.h"


void MenuScene::initialize(const sf::Vector2u& window_size) {
	this->Scene::Scene();

	next_scene[GameEvent::LoadGame] = SceneType::Playing;
	next_scene[GameEvent::NewGame] = SceneType::Playing;
	next_scene[GameEvent::QuitGame] = SceneType::Closing;

	this->window_size = window_size;

	float pos_y_title = window_size.y * POS_Y_COEF_TITLE;
	float pos_y_load_game_button = window_size.y * POS_Y_COEF_LOAD_GAME_BUTTON;
	float pos_y_new_game_button = window_size.y * POS_Y_COEF_NEW_GAME_BUTTON;
	float pos_y_quit_button = window_size.y * pos_Y_COEF_QUIT_BUTTON;

	Text& title = map_text[TITLE];
	title.setText(TITLE);
	title.setFontSize(DEFAULT_TITLE_FONT_SIZE);
	title.setTopLeftPosition(sf::Vector2f(0, pos_y_title));
	title.centerTextHorizontally(window_size.x);

	Button& load_game_button = map_button[GameEvent::LoadGame];
	load_game_button.setImage(TextureType::ButtonDefault, sf::Vector2f(0, pos_y_load_game_button));
	load_game_button.label.setText("LOAD GAME");
	load_game_button.alignImageAndText();

	Button& new_game_button = map_button[GameEvent::NewGame];
	new_game_button.setImage(TextureType::ButtonDefault, sf::Vector2f(0, pos_y_new_game_button));
	new_game_button.label.setText("NEW GAME");
	new_game_button.alignImageAndText();

	Button& quit_button = map_button[GameEvent::QuitGame];
	quit_button.setImage(TextureType::ButtonDefault, sf::Vector2f(0, pos_y_quit_button));
	quit_button.label.setText("QUIT");
	quit_button.alignImageAndText();

	Button::equalizeButtonsSize(start_button, quit_button);
	quit_button.centerButtonHorizontally(window_size.x);
	start_button.centerButtonHorizontally(window_size.x);
}
