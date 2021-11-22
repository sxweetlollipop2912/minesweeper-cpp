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
	Back,
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


enum class TextureType {
	DefaultButton,
	CellMine,
	CellClosed,
	CellFlagged,
	CellBlank,
	CellNum1,
	CellNum2,
	CellNum3,
	CellNum4,
	CellNum5,
	CellNum6,
	CellNum7,
	CellNum8,
	Unknown
};


enum class FontType {
	FontDefault,
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