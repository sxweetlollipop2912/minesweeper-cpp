#pragma once

#include <vector>

#include "../Constants.h"
#include "../Enums.h"
#include "../Interface/Board/Position.h"
#include "../Interface/Board/Board.h"
#include "../Structs.h"


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
		GameState game_state;
		GameCell cell_board[MAX_ROW][MAX_COLUMN];
		char mine_board[MAX_ROW][MAX_COLUMN];
		Timer current_timer;

		// Only needed in SceneType::Leaderboard or in GameEvent::ShowLeaderboard.
		// Xài std::make_shared<Records>(records_var) để tạo shared pointer.
		std::shared_ptr<Records> records = nullptr;
	};
	


	/// Used by INTERFACE to send InterfaceInfo whenever there are changes, to GAME.
	Result interfaceInfoSending(const InterfaceInfo info);

	Result gameInfoSending(const GameInfo info);
}