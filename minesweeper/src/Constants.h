#pragma once

#include <set>

#include <SFML/Graphics.hpp>

#include "Structs.h"

const float EPS = 1e-7;
const sf::Time DOUBLE_CLICK_TIME_LIMIT = sf::milliseconds(200);

// GAME CONFIG
const std::string TITLE = "minesweeper";
const int MIN_COLUMN = 9;
const int MAX_COLUMN = 30;
const int MIN_ROW = 9;
const int MAX_ROW = 30;
const int BEGINNER_ROW = 9;
const int BEGINNER_COL = 9;
const int BEGINNER_MINE = 12;
const int INTERMEDIATE_ROW = 16;
const int INTERMEDIATE_COL = 16;
const int INTERMEDIATE_MINE = 40;
const int EXPERT_ROW = 16;
const int EXPERT_COL = 30;
const int EXPERT_MINE = 99;
const float CUSTOM_MINE_COEF = 0.2f;
const int MAX_RECORDS_PER_DIFF = 5;
const int MAX_SONGS = 15;

// DIRECTORIES
const std::string DATA_PATH = "./data/";
const std::string ASSET_PATH = "./assets/";
const std::string IMG_PATH = ASSET_PATH + (const std::string)"images/";
const std::string FONT_PATH = ASSET_PATH + (const std::string)"fonts/";
const std::string MUSIC_PATH = ASSET_PATH + (const std::string)"music/";

// SAVES
const std::string GAME_INFO_PATH = DATA_PATH + (const std::string)"game_info.txt";


// WINDOW
const sf::VideoMode DEFAULT_WINDOW_SIZE = sf::VideoMode(
        (sf::VideoMode().getDesktopMode().height * 1000 / (float)1080) * 1.5,
        sf::VideoMode().getDesktopMode().height * 1000 / (float)1080);


// TEXT
const int DEFAULT_LARGE_FONT_SIZE = DEFAULT_WINDOW_SIZE.height * 23 / (float)1000;
const int DEFAULT_NORMAL_FONT_SIZE = DEFAULT_LARGE_FONT_SIZE / 1.2;
const int DEFAULT_TITLE_FONT_SIZE = DEFAULT_LARGE_FONT_SIZE * 4.5;
const std::string DEFAULT_FONT_PATH = FONT_PATH + (const std::string)"MochiyPopOne.ttf";


// VISUAL
const int DEFAULT_TRANSPARENT_ALPHA_VALUE = 245;
const sf::Color HOVERED_COLOR = sf::Color(150, 150, 150);
const sf::Color DEFAULT_TEXT_COLOR = sf::Color(187, 187, 187);
const AudioVisualCfg::Cfg DEFAULT_VISUAL_CONFIG(sf::Color(17, 23, 29), sf::Color(47, 78, 107), sf::seconds(5), 225, sf::milliseconds(0));
const float BUBBLE_RADIUS = DEFAULT_WINDOW_SIZE.height * 150 / (float)1000;
const int NUMBER_OF_BUBBLES = 13;


// AUDIO_STUFF
const std::set <std::string> AUDIO_EXTENSIONS = { ".ogg",".wav",".flac" };
const std::string CFG_EXTENSION = ".cfg";
const std::string OPTION_VALUE_SEPARATOR = ":";
const std::string PRIMARY_COLOR_OPTION = "PrimaryColor";
const std::string SECONDARY_COLOR_OPTION = "SecondaryColor";
const std::string TRANSITION_DURATION_OPTION = "TransitionDuration";
const std::string BUBBLE_SPEED_OPTION = "BubbleSpeed";
const int MAX_CHAR_PER_LINE = 100;
const int MAX_LINE = 1000;
const sf::Time VOLUME_DOWN_TIME = sf::milliseconds(400);
const sf::Time VOLUME_CHANGING_TIME = sf::milliseconds(200);


// BUTTON
const sf::Vector2f DEFAULT_PADDING_SIZE = sf::Vector2f(
        DEFAULT_WINDOW_SIZE.width * 35 / (float)1500,
        DEFAULT_WINDOW_SIZE.height * 25 / (float)1000);


