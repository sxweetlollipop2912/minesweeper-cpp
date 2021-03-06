#include <vector>

#include "GameTools.h"

Records records;
Time new_Timers = Time(0, 0, 0, false), old_Timers;


ostream& operator << (ostream& outs, const Time& clock) {
	outs << clock.hours << " " << clock.minutes << " " << clock.seconds;
	return outs;
}

ofstream& operator << (ofstream& outFile, const PLAYER& anObject) {
	outFile << anObject.timePlay << " " << anObject.level << endl;
	return outFile;
}

ofstream& operator << (ofstream& outFile, const GAMEPREDICATE& game_Feature) {
	outFile << game_Feature.flags << " " << game_Feature.MAX_COLUMN << " " << game_Feature.maxMine << " " << game_Feature.MAX_ROW
		<< " " << game_Feature.STOP;
	return outFile;
}

ofstream& operator << (ofstream& outFile, const GAMECELL& anObject) {
	outFile << anObject.isFlag << " " << anObject.isOpened << " " << anObject.mine_Count;
	return outFile;
}

ifstream& operator >> (ifstream& inFile, GAMEPREDICATE& game_Feature) {
	inFile >> game_Feature.flags >> game_Feature.MAX_COLUMN >> game_Feature.maxMine >> game_Feature.MAX_ROW >> game_Feature.STOP;
	return inFile;
}

ifstream& operator >> (ifstream& inFile, Time& old_Clock) {
	inFile >> old_Clock.hours >> old_Clock.minutes >> old_Clock.seconds;
	return inFile;
}

ifstream& operator >> (ifstream& inFile, PLAYER& oldPlayer) {
	inFile >> oldPlayer.timePlay >> oldPlayer.level;
	return inFile;
}

ifstream& operator >> (ifstream& inFile, GAMECELL& anObject) {
	inFile >> anObject.isFlag >> anObject.isOpened >> anObject.mine_Count;
	return inFile;
}

ifstream& operator >> (ifstream& inFile, vector <PLAYER>& score_Board) {
	score_Board.clear();

	PLAYER player;
	while (inFile >> player.timePlay >> player.level) {
		score_Board.push_back(player);
		inFile.ignore(1, '\n');
	}

	return inFile;
}


void set_opened(GAMECELL& cell, GAMEPREDICATE& game_Feature) {
	game_Feature.flags += cell.isFlag;
	cell.isFlag = false;
	cell.isOpened = true;
}

void set_flagged(GAMECELL& cell, GAMEPREDICATE& game_Feature) {
	game_Feature.flags -= !cell.isFlag;
	cell.isFlag = true;
	cell.isOpened = false;
}

void set_unflagged(GAMECELL& cell, GAMEPREDICATE& game_Feature) {
	game_Feature.flags += cell.isFlag;
	cell.isFlag = false;
	cell.isOpened = false;
}

void set_up_game(GAMEPREDICATE& game_Feature, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], int theRow, int theColumn, int max_Mine) {
	game_Feature.MAX_ROW = theRow;
	game_Feature.MAX_COLUMN = theColumn;
	game_Feature.flags = game_Feature.maxMine = max_Mine;
	mine_board_Clear(game_Board, mine_Board, game_Feature);
}

bool isValid(int theRow, int theColumn, const GAMEPREDICATE& game_Feature) {
	return (theRow >= 0 && theRow < game_Feature.MAX_ROW&& theColumn >= 0 && theColumn < game_Feature.MAX_COLUMN);
}


bool isMine(int theRow, int theColumn, char mine_Board[][MAX_COLUMN]) {
	return (theRow >= 0 && theRow < MAX_ROW) && (theColumn >= 0 && theColumn < MAX_COLUMN) && (mine_Board[theRow][theColumn] == '&');
}


void mine_gameBoard_Count(int theRow, int theColumn, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	if (!isValid(theRow, theColumn, game_Feature)) {
		cout << " ERROR: Illegal value input!";
		exit(1);
	}
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (isValid(theRow + i, theColumn + j, game_Feature)) {
				if (mine_Board[theRow + i][theColumn + j] == '&' && !isMine(theRow, theColumn, mine_Board)) {
					game_Board[theRow][theColumn].mine_Count += 1;
				}
			}
		}
	}

}


int mine_Count(int theRow, int theColumn, const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN]) {
	if (!isValid(theRow, theColumn, game_Feature)) {
		cout << " ERROR: Illegal value input!";
		exit(1);
	}
	int mine = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (isValid(theRow + i, theColumn + j, game_Feature)) {
				if (mine_Board[theRow + i][theColumn + j] == '&' && !isMine(theRow, theColumn, mine_Board)) {
					mine++;
				}
			}
		}
	}
	return mine;
}


