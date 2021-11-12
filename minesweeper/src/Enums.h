#pragma once

/*enum class CellType {
	mine,
	number,
	blank,
	unknown
};

enum class CellState {
	opened,
	closed,
	flagged,
	questioned
};

enum class GameState {
	ongoing,
	won,
	lost,
	unknown
};*/

enum class Result {
	success,
	failure
};

enum class ButtonType {
	Start,
	Quit,
	Board,
	Unknown
};


enum class SceneType {
	Menu,
	Playing,
	Won,
	Lost,
	Leaderboard,
	Unkown
};