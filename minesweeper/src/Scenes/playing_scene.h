#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"
#include "../Board/Board.h"


class PlayingScene : public Scene {
	friend class Window;

private:
	const std::string timer_str = "timer";
	const std::string highscore_str = "highscore";

	Board board;


	std::string timerStr(int h, int m, int s);
	std::string highscoreStr(int h, int m, int s);


	// OVERRIDING SCENE METHODS

	// Call on a mouse button event.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	GameEvent handleMouseButtonEvent(const MouseActionType mouse_type) override;
	// Changes window graphics base on new mouse position.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos) override;

public:
	PlayingScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode(), const int board_rows = 0, const int board_cols = 0) {
		if (!checkBoardSize(window_size, board_rows, board_cols))
			return;

		next_scene[GameEvent::Playing] = SceneType::Playing;
		next_scene[GameEvent::Lost] = SceneType::Lost;
		next_scene[GameEvent::Won] = SceneType::Won;
		next_scene[GameEvent::QuitGame] = SceneType::Closing;
		next_scene[GameEvent::QuitToMenu] = SceneType::Menu;

		this->window_size = window_size;


		sf::Vector2f TL_board_area;
		TL_board_area.x = window_size.width * TOP_LEFT_COEF_BOARD_AREA.x;
		TL_board_area.y = window_size.height * TOP_LEFT_COEF_BOARD_AREA.y;
		sf::Vector2f RD_board_area;
		RD_board_area.x = window_size.width * RIGHT_DOWN_COEF_BOARD_AREA.x;
		RD_board_area.y = window_size.height * RIGHT_DOWN_COEF_BOARD_AREA.y;

		sf::Vector2f TL_board;
		TL_board.x = ((RD_board_area.x - TL_board_area.x) - (DEFAULT_CELL_AREA * board_cols)) / (float)2;
		TL_board.y = ((RD_board_area.y - TL_board_area.y) - (DEFAULT_CELL_AREA * board_rows)) / (float)2;

		board = Board(board_rows, board_cols, TL_board);

		Text& timer = map_text[timer_str];
		timer.setText(timerStr(0, 0, 0));
		timer.setFontSize(DEFAULT_FONT_SIZE);

		sf::Vector2f TL_timer;
		TL_timer.x = window_size.width * POS_COEF_TIMER.x;
		TL_timer.y = window_size.height * POS_COEF_TIMER.y;
		timer.setTopLeftPosition(TL_timer);


		Text& highscore = map_text[highscore_str];
		highscore.setText(highscoreStr(0, 0, 0));
		highscore.setFontSize(DEFAULT_FONT_SIZE);

		sf::Vector2f TL_highscore;
		TL_highscore.x = window_size.width * POS_COEF_HIGHSCORE.x;
		TL_highscore.y = window_size.height * POS_COEF_HIGHSCORE.y;
		highscore.setTopLeftPosition(TL_highscore);
	}


	int getBoardRows() const;
	int getBoardCols() const;
	// Checks if number of rows and cols of a board is valid for the window size.
	static bool checkBoardSize(const sf::Vector2u& window_size, const int board_rows, const int board_cols);
};