void mine_Create(const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], int theMines) {
	int hasPlaced = 0; // The number of mines has been placed
	/*ofstream outFile(DATA_PATH + "marked_mines.txt", ios::app);
	if (outFile.fail()) {
		cout << " Cannot open marked_mines.";
		exit(1);
	}*/
	time_t t;
	srand((unsigned)time(&t)); // Activate the random number runner
	while (hasPlaced < theMines) {
		int x = rand() % (game_Feature.MAX_ROW);
		int y = rand() % (game_Feature.MAX_COLUMN);
		bool isLegal = true;

        if (isMine(x, y, mine_Board) || (x == 0 && y == 0)) {
            isLegal = false;
        }

		{
			int cnt_mine = 0;

			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if ((i != 0 || j != 0) && isValid(x + i, y + j, game_Feature)) {
						if (isMine(x + i, y + j, mine_Board)) {
							++cnt_mine;
						}
					}
				}
			}

			isLegal |= cnt_mine == 8;
		}

		if (isLegal) {
			mine_Board[x][y] = '&';
			//outFile << x << " " << y << endl;
			hasPlaced++;
		}
	}
	//outFile.close();
}


void mine_board_Clear(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			mine_Board[i][j] = '.';
			game_Board[i][j].isFlag = game_Board[i][j].isOpened = (game_Board[i][j]).mine_Count = 0;
		}
	}

	//ofstream outFile(DATA_PATH + "marked_mines.txt");
	//if (outFile.fail()) {
	//	cout << " Cannot open.";
	//	exit(1);
	//}
	////Clear the marked-mines TEXT FILE
	//outFile << "";
	//outFile.close();

}


void splash_Feature(int x, int y, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature) {
	set_opened(game_Board[x][y], game_Feature);

	if (game_Board[x][y].mine_Count == 0) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (i != 0 || j != 0) {
					if (isValid(x + i, y + j, game_Feature)) {
						if (!game_Board[x + i][y + j].isOpened && mine_Board[x + i][y + j] != '&')
							splash_Feature(x + i, y + j, game_Board, mine_Board, game_Feature);
					}
				}
			}
		}
	}
}

bool has_Won(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	bool won = false;

	if (game_Feature.flags == 0) {
		won = true;

		for (int i = 0; i < game_Feature.MAX_ROW && won; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN && won; j++) {
				if (isMine(i, j, mine_Board) && !game_Board[i][j].isFlag) {
					won = false;
				}
				if (!isMine(i, j, mine_Board) && game_Board[i][j].isFlag) {
					won = false;
				}
			}
		}
	}

	if (!won) {
		won = true;

		for (int i = 0; i < game_Feature.MAX_ROW && won; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN && won; j++) {
				if (!isMine(i, j, mine_Board) && !game_Board[i][j].isOpened) {
					won = false;
				}
			}
		}
	}

	return won;
}

void open_all_Cell(GAMECELL game_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature) {
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			game_Board[i][j].isOpened = true;
		}
	}
}

bool isFull(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			if (!game_Board[i][j].isOpened && mine_Board[i][j] != '&') {
				return false;
			}
		}
	}
	return true;
}

int count_Flags(int x, int y, GAMECELL game_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	int results = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i != 0 || j != 0) {
				if (isValid(x + i, y + j, game_Feature)) {
					if (game_Board[x + i][y + j].isFlag) {
						results++;
					}
				}
			}
		}
	}
	return results;
}

bool auto_open_Cell(int x, int y, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature) {
	if (!game_Board[x][y].isOpened) return true;

	if ((game_Board[x][y].mine_Count != 0) && (game_Board[x][y].mine_Count == count_Flags(x, y, game_Board, game_Feature))) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (i != 0 || j != 0) {
					if (isValid(x + i, y + j, game_Feature)) {
						if (!(game_Board[x + i][y + j].isOpened || game_Board[x + i][y + j].isFlag)) {
							//game_Board[x + i][y + j].isOpened = true;
							if (isMine(x + i, y + j, mine_Board)) {
								return false;
							}
							splash_Feature(x + i, y + j, game_Board, mine_Board, game_Feature);
						}
					}
				}
			}
		}
	}

	return true;
}

void mine_settingUp(int theLevel, const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN]) {
	switch (theLevel) {
	case (int)Difficulty::Beginner:
	{
		mine_Create(game_Feature, mine_Board, BEGINNER_MINE);
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				mine_gameBoard_Count(i, j, game_Board, mine_Board, game_Feature);
			}
		}
		break;
	}
	case (int)Difficulty::Intermediate:
	{
		mine_Create(game_Feature, mine_Board, INTERMEDIATE_MINE);
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				mine_gameBoard_Count(i, j, game_Board, mine_Board, game_Feature);
			}
		}
		break;
	}
	case (int)Difficulty::Expert:
	{
		mine_Create(game_Feature, mine_Board, EXPERT_MINE);
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				mine_gameBoard_Count(i, j, game_Board, mine_Board, game_Feature);
			}
		}
		break;
	}
	case (int)Difficulty::Custom:
	{
		mine_Create(game_Feature, mine_Board, (float)(game_Feature.MAX_ROW * game_Feature.MAX_COLUMN) * CUSTOM_MINE_COEF);
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				mine_gameBoard_Count(i, j, game_Board, mine_Board, game_Feature);
			}
		}
		break;
	}
	}
}


