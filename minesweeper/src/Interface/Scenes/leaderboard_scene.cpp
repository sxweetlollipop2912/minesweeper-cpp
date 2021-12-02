#include <iostream>
#include <algorithm>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "leaderboard_scene.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Board/Position.h"
#include "../../Constants.h"
#include "../../Structs.h"


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
			beginner += timeToStr(player.timePlay.hours, player.timePlay.minutes, player.timePlay.seconds) + '\n';
		}
		if (i < records->intermediate.size()) {
			PLAYER player = records->intermediate[i];
			inter += timeToStr(player.timePlay.hours, player.timePlay.minutes, player.timePlay.seconds) + '\n';
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
