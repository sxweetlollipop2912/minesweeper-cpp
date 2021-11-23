#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"


class MenuScene : public Scene {
	friend class Window;

private:

	// OVERRIDING METHODS

	// Call on a mouse button event.
	GameEvent handleMouseButtonEvent(const MouseActionType mouse_type) override;

public:
	MenuScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode()) {
		next_scene[GameEvent::LoadGame] = SceneType::Playing;
		next_scene[GameEvent::NewGame] = SceneType::Playing;
		next_scene[GameEvent::QuitGame] = SceneType::Closing;

		this->window_size = window_size;


		float pos_y_title = this->window_size.height * POS_Y_COEF_TITLE;
		float pos_y_load_game_button = this->window_size.height * POS_Y_COEF_LOAD_GAME_BUTTON;
		float pos_y_new_game_button = this->window_size.height * POS_Y_COEF_NEW_GAME_BUTTON;
		float pos_y_quit_button = this->window_size.height * pos_Y_COEF_QUIT_BUTTON;

		Text& title = map_text[TITLE];
		title.setText(TITLE);
		title.setFontSize(DEFAULT_TITLE_FONT_SIZE);
		title.setTopLeftPosition(sf::Vector2f(0, pos_y_title));
		title.centerTextHorizontally(this->window_size.width);

		Button& load_game_button = map_button[GameEvent::LoadGame];
		load_game_button.setImage(TextureType::ButtonDefault);
		load_game_button.label.setText("LOAD GAME");
		load_game_button.setTopLeftPosition(sf::Vector2f(0, pos_y_load_game_button));
		load_game_button.alignImageAndText();

		Button& new_game_button = map_button[GameEvent::NewGame];
		new_game_button.setImage(TextureType::ButtonDefault);
		new_game_button.label.setText("NEW GAME");
		new_game_button.setTopLeftPosition(sf::Vector2f(0, pos_y_new_game_button));
		new_game_button.alignImageAndText();

		Button& quit_button = map_button[GameEvent::QuitGame];
		quit_button.setImage(TextureType::ButtonDefault);
		quit_button.label.setText("QUIT");
		quit_button.setTopLeftPosition(sf::Vector2f(0, pos_y_quit_button));
		quit_button.alignImageAndText();


		for (auto i = map_button.begin(); i != map_button.end(); i++) {
			auto j = i; j++;
			for (; j != map_button.end(); j++) {
				Button::equalizeButtonsSize(i->second, j->second);
			}
		}
		for (auto i = map_button.begin(); i != map_button.end(); i++) {
			i->second.centerButtonHorizontally(this->window_size.width);
		}
	}
};