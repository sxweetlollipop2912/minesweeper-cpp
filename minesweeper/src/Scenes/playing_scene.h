#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Scenes/scene.h"
#include "../Board/Board.h"


class PlayingScene : public Scene {
	friend class Window;

private:
	const std::string timer_str = "timer";
	const std::string highscore_str = "highscore";

	sf::Vector2u window_size;

	Board board;

	std::string timerStr(int h, int m, int s);
	std::string highscoreStr(int h, int m, int s);


	// OVERRIDING SCENE METHODS
	bool changeMousePosition(const sf::Vector2i& pos) override;

	// Initializes PlayingScene object.
	void initialize(const sf::Vector2u& window_size, const int board_rows, const int board_cols);

public:
	PlayingScene() {
		int width = sf::VideoMode::getDesktopMode().width;
		int height = sf::VideoMode::getDesktopMode().height;

		initialize(window_size, 0, 0);
	}

	PlayingScene(const sf::Vector2u& window_size, const int board_rows, const int board_cols) {
		initialize(window_size, board_rows, board_cols);
	}


	// Checks if number of rows and cols of a board is valid for the window size.
	static bool checkBoardSize(const sf::Vector2u& window_size, const int board_rows, const int board_cols);
};