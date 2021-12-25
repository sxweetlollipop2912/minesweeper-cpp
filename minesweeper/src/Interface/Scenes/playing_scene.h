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
#include "../Timer/Timer.h"
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
	Position last_pressed_cell;
	Timer timer;


	std::string timerStr(int h, int m, int s);

	void setTopLeftPosScoreboard(const sf::Vector2f top_left_pos);

	void updateTimerStr(const Time timer);
	// Updates the grahics side of the board.
	// Returns Result::success / Result::failure:
	//	> success: board is successfully updated.
	//	> failure: board has not been changed after calling this method.
	// Regardless of the result, the board is up-to-date at return time.
	void resetTimer(const sf::Time timer_offset = sf::microseconds(0));
	Result updateBoard(const GAMECELL cell_board[][MAX_COLUMN], const char mine_board[][MAX_COLUMN], const int flag_remaining);


	// OVERRIDING SCENE METHODS

	// Call on a mouse button event.
	// Returns corresponding GameEvent.
	GameEvent onMouseButtonReleased(const MouseActionType mouse_type) override;
	// Changes window graphics base on new mouse position.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos) override;
	// Call on a lost window focus event.
	void onLostFocus() override;
	// Call on a gained window focus event.
	void onGainedFocus() override;
	// Call on every frame.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool updatePerFrame() override;

public:
	PlayingScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode(), const int board_rows = 0, const int board_cols = 0, const sf::Time timer_offset = sf::microseconds(0));


	int getBoardRows() const;
	int getBoardCols() const;
	Position getLastPressedCell() const;

	// Draws all textures and texts in the scene on an sf::RenderTarget object
	void draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing = true) override;
};