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
	SkipSong,
	Unknown
};


enum class SceneType {
	Menu,
	Difficulties,
	Playing,
	Leaderboard,
	PopUp,
	Background,
	Unknown
};


 enum class Difficulty {
	Beginner = 1,
	Intermediate = 2,
	Expert = 3,
	Custom = 0,
	Unknown
};


 // Handle only (FirstLMB and SecondLMB) or (LMB and DoubleLMB), never both.
enum class MouseActionType {
	Move,
	FirstLMB,
	SecondLMB,
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
	DefaultButton,
	YesNoButton,
	PopUpBackground,
	ReturnButton,
	SkipSong,
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