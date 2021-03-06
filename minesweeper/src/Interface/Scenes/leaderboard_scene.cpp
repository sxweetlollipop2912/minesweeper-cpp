#include <iostream>

#include "leaderboard_scene.h"


LeaderboardScene::LeaderboardScene(const sf::VideoMode& window_size) : Scene(window_size, SceneType::Leaderboard) {
	next_scene[GameEvent::QuitToMenu] = SceneType::Menu;

	buttons_event[STR_RETURN_BUTTON] = GameEvent::QuitToMenu;

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
		return_button.setImage(TextureType::ReturnButton);
		return_button.setSize(RETURN_BUTTON_SIZE);
		return_button.setTopLeftPosY(texts[STR_TITLE].getPosTopLeft().y);
		return_button.setTopLeftPosX(texts[STR_BEGINNER_COL].getPosTopLeft().x - return_button.getSize().x - (return_button.getSize().x / (float)2));
	}
}


std::string LeaderboardScene::timeToStr(int h, int m, int s) {
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


void LeaderboardScene::updateRecords(const std::shared_ptr<Records> records) {
	if (!records) {
		this->records = std::make_shared<Records>();
	}
	else {
		this->records = records;
	}

	std::string beginner = "Beginner\n\n";
	std::string inter = "Intermediate\n\n";
	std::string expert = "Expert\n\n";

	for (int i = 0; i < MAX_RECORDS_PER_DIFF; i++) {
		if (i < records->beginner.size()) {
			PLAYER player = records->beginner[i];
			beginner +=timeToStr(player.timePlay.hours, player.timePlay.minutes, player.timePlay.seconds) + '\n';
		}
		if (i < records->intermediate.size()) {
			PLAYER player = records->intermediate[i];
			inter += "       " + timeToStr(player.timePlay.hours, player.timePlay.minutes, player.timePlay.seconds) + '\n';
		}
		if (i < records->expert.size()) {
			PLAYER player = records->expert[i];
			expert += timeToStr(player.timePlay.hours, player.timePlay.minutes, player.timePlay.seconds) + '\n';
		}
	}

	texts[STR_BEGINNER_COL].setText(beginner);
	texts[STR_INTER_COL].setText(inter);
	texts[STR_EXPERT_COL].setText(expert);
}
