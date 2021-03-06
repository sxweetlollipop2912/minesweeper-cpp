#include <iostream>

#include "menu_scene.h"


MenuScene::MenuScene(const sf::VideoMode& window_size) : Scene(window_size, SceneType::Menu) {
	next_scene[GameEvent::LoadGame] = SceneType::Playing;
	next_scene[GameEvent::ShowDifficulties] = SceneType::Difficulties;
	next_scene[GameEvent::ShowLeaderboard] = SceneType::Leaderboard;

	buttons_event[STR_LOAD_GAME] = GameEvent::LoadGame;
	buttons_event[STR_NEW_GAME] = GameEvent::ShowDifficulties;
	buttons_event[STR_LEADERBOARD] = GameEvent::ShowLeaderboard;
	buttons_event[STR_QUIT_GAME] = GameEvent::QuitGame;


	float pos_y_title = this->window_size.height * POS_Y_COEF_TITLE;
	float pos_y_load_game_button = this->window_size.height * POS_Y_COEF_LOAD_GAME_BUTTON;
	float pos_y_new_game_button = this->window_size.height * POS_Y_COEF_NEW_GAME_BUTTON;
	float pos_y_leaderboard_button = this->window_size.height * POS_Y_COEF_LEADERBOARD_BUTTON;
	float pos_y_quit_button = this->window_size.height * POS_Y_COEF_QUIT_BUTTON;

	Text& title = texts[TITLE];
	title.setText(TITLE);
	title.setFontSize(DEFAULT_TITLE_FONT_SIZE);
	title.setTopLeftPos(sf::Vector2f(0, pos_y_title));
	title.centerTextHorizontally(this->window_size.width);

	Button& load_game_button = buttons[STR_LOAD_GAME];
	load_game_button.setImage(TextureType::DefaultButton);
	load_game_button.label.setText("LOAD GAME");
	load_game_button.setTopLeftPos(sf::Vector2f(0, pos_y_load_game_button));
	load_game_button.alignImageAndText();

	Button& new_game_button = buttons[STR_NEW_GAME];
	new_game_button.setImage(TextureType::DefaultButton);
	new_game_button.label.setText("NEW GAME");
	new_game_button.setTopLeftPos(sf::Vector2f(0, pos_y_new_game_button));
	new_game_button.alignImageAndText();

	Button& leaderboard_button = buttons[STR_LEADERBOARD];
	leaderboard_button.setImage(TextureType::DefaultButton);
	leaderboard_button.label.setText("LEADERBOARD");
	leaderboard_button.setTopLeftPos(sf::Vector2f(0, pos_y_leaderboard_button));
	leaderboard_button.alignImageAndText();

	Button& quit_button = buttons[STR_QUIT_GAME];
	quit_button.setImage(TextureType::DefaultButton);
	quit_button.label.setText("QUIT");
	quit_button.setTopLeftPos(sf::Vector2f(0, pos_y_quit_button));
	quit_button.alignImageAndText();


	for (auto i = buttons.begin(); i != buttons.end(); i++) {
		if (i->first != STR_LOAD_GAME && i->first != STR_NEW_GAME && i->first != STR_LEADERBOARD && i->first != STR_QUIT_GAME)
			continue;

		auto j = i; j++;
		for (; j != buttons.end(); j++) {
			if (j->first != STR_LOAD_GAME && j->first != STR_NEW_GAME && j->first != STR_LEADERBOARD && j->first != STR_QUIT_GAME)
				continue;

			Button::equalizeButtonsSize(i->second, j->second);
		}
	}
	for (auto i = buttons.begin(); i != buttons.end(); i++) {
		if (i->first != STR_LOAD_GAME && i->first != STR_NEW_GAME && i->first != STR_LEADERBOARD && i->first != STR_QUIT_GAME)
			continue;

		i->second.centerButtonHorizontally(this->window_size.width);
	}
}