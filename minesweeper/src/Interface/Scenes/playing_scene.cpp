#include <iostream>

#include "playing_scene.h"


PlayingScene::PlayingScene(const sf::VideoMode& window_size, const int board_rows, const int board_cols) 
	: Scene(window_size, SceneType::Playing) {
	next_scene[GameEvent::AutoOpenCell] = SceneType::Playing;
	next_scene[GameEvent::OpenCell] = SceneType::Playing;
	next_scene[GameEvent::FlagCell] = SceneType::Playing;
	next_scene[GameEvent::QuitToMenu] = SceneType::Menu;

	buttons_event[STR_RETURN_BUTTON] = GameEvent::QuitToMenu;


	// Board
	{
		board = Board(board_rows, board_cols);
	}

	// Scoreboard
	{
		{
			Text& timer_label = texts[STR_TIMER_LABEL];
			timer_label.setText("Timer");
			timer_label.setFontSize(DEFAULT_LARGE_FONT_SIZE);
		}

		{
			Text& flag_label = texts[STR_FLAG_REMAINING_LABEL];
			flag_label.setText("Flags");
			flag_label.setFontSize(DEFAULT_LARGE_FONT_SIZE);
		}

		{
			Text& timer = texts[STR_TIMER];
			timer.setText(timerStr(0, 0, 0));
			timer.setFontSize(DEFAULT_LARGE_FONT_SIZE);
		}
		
		{
			Text& flag = texts[STR_FLAG_REMAINING];
			flag.setText(std::to_string(0));
			flag.setFontSize(DEFAULT_LARGE_FONT_SIZE);
		}

		{
			Button& scoreboard = buttons[STR_SCOREBOARD];
			scoreboard.setImage(TextureType::Scoreboard);

			sf::Vector2f scale_scoreboard;
			scale_scoreboard.x = scale_scoreboard.y = (window_size.height * SCOREBOARD_SIZE_Y_COEF) / scoreboard.getImageSize().y;
			scoreboard.setScale(scale_scoreboard);
		}
	}

	// Positioning board & scoreboard
	{
		Button& scoreboard = buttons[STR_SCOREBOARD];

		sf::Vector2f TL_area;
		TL_area.x = window_size.width * TOP_LEFT_COEF_BOARD_AREA.x;
		TL_area.y = window_size.height * TOP_LEFT_COEF_BOARD_AREA.y;
		sf::Vector2f RD_area;
		RD_area.x = window_size.width * RIGHT_DOWN_COEF_BOARD_AREA.x;
		RD_area.y = window_size.height * RIGHT_DOWN_COEF_BOARD_AREA.y;

		float space_x = window_size.width * SPAPCE_BETWEEN_BOARD_SCOREBOARD_X_COEF;

		float cell_size = (RD_area.x - TL_area.x - scoreboard.getSize().x - space_x) / board.number_of_cols;
		cell_size = std::min(cell_size, (RD_area.y - TL_area.y) / board.number_of_rows);
		cell_size = std::min(cell_size, MAX_CELL_SIZE);
		cell_size = std::max(cell_size, MIN_CELL_SIZE);
		board.setCellSize(cell_size);

		sf::Vector2f TL_board;
		TL_board.x = TL_area.x + ((RD_area.x - TL_area.x) - (cell_size * board.number_of_cols + space_x + scoreboard.getSize().x)) / (float)2;
		TL_board.y = TL_area.y + ((RD_area.y - TL_area.y) - (cell_size * board.number_of_rows)) / (float)2;
		board.setTopLeftPos(TL_board);


		sf::Vector2f TL_scoreboard;
		TL_scoreboard.y = board.getPosTopLeft().y;
		TL_scoreboard.x = board.getPosRightDown().x + space_x;
		setTopLeftPosScoreboard(TL_scoreboard);
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


std::string PlayingScene::timerStr(int h, int m, int s) {
	if (h < 0 || m < 0 || s < 0) return "-1";

	std::string str = "";
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


Result PlayingScene::updateBoard(const GAMECELL cell_board[][MAX_COLUMN], const char mine_board[][MAX_COLUMN], const int flag_remaining) {
	Text& flag = texts[STR_FLAG_REMAINING];
	flag.setText(std::to_string(flag_remaining));

	return board.updateBoard(cell_board, mine_board);
}


void PlayingScene::setTopLeftPosScoreboard(const sf::Vector2f top_left_pos) {
	Button& scoreboard = buttons[STR_SCOREBOARD];
	scoreboard.setTopLeftPos(top_left_pos);

	{
		Text& timer_label = texts[STR_TIMER_LABEL];

		sf::Vector2f TL_timer_label;
		TL_timer_label.x = scoreboard.getPosTopLeft().x + scoreboard.getSize().x * POS_COEF_SCOREBOARD_TIMER_LABEL_LD.x;
		TL_timer_label.y = scoreboard.getPosTopLeft().y + scoreboard.getSize().y * POS_COEF_SCOREBOARD_TIMER_LABEL_LD.y - timer_label.getHeight();
		timer_label.setTopLeftPos(TL_timer_label);
	}

	{
		Text& flag_label = texts[STR_FLAG_REMAINING_LABEL];

		sf::Vector2f TL_flag_label;
		TL_flag_label.x = scoreboard.getPosTopLeft().x + scoreboard.getSize().x * POS_COEF_SCOREBOARD_FLAG_LABEL_LD.x;
		TL_flag_label.y = scoreboard.getPosTopLeft().y + scoreboard.getSize().y * POS_COEF_SCOREBOARD_FLAG_LABEL_LD.y - flag_label.getHeight();
		flag_label.setTopLeftPos(TL_flag_label);
	}

	{
		Text& timer = texts[STR_TIMER];

		sf::Vector2f TL_timer;
		TL_timer.x = scoreboard.getPosTopLeft().x + scoreboard.getSize().x * POS_COEF_SCOREBOARD_TIMER.x;
		TL_timer.y = scoreboard.getPosTopLeft().y + scoreboard.getSize().y * POS_COEF_SCOREBOARD_TIMER.y;
		timer.setTopLeftPos(TL_timer);
	}

	{
		Text& flag = texts[STR_FLAG_REMAINING];

		sf::Vector2f TL_flag;
		TL_flag.x = scoreboard.getPosTopLeft().x + scoreboard.getSize().x * POS_COEF_SCOREBOARD_FLAG.x;
		TL_flag.y = scoreboard.getPosTopLeft().y + scoreboard.getSize().y * POS_COEF_SCOREBOARD_FLAG.y;
		flag.setTopLeftPos(TL_flag);
	}
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


void PlayingScene::draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing) {
	for (int i = 0; i < board.number_of_rows; i++) {
		for (int j = 0; j < board.number_of_cols; j++) {
			if (is_focusing && Position(i, j) == board.hovered_cell) {
				board.board[i][j].getHoveredSprite(sprite);
				renderer->draw(sprite);
			}
			else {
				board.board[i][j].getDefaultSprite(sprite);
				renderer->draw(sprite);
			}
		}
	}

	Scene::draw(renderer, is_focusing);
}
