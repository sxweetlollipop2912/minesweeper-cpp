#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"
#include "../Board/Board.h"
#include "../../Structs.h"


class LeaderboardScene : public Scene {
	friend class Window;

private:
	const std::string STR_TITLE = "leaderboard";
	const std::string STR_BEGINNER_COL = "beginner";
	const std::string STR_INTER_COL = "inter";
	const std::string STR_EXPERT_COL = "expert";

	const std::string STR_RETURN_BUTTON = "return";

	std::shared_ptr<Records> records;


	std::string timeToStr(int h, int m, int s);

	// Call to update new records.
	void updateRecords(const std::shared_ptr<Records> records);

public:
	LeaderboardScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode()) : Scene(SceneType::Leaderboard) {
		next_scene[GameEvent::QuitToMenu] = SceneType::Menu;

		buttons_event[STR_RETURN_BUTTON] = GameEvent::QuitToMenu;

		this->window_size = window_size;

		// Texts
		{
			float pos_y_leaderboard_title = (float)this->window_size.height * POS_Y_COEF_LEADERBOARD_TITLE;
			float pos_y_col = this->window_size.height * POS_Y_COEF_COL;

			Text& title = texts[STR_TITLE];
			title.setText("Leaderboard");
			title.setFontSize(DEFAULT_TITLE_FONT_SIZE / 2);
			title.setTopLeftPosY(pos_y_leaderboard_title);
			title.centerTextHorizontally(this->window_size.width);

			float padding_x = this->window_size.width / (float)5;

			Text& beginner_col = texts[STR_BEGINNER_COL];
			beginner_col.setText("Beginner\n\n");
			beginner_col.setFontSize(DEFAULT_TITLE_FONT_SIZE / 3.5);
			beginner_col.setTopLeftPos(sf::Vector2f(padding_x, pos_y_col));

			Text& inter_col = texts[STR_INTER_COL];
			inter_col.setText("Intermediate\n\n");
			inter_col.setFontSize(DEFAULT_TITLE_FONT_SIZE / 3.5);
			inter_col.setTopLeftPosY(pos_y_col);
			inter_col.centerTextHorizontally(this->window_size.width);

			Text& expert_col = texts[STR_EXPERT_COL];
			expert_col.setText("Expert\n\n");
			expert_col.setFontSize(DEFAULT_TITLE_FONT_SIZE / 3.5);
			expert_col.setTopLeftPos(sf::Vector2f(this->window_size.width - padding_x - expert_col.getWidth(), pos_y_col));

			updateRecords(std::make_shared<Records>());
		}

		// Buttons
		{
			Button& return_button = buttons[STR_RETURN_BUTTON];
			return_button.setImage(TextureType::ButtonDefault);
			return_button.setPadding(sf::Vector2f(DEFAULT_PADDING_SIZE.x / 2, DEFAULT_PADDING_SIZE.y / 2));
			return_button.label.setText("Back to Menu");
			return_button.label.setFontSize(DEFAULT_SMALL_FONT_SIZE);
			return_button.alignImageAndText();
		}
	}
};