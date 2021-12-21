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

#include "../Structs.h"
#include "../Constants.h"

using namespace std;

void TextColor(int color); 

char InttoChar(int k);

void insertArray(char* h, Timer* j); 

void WriteBlockChar(char* Arraych, int row, int col, int x, int y, int color);

void gotoXY(int column, int line); 

void displayClock();

void timer();

ostream&  operator << (ostream& outs, const Timer& thePlayer); 

ofstream& operator << (ofstream& outFile, const Timer& clock); 

ofstream& operator << (ofstream& outFile, const PLAYER& anObject); 

ofstream& operator << (ofstream& outFile, const GAMEPREDICATE& game_Feature); 

ofstream& operator << (ofstream& outFile, const GAMECELL& anObject);

ifstream& operator >> (ifstream& inFile, GAMEPREDICATE& game_Feature); 

ifstream& operator >> (ifstream& inFile, Timer& old_Clock);

ifstream& operator >> (ifstream& inFile, PLAYER& oldPlayer); 

ifstream& operator >> (ifstream& inFile, GAMECELL& anObject); 

ifstream& operator >> (ifstream& inFile, vector <PLAYER>& score_Board); 

void set_up_game(GAMEPREDICATE& game_Feature, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], int theRow, int theColumn, int max_Mine, int theFlags);

void mine_Level(int level, GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature, char mine_Board[][MAX_COLUMN],
	GAMECELL game_Board[][MAX_COLUMN]); 

bool isValid(int theRow, int theColumn, const GAMEPREDICATE& game_Feature); 

bool isMine(int theRow, int theColumn, char mine_Board[][MAX_COLUMN]); 

void mine_gameBoard_Count(int theRow, int theColumn, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature); 

int mine_Count(int theRow, int theColumn, const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN]); 

void mine_Create(const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], int theMines); 

void mine_board_Clear(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature); 

void printBoard(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature); 

void splash_Feature(int x, int y, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature); 

void inputChoice(int& theRow, int& theColumn, char& k, const GAMEPREDICATE& game_Feature);

bool isFull(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature);

void inputInfo(PLAYER& new_Player, PLAYER& old_Player); 

void mine_settingUp(int theLevel, const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN]); 

void auto_play(int& theRow, int& theColumn, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], GAMEPREDICATE game_Feature);

void mine_reserveData(const PLAYER& current_Player, PLAYER& old_Player, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature, Timer& old_Timers, const Timer& new_Timers);
void mine_updateData(char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN],
	GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature, Timer& new_Timers, Timer& old_Timers, PLAYER& new_Player, PLAYER& old_Player); 

void mine_Onscreen(char& theChoice, bool& isWin, bool Full, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN],
	GAMEPREDICATE& game_Feature, Timer& new_Timers, Timer& old_Timers); 

bool operator < (const PLAYER& first, const PLAYER& second); 

void addtoRecord(int theLevel, const PLAYER& newPlayer, Records& records);

void update_ScoreBoard(Records& records); 

void mine_Playgame(char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature,
	PLAYER& newPlayer, PLAYER& oldPlayer, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN],
	Timer& new_Timers, Timer& old_Timers); 


void mine_Loadgame(char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature,
	PLAYER& newPlayer, PLAYER& oldPlayer, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN],
	Timer& new_Timers, Timer& old_Timers); 

void welcomePlayer(int& choice); 

void implementChoice(int choice, char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature,
	PLAYER& newPlayer, PLAYER& oldPlayer, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN]);