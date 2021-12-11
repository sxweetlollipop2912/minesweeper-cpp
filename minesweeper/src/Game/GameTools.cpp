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
	outFile << anObject.timePlay << " " << anObject.level << " " << anObject.name << endl;
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
	inFile >> oldPlayer.timePlay >> oldPlayer.level >> oldPlayer.name;
	return inFile;
}

ifstream& operator >> (ifstream& inFile, GAMECELL& anObject) {
	inFile >> anObject.isFlag >> anObject.isOpened >> anObject.mine_Count;
	return inFile;
}

ifstream& operator >> (ifstream& inFile, vector <PLAYER>& score_Board) {
	score_Board.clear();

	PLAYER player;
	while (inFile >> player.timePlay >> player.level >> player.name) {
		score_Board.push_back(player);
		inFile.ignore(1, '\n');
	}

	return inFile;
}

void mine_Level(int level, GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature, char mine_Board[][MAX_COLUMN],
	GAMECELL game_Board[][MAX_COLUMN]) {

	switch (level) {
	case 1: {
		game_Feature.MAX_ROW = 9;
		game_Feature.MAX_COLUMN = 9;
		game_Feature.maxMine = 10;
		game_Feature.flags = 10;
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				(game_Board[i][j]).isOpened = (game_Board[i][j]).isFlag = (game_Board[i][j]).mine_Count = 0;
				mine_Board[i][j] = '.';
			}
		}
		old_game_Feature = game_Feature;
		break;
	}
	case 2: {
		game_Feature.MAX_ROW = 16;
		game_Feature.MAX_COLUMN = 16;
		game_Feature.maxMine = 40;
		game_Feature.flags = 40;
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				(game_Board[i][j]).isOpened = (game_Board[i][j]).isFlag = (game_Board[i][j]).mine_Count = 0;
				mine_Board[i][j] = '.';
			}
		}
		old_game_Feature = game_Feature;
		break;
	}
	case 3: {
		game_Feature.MAX_ROW = 16;
		game_Feature.MAX_COLUMN = 30;
		game_Feature.maxMine = 99;
		game_Feature.flags = 99;
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				(game_Board[i][j]).isOpened = (game_Board[i][j]).isFlag = (game_Board[i][j]).mine_Count = 0;
				mine_Board[i][j] = '.';
			}
		}
		old_game_Feature = game_Feature;
		break;
	}
	default: {
		cout << " ERROR: Illegal value input!";
		break;
	}
	}
	ofstream outFile(DATA_PATH + "last_Gamefeature.txt");
	if (outFile.fail()) {
		cout << " Cannot open Game_Feature";
		exit(1);
	}
	outFile << old_game_Feature;
	outFile.close();
}


bool isValid(int theRow, int theColumn, const GAMEPREDICATE& game_Feature) {
	return (theRow >= 0 && theRow < game_Feature.MAX_ROW&& theColumn >= 0 && theColumn < game_Feature.MAX_COLUMN);
}


bool isMine(int theRow, int theColumn, char mine_Board[][MAX_COLUMN]) {
	return (mine_Board[theRow][theColumn] == '&');
}


void mine_gameBoard_Count(int theRow, int theColumn, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	if (!isValid(theRow, theColumn, game_Feature)) {
		cout << " ERROR: Illegal value input!";
		exit(1);
	}
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if ((theRow + i >= 0) && (theColumn + j >= 0) && (theRow + i <= game_Feature.MAX_ROW) && (theColumn + j <= game_Feature.MAX_COLUMN)) {
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
			if ((theRow + i >= 0) && (theColumn + j >= 0) && (theRow + i <= game_Feature.MAX_ROW) && (theColumn + j <= game_Feature.MAX_COLUMN)) {
				if (mine_Board[theRow + i][theColumn + j] == '&' && !isMine(theRow, theColumn, mine_Board)) {
					mine++;
				}
			}
		}
	}
	return mine;
}


