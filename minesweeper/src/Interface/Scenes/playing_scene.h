#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"
#include "../Board/Board.h"


class PlayingScene : public Scene {
	friend class Window;

private:
	const std::string STR_TIMER = "timer";
	const std::string STR_RECORD = "record";

	const std::string STR_RETURN_BUTTON = "return";

	Board board;


	std::string timerStr(int h, int m, int s);
	std::string recordStr(int h, int m, int s);


	// OVERRIDING SCENE METHODS

	// Call on a mouse button event.
	// Returns corresponding GameEvent.
	GameEvent onMouseButtonReleased(const MouseActionType mouse_type) override;
	// Changes window graphics base on new mouse position.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos) override;

public:
	PlayingScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode(), const int board_rows = 0, const int board_cols = 0) : Scene(SceneType::Playing) {
		if (!checkBoardSize(window_size, board_rows, board_cols))
			return;

		next_scene[GameEvent::AutoOpenCell] = SceneType::Playing;
		next_scene[GameEvent::OpenCell] = SceneType::Playing;
		next_scene[GameEvent::FlagCell] = SceneType::Playing;
		next_scene[GameEvent::QuitToMenu] = SceneType::Menu;

		buttons_event[STR_RETURN_BUTTON] = GameEvent::QuitToMenu;

		this->window_size = window_size;

		// Board
		{
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
		}

		// Timer & Record
		{
			Text& timer = texts[STR_TIMER];
			timer.setText(timerStr(0, 0, 0));
			timer.setFontSize(DEFAULT_LARGE_FONT_SIZE);

			sf::Vector2f TL_timer;
			TL_timer.x = window_size.width * POS_COEF_TIMER.x;
			TL_timer.y = window_size.height * POS_COEF_TIMER.y;
			timer.setTopLeftPos(TL_timer);


			Text& record = texts[STR_RECORD];
			record.setText(recordStr(0, 0, 0));
			record.setFontSize(DEFAULT_LARGE_FONT_SIZE);

			sf::Vector2f TL_record;
			TL_record.x = window_size.width * POS_COEF_RECORD.x;
			TL_record.y = window_size.height * POS_COEF_RECORD.y;
			record.setTopLeftPos(TL_record);
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


	int getBoardRows() const;
	int getBoardCols() const;
	Position getLastPressedCell() const;

	// Checks if number of rows and cols of a board is valid for the window size.
	static bool checkBoardSize(const sf::VideoMode& window_size, const int board_rows, const int board_cols);

	DrawableList getDrawableList(const bool is_focusing = false, const int rank = 0) override;
};