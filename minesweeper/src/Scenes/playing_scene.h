#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Window/Window.h"
#include "../Scenes/scene.h"
#include "../Board/Board.h"


class PlayingScene : public Scene {
private:
	const std::string timer_str = "timer";
	const std::string highscore_str = "highscore";

	sf::Vector2u window_size;


	std::string timerStr(int h, int m, int s);
	std::string highscoreStr(int h, int m, int s);

public:
	PlayingScene(const sf::Vector2u& window_size, const int board_rows, const int board_cols) : Scene() {
		std::cout << "SCENE INTIING\n";
		if (!checkBoardSize(window_size, board_rows, board_cols))
			return;
		std::cout << "SCENE INTIING\n";

		next_scene[ButtonType::Board] = SceneType::Playing;
		next_scene[ButtonType::Quit] = SceneType::Closing;
		next_scene[ButtonType::Back] = SceneType::Menu;

		this->window_size = window_size;


		sf::Vector2f TL_board_area;
		TL_board_area.x = window_size.x * TOP_LEFT_COEF_BOARD_AREA.x;
		TL_board_area.y = window_size.y * TOP_LEFT_COEF_BOARD_AREA.y;
		sf::Vector2f RD_board_area;
		RD_board_area.x = window_size.x * RIGHT_DOWN_COEF_BOARD_AREA.x;
		RD_board_area.y = window_size.y * RIGHT_DOWN_COEF_BOARD_AREA.y;

		Button& board = map_button[ButtonType::Board];
		board = Board(board_rows, board_cols);

		sf::Vector2f TL_board;
		TL_board.x = ((RD_board_area.x - TL_board_area.x) - board.getSize().x) / (float)2;
		TL_board.y = ((RD_board_area.y - TL_board_area.y) - board.getSize().y) / (float)2;
		board.setTopLeftPosition(TL_board);


		Text& timer = map_text[timer_str];
		timer.setText(timerStr(0, 0, 0), DEFAULT_FONT_SIZE);

		sf::Vector2f TL_timer;
		TL_timer.x = window_size.x * POS_COEF_TIMER.x;
		TL_timer.y = window_size.y * POS_COEF_TIMER.y;
		timer.setTopLeftPosition(TL_timer);


		Text& highscore = map_text[highscore_str];
		highscore.setText(highscoreStr(0, 0, 0), DEFAULT_FONT_SIZE);

		sf::Vector2f TL_highscore;
		TL_highscore.x = window_size.x * POS_COEF_HIGHSCORE.x;
		TL_highscore.y = window_size.y * POS_COEF_HIGHSCORE.y;
		highscore.setTopLeftPosition(TL_highscore);
	}


	// Checks if number of rows and cols of a board is valid for the window size.
	static bool checkBoardSize(const sf::Vector2u& window_size, const int board_rows, const int board_cols);
};