void mine_Create(const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], int theMines) {
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
			mine_Board[x][y] = old_mine_Board[x][y] = '&';
		}
		hasPlaced++;
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			outFile << old_mine_Board[i][j];
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


void printBoard(GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			if (game_Board[i][j].isOpened && mine_Board[i][j] != '&') {
				cout << game_Board[i][j].mine_Count << " ";
			}
			else if (game_Board[i][j].isOpened && mine_Board[i][j] == '&') {
				cout << "& ";
			}
			else if (game_Board[i][j].isFlag) {
				cout << "$ ";
			}
			else { // not opened yet
				cout << ". ";
			}
		}
		cout << endl;
	}
}


void splash_Feature(int x, int y, GAMECELL game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature) {
	game_Board[x][y].isOpened = true;
	if (game_Board[x][y].mine_Count == 0) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (i != 0 || j != 0) {
					if (x + i >= 0 && x + i < game_Feature.MAX_ROW && y + j >= 0 && y + j < game_Feature.MAX_COLUMN) {
						if (!game_Board[x + i][y + j].isOpened && mine_Board[x + i][y + j] != '&')
							splash_Feature(x + i, y + j, game_Board, mine_Board, game_Feature);
					}
				}
			}
		}
	}
}


void inputChoice(int& theRow, int& theColumn, char& k, const GAMEPREDICATE& game_Feature) {
	cout << "\n\n You have " << game_Feature.flags << " flags left!" << endl
		<< " Choose (C) or Flags (F) or Exit game (E): ";
	cin >> k;
	if (k == 'E') {
		// do nothing
	}
	else { // k=='C' || k=='F'
		cout << " Input Row - Column: ";
		cin >> theRow >> theColumn;
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



void inputInfo(PLAYER& new_Player, PLAYER& old_Player) {
	system("cls");
	cout << " Please enter your name: ";
	cin.ignore(1, '\n');
	getline(cin, new_Player.name);
	cout << " " << new_Player.name << " , please choose the game level : \n\n"
		<< " A. Press 1 for records.beginner ( 9 x 9 cells and 10 mines )\n"
		<< " B. Press 2 for INTERMEDIATE ( 16 x 16 cells and 40 mines )\n"
		<< " C. Press 3 for EXPERT ( 16 x 30 cells and 99 mines )\n"
		<< " ENTER YOUR CHOICE HERE: ";
	cin >> new_Player.level;
	old_Player = new_Player;
	ofstream outFile(DATA_PATH + "last_Player.txt");
	if (outFile.fail()) {
		cout << " ERROR: Cannot open Information.";
	}
	outFile << static_cast<const PLAYER&>(old_Player);
	outFile.close();
}

void mine_settingUp(int theLevel, const GAMEPREDICATE& game_Feature, char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN]) {
	switch (theLevel) {
	case 1: {
		mine_Create(game_Feature, mine_Board, old_mine_Board, 10);
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				mine_gameBoard_Count(i, j, game_Board, mine_Board, game_Feature);
			}
		}
		break;
	}
	case 2: {
		mine_Create(game_Feature, mine_Board, old_mine_Board, 40);
		for (int i = 0; i < game_Feature.MAX_ROW; i++) {
			for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				mine_gameBoard_Count(i, j, game_Board, mine_Board, game_Feature);
			}
		}
		break;
	}
	case 3: {
		mine_Create(game_Feature, mine_Board, old_mine_Board, 99);
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

void mine_reserveData(GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN], const GAMEPREDICATE& game_Feature, Timer& old_Timers, const Timer& new_Timers) {
	ofstream outFile(DATA_PATH + "last_Gameboard.txt");
	if (outFile.fail()) {
		cout << " Cannot open last_Gameboard";
		exit(1);
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			old_game_Board[i][j] = game_Board[i][j];
			outFile << old_game_Board[i][j] << endl;
		}
	}
	outFile.close();

	outFile.open(DATA_PATH + "last_Clock.txt");
	if (outFile.fail()) {
		cout << " Cannot open last_Clock";
		exit(1);
	}
	old_Timers = new_Timers;
	outFile << old_Timers;
	outFile.close();
}

