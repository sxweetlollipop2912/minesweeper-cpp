#pragma once

/*
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
	Cell,
	Unknown
};


enum class CellState {
	Closed,
	Opened,
	Flagged,
	Unknown
};


enum class CellType {
	Mine,
	Number,
	Blank,
	Unknown
};


enum class SceneType {
	Menu,
	Playing,
	Won,
	Lost,
	Leaderboard,
	Closing,
	Unkown
};