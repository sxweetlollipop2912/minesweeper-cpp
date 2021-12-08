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


class LeaderboardScene : public Scene {
	friend class Window;

private:
	const std::string STR_TITLE = "leaderboard";
	const std::string STR_BEGINNER_COL = "beginner";
	const std::string STR_INTER_COL = "inter";
	const std::string STR_EXPERT_COL = "expert";

	const std::string STR_RETURN_BUTTON = "return";

	std::shared_ptr<Records> records;


	std::string timeToStr(int h, int m, int s);

	// Call to update new records.
	void updateRecords(const std::shared_ptr<Records> records);

public:
	LeaderboardScene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode());
};