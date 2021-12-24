#pragma once

// This is to prevent #include<Windows.h> from overwriting std::min and std::max from #include <algorithm>.
// Required by SFML.
#define NOMINMAX

#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<thread>
#include<vector>
#include<algorithm>
#include<fstream>
#include<Windows.h>
#include<conio.h>

#include "../Enums.h"
#include "../Structs.h"
#include "../Constants.h"

using namespace std;

void TextColor(int color);

char InttoChar(int k);

void insertArray(char* h, Time* j);

void WriteBlockChar(char* Arraych, int row, int col, int x, int y, int color);

void gotoXY(int column, int line);

void displayClock();

void timer();

ostream& operator << (ostream& outs, const Time& clock);

ofstream& operator << (ofstream& outFile, const PLAYER& anObject);

ofstream& operator << (ofstream& outFile, const GAMEPREDICATE& game_Feature);

ofstream& operator << (ofstream& outFile, const GAMECELL& anObject);

ifstream& operator >> (ifstream& inFile, GAMEPREDICATE& game_Feature);

ifstream& operator >> (ifstream& inFile, Time& old_Clock);

ifstream& operator >> (ifstream& inFile, PLAYER& oldPlayer);

ifstream& operator >> (ifstream& inFile, GAMECELL& anObject);

ifstream& operator >> (ifstream& inFile, vector <PLAYER>& score_Board);

void set_up_game(GAMEPREDICATE& game_Feature, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], int theRow, int theColumn, int max_Mine);

bool isValid(int theRow, int theColumn, const GAMEPREDICATE& game_Feature);

bool isMine(int theRow, int theColumn, char mine_Board[][MAX_COLUMN]);

void mine_gameBoard_Count(int theRow, int theColumn, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

int mine_Count(int theRow, int theColumn, const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN]);

void mine_Create(const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], int theMines);

void mine_board_Clear(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

int fully_Flagged(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

void open_all_Cell(GAMECELL game_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

void splash_Feature(int x, int y, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

int count_Flags(int x, int y, GAMECELL game_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

bool auto_open_Cell(int x, int y, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

bool isFull(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

void mine_settingUp(int theLevel, const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN]);

bool auto_play(int& theRow, int& theColumn, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], GAMEPREDICATE game_Feature);

void mine_reserveData(const PLAYER& current_Player, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature, const Time& new_Timers);

bool mine_updateData(char mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, /*Time& new_Timers,*/ PLAYER& new_Player);

bool operator < (const PLAYER& first, const PLAYER& second);

void addtoRecord(int theLevel, const PLAYER& newPlayer, Records& records);

void update_ScoreBoard(Records& records);
