#pragma once

#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.h"
#include "../Board/Board.h"
#include "../Board/Position.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../../Structs.h"
#include "../../Constants.h"
#include "../../Enums.h"


class PlayingScene : public Scene {
	friend class Window;

private:
	const std::string STR_SCOREBOARD = "scoreboard";
	const std::string STR_TIMER_LABEL = "timer_label";
	const std::string STR_FLAG_REMAINING_LABEL = "flag_label";
	const std::string STR_TIMER = "timer";
	const std::string STR_FLAG_REMAINING = "flag";

	const std::string STR_RETURN_BUTTON = "return";

	Board board;


	std::string timerStr(int h, int m, int s);

	void updateTimer(const Timer timer);
	// Updates the grahics side of the board.
	// Returns Result::success / Result::failure:
	//	> success: board is successfully updated.
	//	> failure: board has not been changed after calling this method.
	// Regardless of the result, the board is up-to-date at return time.
	Result updateBoard(const GameCell cell_board[][MAX_COLUMN], const char mine_board[][MAX_COLUMN], const int flag_remaining);
	void setTopLeftPosScoreboard(const sf::Vector2f top_left_pos);


	// OVERRIDING SCENE METHODS

	// Call on a mouse button event.
	// Returns corresponding GameEvent.
	GameEvent onMouseButtonReleased(const MouseActionType mouse_type) override;
	// Changes window graphics base on new mouse position.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos) override;

public:
	PlayingScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode(), const int board_rows = 0, const int board_cols = 0);


	int getBoardRows() const;
	int getBoardCols() const;
	Position getLastPressedCell() const;

	// Checks if number of rows and cols of a board is valid for the window size.
	static bool checkBoardSize(const sf::VideoMode& window_size, const int board_rows, const int board_cols);

	DrawableList getDrawableList(const bool is_focusing = false, const int rank = 0) override;
};