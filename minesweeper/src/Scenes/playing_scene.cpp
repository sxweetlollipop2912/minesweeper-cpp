#include <iostream>
#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Board/Position.h"
#include "../Constants.h"
#include "playing_scene.h"


std::string PlayingScene::timerStr(int h, int m, int s) {
	if (h < 0 || m < 0 || s < 0) return "timer -1";

	std::string str = "timer ";
	std::string s_h, s_m, s_s;

	for (; h != 0; h /= 10) s_h += (char)('0' + (h % 10));
	while (s_h.size() < 1) s_h += "0";
	for (; m != 0; m /= 10) s_m += (char)('0' + (m % 10));
	while (s_m.size() < 2) s_m += "0";
	for (; s != 0; s /= 10) s_s += (char)('0' + (s % 10));
	while (s_s.size() < 2) s_s += "0";

	std::reverse(s_h.begin(), s_h.end());
	std::reverse(s_m.begin(), s_m.end());
	std::reverse(s_s.begin(), s_s.end());

	str += s_h + ":" + s_m + ":" + s_s;

	return str;
}


std::string PlayingScene::highscoreStr(int h, int m, int s) {
	if (h < 0 || m < 0 || s < 0) return "highscore -1";

	std::string str = "highscore ";
	std::string s_h, s_m, s_s;

	for (; h != 0; h /= 10) s_h += (char)('0' + (h % 10));
	while (s_h.size() < 1) s_h += "0";
	for (; m != 0; m /= 10) s_m += (char)('0' + (m % 10));
	while (s_m.size() < 2) s_m += "0";
	for (; s != 0; s /= 10) s_s += (char)('0' + (s % 10));
	while (s_s.size() < 2) s_s += "0";

	std::reverse(s_h.begin(), s_h.end());
	std::reverse(s_m.begin(), s_m.end());
	std::reverse(s_s.begin(), s_s.end());

	str += s_h + ":" + s_m + ":" + s_s;

	return str;
}


GameEvent PlayingScene::handleMouseButtonEvent(const MouseActionType mouse_type) {
	switch (mouse_type) {
		// RMB: Flag/Unflag a cell.
		case MouseActionType::RMB:
		{
			Position cell_pos = board.hovered_cell;

			if (!board.isValidPos(cell_pos))
				return GameEvent::Unknown;

			std::cout << "RMB " << cell_pos.r << ' ' << cell_pos.c << '\n';
		
			return GameEvent::FlagCell;
		}

		// LMB: Open a cell.
		case MouseActionType::LMB:
		{
			Position cell_pos = board.hovered_cell;

			if (!board.isValidPos(cell_pos))
				return GameEvent::Unknown;

			std::cout << "LMB " << cell_pos.r << ' ' << cell_pos.c << '\n';

			return GameEvent::OpenCell;
		}

		// Double-LMB: Auto-open nearby safe cells.
		case MouseActionType::DoubleLMB:
		{
			Position cell_pos = board.hovered_cell;

			if (!board.isValidPos(cell_pos))
				return GameEvent::Unknown;

			std::cout << "DoubleLMB " << cell_pos.r << ' ' << cell_pos.c << '\n';

			return GameEvent::AutoOpenCell;
		}
	}

	return GameEvent::Unknown;
}


bool PlayingScene::changeMousePosition(const sf::Vector2i& pos) {
	bool re = false;
	re |= Scene::changeMousePosition(pos);
	re |= board.determineHoveredCell(pos);

	return re;
}


void PlayingScene::initialize(const sf::Vector2u& window_size, const int board_rows, const int board_cols) {
	if (!checkBoardSize(window_size, board_rows, board_cols))
		return;

	this->Scene::Scene();
	
	next_scene[GameEvent::Playing] = SceneType::Playing;
	next_scene[GameEvent::Lost] = SceneType::Lost;
	next_scene[GameEvent::Won] = SceneType::Won;
	next_scene[GameEvent::QuitGame] = SceneType::Closing;
	next_scene[GameEvent::QuitToMenu] = SceneType::Menu;

	this->window_size = window_size;


	sf::Vector2f TL_board_area;
	TL_board_area.x = window_size.x * TOP_LEFT_COEF_BOARD_AREA.x;
	TL_board_area.y = window_size.y * TOP_LEFT_COEF_BOARD_AREA.y;
	sf::Vector2f RD_board_area;
	RD_board_area.x = window_size.x * RIGHT_DOWN_COEF_BOARD_AREA.x;
	RD_board_area.y = window_size.y * RIGHT_DOWN_COEF_BOARD_AREA.y;

	sf::Vector2f TL_board;
	TL_board.x = ((RD_board_area.x - TL_board_area.x) - (DEFAULT_CELL_AREA * board_cols)) / (float)2;
	TL_board.y = ((RD_board_area.y - TL_board_area.y) - (DEFAULT_CELL_AREA * board_rows)) / (float)2;
	
	board.initialize(board_rows, board_cols, TL_board);


	Text& timer = map_text[timer_str];
	timer.setText(timerStr(0, 0, 0));
	timer.setFontSize(DEFAULT_FONT_SIZE);

	sf::Vector2f TL_timer;
	TL_timer.x = window_size.x * POS_COEF_TIMER.x;
	TL_timer.y = window_size.y * POS_COEF_TIMER.y;
	timer.setTopLeftPosition(TL_timer);


	Text& highscore = map_text[highscore_str];
	highscore.setText(highscoreStr(0, 0, 0));
	highscore.setFontSize(DEFAULT_FONT_SIZE);

	sf::Vector2f TL_highscore;
	TL_highscore.x = window_size.x * POS_COEF_HIGHSCORE.x;
	TL_highscore.y = window_size.y * POS_COEF_HIGHSCORE.y;
	highscore.setTopLeftPosition(TL_highscore);
}


bool PlayingScene::checkBoardSize(const sf::Vector2u& window_size, const int board_rows, const int board_cols) {
	sf::Vector2f top_left_board_area;
	top_left_board_area.x = window_size.x * TOP_LEFT_COEF_BOARD_AREA.x;
	top_left_board_area.y = window_size.y * TOP_LEFT_COEF_BOARD_AREA.y;
	sf::Vector2f right_down_board_area;
	right_down_board_area.x = window_size.x * RIGHT_DOWN_COEF_BOARD_AREA.x;
	right_down_board_area.y = window_size.y * RIGHT_DOWN_COEF_BOARD_AREA.y;

	if (right_down_board_area.x - top_left_board_area.x < board_cols * DEFAULT_CELL_SIZE)
		return false;
	if (right_down_board_area.y - top_left_board_area.y < board_rows * DEFAULT_CELL_SIZE)
		return false;

	return true;
}
