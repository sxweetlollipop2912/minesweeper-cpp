#pragma once

#include <vector>
#include <string>
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "../Interface/Board/Position.h"
#include "../Interface/Board/Board.h"
#include "../Game/GameTools.h"
#include "../Structs.h"
#include "../Constants.h"
#include "../Enums.h"


/// > INTERFACE: handles UI, graphical stuff, receives inputs from user then sends to GAME for processing.
/// > GAME: handles logic, game data, processes user inputs sent from INTERFACE then sends game data back to INTERFACE for printing out on screen.
/// > Whenever INTERFACE sends an InterfaceInfo, GAME must ALWAYS return a GameInfo, regardless of whether GAME has made any change or not.
namespace Comms {
	struct InterfaceInfo {
		// This is a list a GameEvent that GAME should ONLY handle:
		// > StartGame:		sent at game initialization.
		// > QuitGame:		quitting the game. Time to wrap up everything.
		// > QuitToMenu:		quitting to menu. Time to wrap up things if current_scene is Playing.
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
		SceneType current_scene = SceneType::Unknown;

		// Only assigned on GameEvent::NewGame.
		// This can be a custom board size, or a generic board size (depends on difficulty).
		int new_row = -1;
		int new_col = -1;
		Difficulty difficulty = Difficulty::Unknown;

		// Only assigned during SceneType::Playing
		Time current_timer = Time(-1, -1, -1, false);

		// Only assigned when GameEvent `game_event` is one the following: OpenCell, FlagCell, AutoOpenCell.
		// `current_scene` should be SceneType::Playing.
		// Otherwise, it is Position( r: -1, c: -1 ).
		Position cell_pos = Position(-1, -1);
	};


	struct GameInfo {
		// Only needed in SceneType::Playing.
		// These should be the info of current saved game.
		GameState game_state = GameState::Ongoing;
		GAMECELL cell_board[MAX_ROW][MAX_COLUMN];
		char mine_board[MAX_ROW][MAX_COLUMN];
		GAMEPREDICATE game_Feature;
		PLAYER current_player;

		// Only needed while loading game.
		Time current_timer = Time(-1, -1, -1, false);

		// Only needed in SceneType::Leaderboard or in GameEvent::ShowLeaderboard.
		Records records;


		template<class Archive>
		void serialize(Archive& ar, const unsigned int version) {
			ar& game_state;
			ar& game_Feature;
			ar& current_player;
			ar& current_timer;
			ar& records;

			for (int i = 0; i < game_Feature.MAX_ROW; i++) for (int j = 0; j < game_Feature.MAX_COLUMN; j++) {
				ar& cell_board[i][j];
				ar& mine_board[i][j];
			}
		}
	};
	

	bool readGameInfo(GameInfo& game_info, const std::string& path);
	bool writeGameInfo(GameInfo& game_info, const std::string& path);

	/// Used by INTERFACE to send InterfaceInfo whenever there are changes, to GAME.
	Result interfaceInfoSending(const InterfaceInfo& info);

	Result gameInfoSending(const GameInfo& info);
}