// POSITION AND SCALING
const sf::Vector2f RETURN_BUTTON_SIZE = sf::Vector2f(
        DEFAULT_WINDOW_SIZE.width * 60 / (float)1500,
        DEFAULT_WINDOW_SIZE.height * 60 / (float)1000);
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
const float POS_Y_COEF_SLIDER_COL = 4 / (float)7;
const float WIDTH_COEF_SLIDER = 180 / (float)1500;
const float HEIGHT_COEF_SLIDER = 7.5 / (float)1000;
// PLAYING SCENE
const float MIN_CELL_SIZE = DEFAULT_WINDOW_SIZE.height * 30 / (float)1500;
const float MAX_CELL_SIZE = DEFAULT_WINDOW_SIZE.width * 60 / (float)1500;
const sf::Vector2f TOP_LEFT_COEF_BOARD_AREA = sf::Vector2f((RETURN_BUTTON_SIZE.x * (const float)1.7f) / (float)DEFAULT_WINDOW_SIZE.width, 1 / (float)20);
const sf::Vector2f RIGHT_DOWN_COEF_BOARD_AREA = sf::Vector2f((DEFAULT_WINDOW_SIZE.width - (RETURN_BUTTON_SIZE.x * (const float)0.3f)) / (float)DEFAULT_WINDOW_SIZE.width, 19 / (float)20);
const float SPAPCE_BETWEEN_BOARD_SCOREBOARD_X_COEF = 1 / (float)40;
// SCOREBOARD
const float SCOREBOARD_SIZE_Y_COEF = 2 / (float)5;
const sf::Vector2f POS_COEF_SCOREBOARD_DIFFICULTY = sf::Vector2f(55 / (float)447, 80 / (float)600);
const sf::Vector2f POS_COEF_SCOREBOARD_TIMER_LABEL_LD = sf::Vector2f(55 / (float)447, (170 - 25) / (float)600);
const sf::Vector2f POS_COEF_SCOREBOARD_FLAG_LABEL_LD = sf::Vector2f(55 / (float)447, (401 - 25) / (float)600);
const sf::Vector2f POS_COEF_SCOREBOARD_TIMER = sf::Vector2f(70 / (float)447, (170 + 30) / (float)600);
const sf::Vector2f POS_COEF_SCOREBOARD_FLAG = sf::Vector2f(70 / (float)447, (401 + 30) / (float)600);
// LEADERBOARD
const float POS_Y_COEF_LEADERBOARD_TITLE = 1 / (float)8;
const float POS_Y_COEF_COL = 1 / (float)3;
// AUDIO
const float VOLUME_HEIGHT = 7 / (float)1000;
const float VOLUME_WIDTH = 150 / (float)1500;
const sf::Vector2f RIGHT_DOWN_COEF_VOLUME = sf::Vector2f((float)(DEFAULT_WINDOW_SIZE.width * 11 / (float)12) / (float)DEFAULT_WINDOW_SIZE.width, (float)(DEFAULT_WINDOW_SIZE.height * 15 / (float)17) / (float)DEFAULT_WINDOW_SIZE.height);
const float SPACE_Y_COEF_SKIP_SONG_AND_VOLUME = VOLUME_HEIGHT * (float)5;
const sf::Vector2f SKIP_SONG_SIZE = sf::Vector2f(
        DEFAULT_WINDOW_SIZE.width * 40 / (float)1500,
        DEFAULT_WINDOW_SIZE.height * 40 / (float)1000);



// BOARD IMAGE PATHS
const std::string BOARD_IMG_DIR = IMG_PATH + (const std::string)"board/";
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


// OTHER IMG PATHS
const std::string OTHER_IMG_DIR = IMG_PATH + (const std::string)"other/";
const std::string RETURN_BUTTON_PATH = OTHER_IMG_DIR + (const std::string)"return_button.png";
const std::string SKIP_SONG_BUTTON_PATH = OTHER_IMG_DIR + (const std::string)"skip.png";
const std::string YES_NO_BUTTON_PATH = OTHER_IMG_DIR + (const std::string)"yes_no_button.png";
const std::string POP_UP_BACKGROUND = OTHER_IMG_DIR + (const std::string)"pop_up_background.png";
const std::string DEFAULT_BUTTON_PATH = OTHER_IMG_DIR + (const std::string)"rect_button.png";