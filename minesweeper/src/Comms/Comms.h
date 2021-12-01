#pragma once

#include <vector>

#include "../Constants.h"
#include "../Enums.h"
#include "../Board/Position.h"
#include "../Board/Board.h"


// Temporary definitions. Will be deleted in code merging.
// Tui copy từ bên ông qua á, nên ông cứ xoá đống này r xài cái của ông khi code cũng đc.
struct Timer {
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	bool STOP = false;
};
struct PLAYER {
	std::string name;
	Timer timePlay = { 0,0,0, 0 };
	int level = -1;
};
typedef std::vector<PLAYER> Record;
//********************************************************


namespace Comms {
	/// INTERFACE: handles UI, graphical stuff, receives inputs from user then sends to GAME for processing.
	/// GAME: handles logic, game data, processes user inputs sent from INTERFACE then sends game data back to INTERFACE for printing out on screen.
	

	struct InterfaceInfo {
		// This is a list a GameEvent that GAME should handle:
		// > QuitGame:		quitting the game. Time to wrap up everything.
		// > QuitToMenu:		quitting to menu. Time to wrap up things base on `current_scene`.
		// > NewGame:		create a new board and delete current save.
		// > LoadGame:		load current saved game (board, flags left, timer).
		// > ShowLeaderboard:	load leaderboard.
		// > OpenCell:		open a cell.
		// > FlagCell:		flag a cell.
		// > AutoOpenCell:		auto-open safe cells around current cell.
		// Upon receiving a GameEvent, INTERFACE would send an InterfaceInfo back to GAME first before doing anything else.
		GameEvent game_event = GameEvent::Unknown;

		// SceneType `current_scene` is one of the following:
		// > Menu,
		// > Playing,
		// > Leaderboard,
		SceneType current_scene = SceneType::Unkown;

		// Only assigned when GameEvent `game_event` is one the following: OpenCell, FlagCell, AutoOpenCell.
		// `current_scene` should be SceneType::Playing.
		// Otherwise, it is Position( r: -1, c: -1 ).
		Position cell_pos = Position(-1, -1);
	};


	struct GameInfo {
		// Only needed in SceneType::Playing.
		// These should be the info of current saved game.
		GameCell cell_board[MAX_ROW][MAX_COLUMN];
		char mine_board[MAX_ROW][MAX_COLUMN];
		Timer current_timer;

		// Only needed in SceneType::Leaderboard or in GameEvent::ShowLeaderboard.
		// Just use std::make_shared<Record>(record_var) to create a shared pointer.
		std::shared_ptr<Record> beginner = nullptr;
		std::shared_ptr<Record> intermediate = nullptr;
		std::shared_ptr<Record> expert = nullptr;
	};
	


	/// Used by INTERFACE to send InterfaceInfo whenever there are changes, to GAME.
	Result interfaceInfoSending(const InterfaceInfo info);

	Result gameInfoSending(const GameInfo info);
}