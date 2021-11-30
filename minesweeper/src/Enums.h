#pragma once

enum class Result {
	success,
	failure
};


enum class GameEvent {
	QuitGame,
	QuitToMenu,
	OpenPopUp,
	ClosePopUp,
	NewGame,
	LoadGame,
	ShowLeaderboard,
	Playing,
	OpenCell,
	FlagCell,
	AutoOpenCell,
	Won,
	Lost,
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


enum class MouseActionType {
	Move,
	LMB,
	RMB,
	DoubleLMB,
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
	ButtonDefault,
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