void mine_updateData(char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN],
	GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature, Timer& new_Timers, Timer& old_Timers, PLAYER& new_Player, PLAYER& old_Player) {
	ifstream inFile(DATA_PATH + "last_Gamefeature.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Gamefeature";
		exit(1);
	}
	inFile >> old_game_Feature;
	inFile.close();
	game_Feature = old_game_Feature;
	inFile.open(DATA_PATH + "last_Gameboard.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Gameboard";
		exit(1);
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			inFile >> old_game_Board[i][j];
			inFile.ignore(1, '\n');
			game_Board[i][j] = old_game_Board[i][j];
		}
	}
	inFile.close();
	inFile.open(DATA_PATH + "last_Mineboard.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Mineboard";
		exit(1);
	}
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			inFile >> old_mine_Board[i][j];
		}
	}
	inFile.close();
	for (int i = 0; i < game_Feature.MAX_ROW; i++) {
		for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
			mine_Board[i][j] = old_mine_Board[i][j];
		}
	}
	inFile.open(DATA_PATH + "last_Clock.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Clock";
		exit(1);
	}
	inFile >> old_Timers;
	inFile.close();
	new_Timers = old_Timers;
	inFile.open(DATA_PATH + "last_Player.txt");
	if (inFile.fail()) {
		cout << " Cannot open last_Player";
		exit(1);
	}
	inFile >> old_Player;
	inFile.close();
	new_Player = old_Player;
}

void mine_Onscreen(char& theChoice, bool& isWin, bool Full, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN], char mine_Board[][MAX_COLUMN],
	GAMEPREDICATE& game_Feature, Timer& new_Timers, Timer& old_Timers) {
	do {
		int a, b;
		system("cls");
		printBoard(game_Board, mine_Board, game_Feature);
		//inputChoice(a, b, theChoice);
		theChoice = 'C';
		auto_play(a, b, game_Board, mine_Board, game_Feature);
		if (theChoice == 'E') {
			mine_reserveData(game_Board, old_game_Board, game_Feature, old_Timers, new_Timers);
			new_Timers.STOP = true;
			system("cls");
			break;
		}
		if (mine_Board[a][b] == '&' && theChoice == 'C') {
			isWin = false;
			game_Board[a][b].isOpened = true;
			system("cls");
			printBoard(game_Board, mine_Board, game_Feature);
			cout << " \n\n You chose a mine. You lose the game. Good Luck next time.\n";
			game_Feature.STOP = false;
			new_Timers.STOP = true;
			Sleep(3000);
			system("cls");
			break;
		}
		else if (game_Board[a][b].isOpened) {
			cout << " The cell has been opened.";
			Sleep(1000);
		}
		else {
			if (theChoice == 'C') {
				splash_Feature(a, b, game_Board, mine_Board, game_Feature);
				mine_reserveData(game_Board, old_game_Board, game_Feature, old_Timers, new_Timers);
			}
			else if (theChoice == 'F') {
				game_Board[a][b].isFlag = true;
				game_Feature.flags--;
				mine_reserveData(game_Board, old_game_Board, game_Feature, old_Timers, new_Timers);
			}
		}
		Full = isFull(game_Board, mine_Board, game_Feature);
		if (Full) {
			game_Feature.STOP = false;
			new_Timers.STOP = true;
			isWin = true;
		}
	} while (isWin && !Full);
}

bool operator < (const PLAYER& first, const PLAYER& second) {
	int a = first.timePlay.hours * 3600 + first.timePlay.minutes * 60 + first.timePlay.seconds;
	int b = second.timePlay.hours * 3600 + second.timePlay.minutes * 60 + second.timePlay.seconds;
	return (a < b);
}



