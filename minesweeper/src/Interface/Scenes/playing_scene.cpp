#include <iostream>
#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Board/Position.h"
#include "../../Constants.h"
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


void PlayingScene::updateTimer(const Timer new_timer) {
	Text& timer = texts[STR_TIMER];
	timer.setText(timerStr(new_timer.hours, new_timer.minutes, new_timer.seconds));
}


GameEvent PlayingScene::onMouseButtonReleased(const MouseActionType mouse_type) {
	auto game_event = this->Scene::onMouseButtonReleased(mouse_type);

	if (game_event == GameEvent::Unknown && !pop_up) {
		// If mouse is hovering over a cell.
		if (board.isValidPos(board.hovered_cell)) {
			switch (mouse_type) {
				// RMB: Flag/Unflag a cell.
			case MouseActionType::RMB:
			{
				Position cell_pos = board.hovered_cell;
				std::cout << "RMB " << cell_pos.r << ' ' << cell_pos.c << '\n';

				return GameEvent::FlagCell;
			}
			// LMB: Open a cell.
			case MouseActionType::LMB:
			{
				Position cell_pos = board.hovered_cell;
				std::cout << "LMB " << cell_pos.r << ' ' << cell_pos.c << '\n';

				return GameEvent::OpenCell;
			}
			// Double-LMB: Auto-open nearby safe cells.
			case MouseActionType::DoubleLMB:
			{
				Position cell_pos = board.hovered_cell;
				std::cout << "DoubleLMB " << cell_pos.r << ' ' << cell_pos.c << '\n';

				return GameEvent::AutoOpenCell;
			}
			}
		}
	}

	return game_event;
}


bool PlayingScene::changeMousePosition(const sf::Vector2i& pos) {
	bool re = false;

	re |= Scene::changeMousePosition(pos);
	if (!pop_up) {
		re |= board.determineHoveredCell(pos);
	}
	else {
		board.hovered_cell = Position(-1, -1);
	}

	return re;
}


int PlayingScene::getBoardRows() const {
	return board.getRows();
}


int PlayingScene::getBoardCols() const {
	return board.getCols();
}

Position PlayingScene::getLastPressedCell() const {
	return board.getLastPressedCell();
}


bool PlayingScene::checkBoardSize(const sf::VideoMode& window_size, const int board_rows, const int board_cols) {
	sf::Vector2f top_left_board_area;
	top_left_board_area.x = window_size.width * TOP_LEFT_COEF_BOARD_AREA.x;
	top_left_board_area.y = window_size.height * TOP_LEFT_COEF_BOARD_AREA.y;
	sf::Vector2f right_down_board_area;
	right_down_board_area.x = window_size.width * RIGHT_DOWN_COEF_BOARD_AREA.x;
	right_down_board_area.y = window_size.height * RIGHT_DOWN_COEF_BOARD_AREA.y;

	if (right_down_board_area.x - top_left_board_area.x < board_cols * DEFAULT_CELL_SIZE)
		return false;
	if (right_down_board_area.y - top_left_board_area.y < board_rows * DEFAULT_CELL_SIZE)
		return false;

	return true;
}


Scene::DrawableList PlayingScene::getDrawableList(const bool is_focusing, const int rank) {
	DrawableList list;

	for (int i = 0; i < board.number_of_rows; i++) {
		for (int j = 0; j < board.number_of_cols; j++) {
			if (is_focusing && Position(i, j) == board.hovered_cell) {
				list.sprites.push_back(DrawableList::DrawableSprite(std::make_shared<sf::Sprite>(board.board[i][j].getHoveredSprite()), rank));
			}
			else {
				list.sprites.push_back(DrawableList::DrawableSprite(std::make_shared<sf::Sprite>(board.board[i][j].getDefaultSprite()), rank));
			}
		}
	}

	list.append(Scene::getDrawableList(is_focusing, rank));

	return list;
}