bool auto_play(int& theRow, int& theColumn, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], GAMEPREDICATE game_Feature) {

	do {
		theRow = rand() % (game_Feature.MAX_ROW);
		theColumn = rand() % (game_Feature.MAX_COLUMN);
	} while (game_Board[theRow][theColumn].isOpened || game_Board[theRow][theColumn].isFlag);

	if (isMine(theRow, theColumn, mine_Board)) {
		return false;
	}

	game_Board[theRow][theColumn].isOpened = true;
	return true;

}


void mine_reserveData(const PLAYER& current_Player, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature, const Time& new_Timers) {
	ofstream outFile(DATA_PATH + "last_Gameboard.txt");
	if (outFile.fail()) {
		cout << " Cannot open last_Gameboard";
		exit(1);
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			outFile << game_Board[i][j] << endl;
		}
	}
	outFile.close();

	outFile.open(DATA_PATH + "last_mineBoard.txt");
	if (outFile.fail()) {
		cout << " Cannot open old_mineBoard";
		exit(1);
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			outFile << mine_Board[i][j];
		}
	}
	outFile.close();

	outFile.open(DATA_PATH + "last_Clock.txt");
	if (outFile.fail()) {
		cout << " Cannot open last_Clock";
		exit(1);
	}
	outFile << new_Timers;
	outFile.close();

	outFile.open(DATA_PATH + "last_Gamefeature.txt");
	if (outFile.fail()) {
		cout << " Cannot open Game_Feature";
		exit(1);
	}
	outFile << game_Feature;
	outFile.close();

	outFile.open(DATA_PATH + "last_Player.txt");
	if (outFile.fail()) {
		cout << " ERROR: Cannot open Information.";
		exit(1);
	}
	outFile << current_Player;
	outFile.close();

}


bool mine_updateData(char mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, PLAYER& new_Player) {
	ifstream inFile(DATA_PATH + "last_Gamefeature.txt");
	if (inFile.fail() || inFile.peek() == std::ifstream::traits_type::eof()) {
		cout << " Cannot open last_Gamefeature";
		return false;
	}
	inFile >> game_Feature;
	inFile.close();

	inFile.open(DATA_PATH + "last_Gameboard.txt");
	if (inFile.fail() || inFile.peek() == std::ifstream::traits_type::eof()) {
		cout << " Cannot open last_Gamefeature";
		return false;
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			inFile >> game_Board[i][j];
			inFile.ignore(1, '\n');
		}
	}
	inFile.close();

	inFile.open(DATA_PATH + "last_Mineboard.txt");
	if (inFile.fail() || inFile.peek() == std::ifstream::traits_type::eof()) {
		cout << " Cannot open last_Gamefeature";
		return false;
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			inFile >> mine_Board[i][j];
		}
	}
	inFile.close();

	inFile.open(DATA_PATH + "last_Player.txt");
	if (inFile.fail() || inFile.peek() == std::ifstream::traits_type::eof()) {
		cout << " Cannot open last_Gamefeature";
		return false;
	}
	inFile >> new_Player;
	inFile.close();

	return true;
}


bool operator < (const PLAYER& first, const PLAYER& second) {
	int a = first.timePlay.hours * 3600 + first.timePlay.minutes * 60 + first.timePlay.seconds;
	int b = second.timePlay.hours * 3600 + second.timePlay.minutes * 60 + second.timePlay.seconds;
	return (a < b);
}


void addtoRecord(int theLevel, const PLAYER& newPlayer, Records& records) {
	switch (theLevel) {
	case (int)Difficulty::Beginner:
	{
		records.beginner.push_back(newPlayer);
		sort(records.beginner.begin(), records.beginner.end());
		break;
	}
	case (int)Difficulty::Intermediate:
	{
		records.intermediate.push_back(newPlayer);
		sort(records.intermediate.begin(), records.intermediate.end());
		break;
	}
	case (int)Difficulty::Expert:
	{
		records.expert.push_back(newPlayer);
		sort(records.expert.begin(), records.expert.end());
		break;
	}
	}
}


void update_ScoreBoard(Records& record) {

	ifstream file1(DATA_PATH + "beginner_records.txt"),
		file2(DATA_PATH + "intermediate_records.txt"),
		file3(DATA_PATH + "expert_records.txt");
	if (file1.fail() || file2.fail() || file3.fail()) {
		cout << " ERROR: cannot open inFile.";
		exit(1);
	}

	file1 >> records.beginner;
	file2 >> records.intermediate;
	file3 >> records.expert;
	file1.close();
	file2.close();
	file3.close();
}



