#include <iostream>
#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Text/Text.h"
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
