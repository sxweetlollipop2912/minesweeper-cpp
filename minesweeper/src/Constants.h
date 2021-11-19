#pragma once

#include <SFML/Graphics.hpp>

// GAME_INFO
const std::string TITLE = "minesweeper";
const int MAX_COLUMN = 30;
const int MAX_ROW = 30;


// TEXT
const unsigned int DEFAULT_TITLE_FONT_SIZE = 40;
const unsigned int DEFAULT_FONT_SIZE = 15;
const std::string DEFAULT_FONT_PATH = "D:\\Music\\OneDrive - VNU-HCMUS\\Assignment Documents\\CS161 - Final Project\\minesweeper\\minesweeper\\assets\\fonts\\MochiyPopOne.ttf";


// COLOR
const sf::Color MAIN_COLOR = sf::Color::Blue;
const sf::Color SECONDARY_COLOR = sf::Color::Cyan;
const sf::Color DEFAULT_TEXT_COLOR = sf::Color::White;


// BUTTON
const sf::Vector2f DEFAULT_PADDING_SIZE = sf::Vector2f(10, 10);


// POSITION
// START SCENE
const float POS_Y_COEF_TITLE = 1 / (float)3;
const float POS_Y_COEF_START_BUTTON = 1 / (float)2;
const float pos_Y_COEF_QUIT_BUTTON = 5 / (float)8;
// BOARD
const int DEFAULT_CELL_SIZE = 30;
const float DEFAULT_CELL_AREA = DEFAULT_CELL_SIZE;// +(DEFAULT_CELL_SIZE / (float)7);
const sf::Vector2f TOP_LEFT_COEF_BOARD_AREA = sf::Vector2f(0, 0);
const sf::Vector2f RIGHT_DOWN_COEF_BOARD_AREA = sf::Vector2f(4 / (float)5, 1);
const sf::Vector2f POS_COEF_TIMER = sf::Vector2f(4 / (float)5, 1 / (float)3);
const sf::Vector2f POS_COEF_HIGHSCORE = sf::Vector2f(4 / (float)5, 2 / (float)5);


// IMAGE PATHS
const std::string BOARD_IMG_DIR = 
"D:\\Music\\OneDrive - VNU-HCMUS\\Assignment Documents\\CS161 - Final Project\\minesweeper\\minesweeper\\assets\\images\\board\\";
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
const std::string BLUE_BG_PATH = BOARD_IMG_DIR + (const std::string)"closed.png";