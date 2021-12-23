#include <vector>

#include "GameTools.h"
#include "../Structs.h"
#include "../Constants.h"

Records records;
Timer new_Timers = { 0,0,0,0 }, old_Timers;

void TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

char InttoChar(int k) {
	switch (k) {
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	default: break;
	}
}

void insertArray(char* h, Timer* j) {
	int balt = 0;
	char u;
	balt = j->seconds;
	h[7] = InttoChar(balt % 10);
	h[6] = InttoChar(balt /= 10);
	balt = j->minutes;
	h[4] = InttoChar(balt % 10);
	h[3] = InttoChar(balt /= 10);
	balt = j->hours;
	h[1] = InttoChar(balt % 10);
	h[0] = InttoChar(balt /= 10);
}


void WriteBlockChar(char* Arraych, int row, int col, int x, int y, int color) {
	CHAR_INFO* character = new CHAR_INFO[row * col];
	for (int i = 0; i < row * col; i++) {
		character[i].Attributes = color;
		character[i].Char.UnicodeChar = Arraych[i];
	}
	COORD sizebuff = { col,row };
	COORD pos = { 0,0 };
	SMALL_RECT earea = { x,y,x + col - 1,y + row - 1 };
	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), character, sizebuff, pos, &earea);
	delete[] character;
}


void gotoXY(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// function to display the timer
void displayClock()
{
	char a[8] = { '0','0',':','0','0',':','0','0' };
	insertArray(a, &new_Timers);
	WriteBlockChar(a, 1, 8, 70, 3, 0x004);
}

void timer()
{
	while (!new_Timers.STOP) {

		// display the timer
		displayClock();

		// sleep system call to sleep
		// for 1 second

		// increment seconds
		new_Timers.seconds++;

		// if seconds reaches 60
		if (new_Timers.seconds == 60) {

			// increment minutes
			new_Timers.minutes++;

			// if minutes reaches 60
			if (new_Timers.minutes == 60) {

				// increment hours
				new_Timers.hours++;
				new_Timers.minutes = 0;
			}
			new_Timers.seconds = 0;
		}
		Sleep(1100);
	}
}

ostream& operator <<(ostream& outs, const Timer& thePlayer) {
	if (thePlayer.hours < 10) {
		outs << "0";
	}
	outs << thePlayer.hours << ":";
	if (thePlayer.minutes < 10) {
		outs << "0";
	}
	outs << thePlayer.minutes << ":";
	if (thePlayer.seconds < 10) {
		outs << "0";
	}
	outs << thePlayer.seconds;
	return outs;
}

ofstream& operator << (ofstream& outFile, const Timer& clock) {
	outFile << clock.hours << " " << clock.minutes << " " << clock.seconds;
	return outFile;
}

ofstream& operator << (ofstream& outFile, const PLAYER& anObject) {
	outFile << anObject.timePlay << " " << anObject.level <<  endl;
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

ifstream& operator >> (ifstream& inFile, Timer& old_Clock) {
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

void set_up_game(GAMEPREDICATE& game_Feature, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], int theRow, int theColumn, int max_Mine, int theFlags) {
	game_Feature.MAX_ROW = theRow;
	game_Feature.MAX_COLUMN = theColumn;
	game_Feature.maxMine = max_Mine;
	game_Feature.flags = theFlags;
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			(game_Board[i][j]).isOpened = (game_Board[i][j]).isFlag = (game_Board[i][j]).mine_Count = 0;
			mine_Board[i][j] = '.';
		}
	}
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
	ofstream outFile(DATA_PATH + "last_mineBoard.txt");
	if (outFile.fail()) {
		cout << " Cannot open old_mineBoard";
		exit(1);
	}
	time_t t;
	srand((unsigned)time(&t)); // Activate the random number runner
	while (hasPlaced < theMines) {
		int x = rand() % (game_Feature.MAX_ROW);
		int y = rand() % (game_Feature.MAX_COLUMN);
		bool isLegal = true;

		if (isMine(x, y, mine_Board)) {
			isLegal = false;
		}
		if (isLegal) {
			mine_Board[x][y] = '&';
			hasPlaced++;
		}
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			outFile << mine_Board[i][j];
		}
	}
	outFile.close();
}


void mine_board_Clear(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			mine_Board[i][j] = '.';
			(game_Board[i][j]).mine_Count = 0;
		}
	}
}


void splash_Feature(int x, int y, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	game_Board[x][y].isOpened = true;
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


void mine_settingUp(int theLevel, const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN]) {
	switch (theLevel) {
	case (int)Difficulty::Beginner: {
		mine_Create(game_Feature, mine_Board, BEGINNER_MINE);
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				mine_gameBoard_Count(i, j, game_Board, mine_Board, game_Feature);
			}
		}
		break;
	}
	case (int)Difficulty::Intermediate: {
		mine_Create(game_Feature, mine_Board, INTERMEDIATE_MINE);
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				mine_gameBoard_Count(i, j, game_Board, mine_Board, game_Feature);
			}
		}
		break;
	}
	case (int)Difficulty::Expert: {
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


void auto_play(int& theRow, int& theColumn, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], GAMEPREDICATE game_Feature) {
	do {
		theRow = rand() % (game_Feature.MAX_ROW);
		theColumn = rand() % (game_Feature.MAX_COLUMN);
	} while (mine_Board[theRow][theColumn] == '&' || game_Board[theRow][theColumn].isOpened);
}


void mine_reserveData(const PLAYER& current_Player, GAMECELL game_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature, const Timer& new_Timers) {
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
	outFile << static_cast<const PLAYER&>(current_Player);
	outFile.close();

}


bool mine_updateData(char mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, Timer& new_Timers, PLAYER& new_Player) {
	ifstream inFile(DATA_PATH + "last_Gamefeature.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Gamefeature";
		return false;
	}
	inFile >> game_Feature;
	inFile.close();
	
	inFile.open(DATA_PATH + "last_Gameboard.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Gameboard";
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
	if (inFile.fail()) {
		cout << " Cannot open last_Mineboard";
		return false;
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			inFile >> mine_Board[i][j];
		}
	}
	inFile.close();

	inFile.open(DATA_PATH + "last_Clock.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Clock";
		return false;
	}
	inFile >> new_Timers;
	inFile.close();

	inFile.open(DATA_PATH + "last_Player.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Player";
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
	ofstream outFile;
	switch (theLevel) {
	case 1: {
		records.beginner.push_back(newPlayer);
		outFile.open(DATA_PATH + "beginner_records.txt", ios::app);
		if (outFile.fail()) {
			cout << " ERROR: outFile cannot be opened.";
			exit(1);
		}
		outFile << records.beginner[records.beginner.size() - 1];
		sort(records.beginner.begin(), records.beginner.end());
		break;
	}
	case 2: {
		records.intermediate.push_back(newPlayer);
		outFile.open(DATA_PATH + "intermediate_records.txt", ios::app);
		if (outFile.fail()) {
			cout << " ERROR: outFile cannot be opened.";
			exit(1);
		}
		outFile << records.intermediate[records.intermediate.size() - 1];
		sort(records.intermediate.begin(), records.intermediate.end());
		break;
	}
	case 3: {
		records.expert.push_back(newPlayer);
		outFile.open(DATA_PATH + "expert_records.txt", ios::app);
		if (outFile.fail()) {
			cout << " ERROR: outFile cannot be opened.";
			exit(1);
		}
		outFile << records.expert[records.expert.size() - 1];
		sort(records.expert.begin(), records.expert.end());
		break;
	}
	}
	outFile.close();
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



