#pragma once

#include <string>
#include <vector>
 
using std::string;


struct Timer {
	int hours;
	int minutes;
	int seconds;
	bool STOP = false;
};

struct PLAYER {
	std::string name;
	Timer timePlay = { 0,0,0, false };
	int level;
};

struct Records {
	std::vector <PLAYER> beginner;
	std::vector <PLAYER> intermediate;
	std::vector <PLAYER> expert;

	Records() {
		beginner.clear();
		intermediate.clear();
		expert.clear();
	}
};

struct GAMEPREDICATE {
	int MAX_ROW;
	int MAX_COLUMN;
	int maxMine;
	int flags;
	bool STOP = false;
};

struct GAMECELL {
	bool isOpened;
	bool isFlag;
	int mine_Count;
};


