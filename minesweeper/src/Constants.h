#pragma once

#include <SFML/Graphics.hpp>

const float EPS = 1e-7;

// GAME
const std::string TITLE = "minesweeper";
const int MIN_COLUMN = 9;
const int MAX_COLUMN = 30;
const int MIN_ROW = 9;
const int MAX_ROW = 30;
const int BEGINNER_ROW = 9;
const int BEGINNER_COL = 9;
const int INTERMEDIATE_ROW = 16;
const int INTERMEDIATE_COL = 16;
const int EXPERT_ROW = 16;
const int EXPERT_COL = 30;
const int MAX_RECORDS_PER_DIFF = 3;
const int MAX_SONGS = 2;

// PATH
const std::string DATA_PATH = ".\\data\\";
const std::string ASSET_PATH = ".\\assets\\";
const std::string IMG_PATH = ASSET_PATH + (const std::string)"images\\";
const std::string FONT_PATH = ASSET_PATH + (const std::string)"fonts\\";
const std::string MUSIC_PATH = ASSET_PATH + (const std::string)"music\\";


// WINDOW
const sf::VideoMode DEFAULT_WINDOW_SIZE = sf::VideoMode(1500, 1000);


// TEXT
const int DEFAULT_LARGE_FONT_SIZE = 23;
const int DEFAULT_NORMAL_FONT_SIZE = DEFAULT_LARGE_FONT_SIZE / 1.2;
const int DEFAULT_SMALL_FONT_SIZE = DEFAULT_LARGE_FONT_SIZE / 1.5;
const int DEFAULT_TITLE_FONT_SIZE = DEFAULT_LARGE_FONT_SIZE * 4.5;
const std::string DEFAULT_FONT_PATH = FONT_PATH + (const std::string)"MochiyPopOne.ttf";


// COLOR
const sf::Color BACKGROUMD_COLOR = sf::Color(245, 245, 245);
const sf::Color DEFAULT_TEXT_COLOR = sf::Color::White;


// BUTTON
const sf::Vector2f DEFAULT_PADDING_SIZE = sf::Vector2f(50, 25);


// POSITION
// START SCENE
const float POS_Y_COEF_TITLE = 1 / (float)7;
const float SPACE_BETWEEN_BUTTONS_Y_COEF = 2 / (float)17;
const float POS_Y_COEF_LOAD_GAME_BUTTON = 55 / (float)140;
const float POS_Y_COEF_NEW_GAME_BUTTON = POS_Y_COEF_LOAD_GAME_BUTTON + SPACE_BETWEEN_BUTTONS_Y_COEF;
const float POS_Y_COEF_LEADERBOARD_BUTTON = POS_Y_COEF_NEW_GAME_BUTTON + SPACE_BETWEEN_BUTTONS_Y_COEF;
const float POS_Y_COEF_QUIT_BUTTON = POS_Y_COEF_LEADERBOARD_BUTTON + SPACE_BETWEEN_BUTTONS_Y_COEF;
// DIFFICULTIES SCENE
const float POS_Y_COEF_DIFF_BUTTON = 3 / (float)12;
const float POS_Y_COEF_CONTINUE_BUTTON = 4 / (float)6;
const float POS_Y_COEF_SLIDER_ROW = 3 / (float)7;
const float POS_Y_COEF_SLODER_COL = 4 / (float)7;
// PLAYING SCENE
const float MIN_CELL_SIZE = 30;
const float MAX_CELL_SIZE = 55;
const sf::Vector2f TOP_LEFT_COEF_BOARD_AREA = sf::Vector2f(1 / (float)30, 1 / (float)20);
const sf::Vector2f RIGHT_DOWN_COEF_BOARD_AREA = sf::Vector2f(29 / (float)30, 19 / (float)20);
const float SPAPCE_BETWEEN_BOARD_SCOREBOARD_X_COEF = 1 / (float)40;
// SCOREBOARD
const float SCOREBOARD_SIZE_Y_COEF = 2 / (float)5;
const sf::Vector2f POS_COEF_SCOREBOARD_DIFFICULTY = sf::Vector2f(55 / (float)447, 70 / (float)600);
const sf::Vector2f POS_COEF_SCOREBOARD_TIMER_LABEL_LD = sf::Vector2f(55 / (float)447, (170 - 25) / (float)600);
const sf::Vector2f POS_COEF_SCOREBOARD_FLAG_LABEL_LD = sf::Vector2f(55 / (float)447, (401 - 25) / (float)600);
const sf::Vector2f POS_COEF_SCOREBOARD_TIMER = sf::Vector2f(70 / (float)447, (170 + 30) / (float)600);
const sf::Vector2f POS_COEF_SCOREBOARD_FLAG = sf::Vector2f(70 / (float)447, (401 + 30) / (float)600);
// LEADERBOARD
const float POS_Y_COEF_LEADERBOARD_TITLE = 1 / (float)8;
const float POS_Y_COEF_COL = 1 / (float)3;
// AUDIO
const sf::Vector2f RIGHT_DOWN_COEF_NEXT_SONG = RIGHT_DOWN_COEF_BOARD_AREA;
const sf::Vector2f NEXT_SONG_SIZE = sf::Vector2f(40, 40);


// IMAGE PATHS
const std::string BOARD_IMG_DIR = IMG_PATH + (const std::string)"board\\";
const std::string SCOREBOARD_IMG_PATH = BOARD_IMG_DIR + (const std::string)"scoreboard.png";
const std::string CLOSED_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"closed.png";
const std::string BLANK_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"blank.png";
const std::string FLAGGED_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"flagged.png";
const std::string MINE_CELL_IMG_PATH = BOARD_IMG_DIR + (const std::string)"bomb.png";
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