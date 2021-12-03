#pragma once

#include <SFML/Graphics.hpp>

// GAME_INFO
const std::string TITLE = "minesweeper";
const int MAX_COLUMN = 30;
const int MAX_ROW = 30;
const int MAX_RECORDS_PER_DIFF = 3;


// WINDOW
const sf::VideoMode DEFAULT_WINDOW_SIZE = sf::VideoMode(1500, 1000);


// TEXT
const int DEFAULT_LARGE_FONT_SIZE = 23;
const int DEFAULT_NORMAL_FONT_SIZE = DEFAULT_LARGE_FONT_SIZE / 1.2;
const int DEFAULT_SMALL_FONT_SIZE = DEFAULT_LARGE_FONT_SIZE / 1.5;
const int DEFAULT_TITLE_FONT_SIZE = DEFAULT_LARGE_FONT_SIZE * 4.5;
const std::string DEFAULT_FONT_PATH = ".\\assets\\fonts\\MochiyPopOne.ttf";


// COLOR
const sf::Color MAIN_COLOR = sf::Color::Blue;
const sf::Color SECONDARY_COLOR = sf::Color::Cyan;
const sf::Color DEFAULT_TEXT_COLOR = sf::Color::White;


// BUTTON
const sf::Vector2f DEFAULT_PADDING_SIZE = sf::Vector2f(15, 15);


// POSITION
// START SCENE
const float POS_Y_COEF_TITLE = 1 / (float)7;
const float SPACE_BETWEEN_BUTTONS_Y_COEF = 1 / (float)8;
const float POS_Y_COEF_LOAD_GAME_BUTTON = 3 / (float)7;
const float POS_Y_COEF_NEW_GAME_BUTTON = POS_Y_COEF_LOAD_GAME_BUTTON + SPACE_BETWEEN_BUTTONS_Y_COEF;
const float POS_Y_COEF_LEADERBOARD_BUTTON = POS_Y_COEF_NEW_GAME_BUTTON + SPACE_BETWEEN_BUTTONS_Y_COEF;
const float POS_Y_COEF_QUIT_BUTTON = POS_Y_COEF_LEADERBOARD_BUTTON + SPACE_BETWEEN_BUTTONS_Y_COEF;
// BOARD
const int DEFAULT_CELL_SIZE = 30;
const float DEFAULT_CELL_AREA = DEFAULT_CELL_SIZE;// + (DEFAULT_CELL_SIZE / (float)7);
const sf::Vector2f TOP_LEFT_COEF_BOARD_AREA = sf::Vector2f(0, 0);
const sf::Vector2f RIGHT_DOWN_COEF_BOARD_AREA = sf::Vector2f(4 / (float)5, 1);
const sf::Vector2f POS_COEF_TIMER = sf::Vector2f(4 / (float)5, 1 / (float)3);
const sf::Vector2f POS_COEF_RECORD = sf::Vector2f(4 / (float)5, 2 / (float)5);
// LEADERBOARD
const float POS_Y_COEF_LEADERBOARD_TITLE = 1 / (float)8;
const float POS_Y_COEF_COL = 1 / (float)3;


// IMAGE PATHS
const std::string BOARD_IMG_DIR = 
".\\assets\\images\\board\\";
const std::string CLOSED_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"closed.png";
const std::string BLANK_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"blank.png";
const std::string FLAGGED_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"flagged.png";
const std::string MINE_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"bomb_redbg.png";
const std::string NUM_1_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"num_1.png";
const std::string NUM_2_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"num_2.png";
const std::string NUM_3_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"num_3.png";
const std::string NUM_4_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"num_4.png";
const std::string NUM_5_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"num_5.png";
const std::string NUM_6_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"num_6.png";
const std::string NUM_7_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"num_7.png";
const std::string NUM_8_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"num_8.png";


// TEMP
const std::string DEFAULT_BUTTON_PATH = BOARD_IMG_DIR + (const std::string)"blank.png";