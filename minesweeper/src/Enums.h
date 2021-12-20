#pragma once


enum class Result {
	success,
	failure
};


enum class GameState {
	Ongoing,
	Won,
	Lost
};


enum class GameEvent {
	QuitGame,
	QuitToMenu,
	OpenPopUp,
	ClosePopUp,
	ShowDifficulties,
	NewGame,
	LoadGame,
	ShowLeaderboard,
	OpenCell,
	FlagCell,
	AutoOpenCell,
	Won,
	Lost,
	ChangesInScene,
	NextSong,
	Unknown
};


enum class SceneType {
	Menu,
	Difficulties,
	Playing,
	Leaderboard,
	PopUp,
	Unkown
};

 enum class Difficulty {
	Beginner,
	Intermediate,
	Expert,
	Custom,
	Unknown
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
	NextSong,
	Scoreboard,
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