void addtoRecord(int theLevel, const PLAYER& newPlayer) {
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

void printRecord(std::vector <PLAYER>& v) {
	system("cls");
	cout << " Here is the record: \n"
		<< " Rank					Name					Time play\n";
	int a = 1;
	for (const auto& i : v) {
		cout << " " << a << "					" << i.name << "					" << i.timePlay << endl;
		a++;
	}
	char k;
	cout << endl << " Left? (Y): ";
	cin >> k;
	system("cls");
}

void mine_Playgame(char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature,
	PLAYER& newPlayer, PLAYER& oldPlayer, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN],
	Timer& new_Timers, Timer& old_Timers) {
	update_ScoreBoard(records);
	thread clock;
	inputInfo(newPlayer, oldPlayer);
	mine_Level(newPlayer.level, game_Feature, old_game_Feature, mine_Board, game_Board);
	mine_settingUp(newPlayer.level, game_Feature, mine_Board, old_mine_Board, game_Board);
	bool isWin = true;
	bool Full = false;
	clock = thread(timer);
	int a, b;
	char k;
	mine_Onscreen(k, isWin, Full, game_Board, old_game_Board, mine_Board, game_Feature, new_Timers, old_Timers);
	clock.join();
	if (isWin && k != 'E') {
		cout << " \nCONGRATULATION! YOU WIN THE GAME!";
		newPlayer.timePlay = new_Timers;
		addtoRecord(newPlayer.level, newPlayer);
	}
	new_Timers = { 0,0,0 };
}


void mine_Loadgame(char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature,
	PLAYER& newPlayer, PLAYER& oldPlayer, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN],
	Timer& new_Timers, Timer& old_Timers) {
	mine_updateData(mine_Board, old_mine_Board, game_Board, old_game_Board, game_Feature, old_game_Feature, new_Timers, old_Timers, newPlayer, oldPlayer);
	thread clock;
	bool isWin = true, Full = false;
	clock = thread(timer);
	char k;
	mine_Onscreen(k, isWin, Full, game_Board, old_game_Board, mine_Board, game_Feature, new_Timers, old_Timers);
	clock.join();
	if (isWin && k != 'E') {
		cout << " \nCONGRATULATION! YOU WIN THE GAME!";
		newPlayer.timePlay = new_Timers;
		addtoRecord(newPlayer.level, newPlayer);
	}
}

void welcomePlayer(int& choice) {
	cout << " WELCOME TO MINESWEEPER!\n\n\n"
		<< " 1. PLAY GAME\n"
		<< " 2. LOAD GAME\n"
		<< " 3. SCOREBOARD\n"
		<< " 4. EXIT\n";
	cout << " Please enter your choice here: ";
	cin >> choice;
}



void implementChoice(int choice, char mine_Board[][MAX_COLUMN], char old_mine_Board[][MAX_COLUMN], GAMEPREDICATE& game_Feature, GAMEPREDICATE& old_game_Feature,
	PLAYER& newPlayer, PLAYER& oldPlayer, GAMECELL game_Board[][MAX_COLUMN], GAMECELL old_game_Board[][MAX_COLUMN]) {
	switch (choice) {
	case 1: {
		mine_Playgame(mine_Board, old_mine_Board, game_Feature, old_game_Feature, newPlayer, oldPlayer, game_Board, old_game_Board, new_Timers, old_Timers);
		break;
	}
	case 2: {
		mine_Loadgame(mine_Board, old_mine_Board, game_Feature, old_game_Feature, newPlayer, oldPlayer, game_Board, old_game_Board, new_Timers, old_Timers);
		break;
	}
	case 3: {
		system("cls");
		update_ScoreBoard(records);
		cout << " Which level do you want to see? (B-I-E): ";
		char ans;
		cin >> ans;
		switch (ans) {
		case 'B': {
			printRecord(records.beginner);
			break;
		}
		case 'I': {
			printRecord(records.intermediate);
			break;
		}
		case 'E': {
			printRecord(records.expert);
			break;
		}
		}
		break;
	}
	case 4: {
		system("cls");
		cout << " Program is closing....";
		Sleep(1000);
		exit(1);
		break;
	}
	default: {
		cout << " Illegal input!";
		exit(1);
	}
	}
}
