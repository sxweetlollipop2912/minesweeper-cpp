#include "Comms.h"

#include "../Interface/Window/Window.h"


bool Comms::readGameInfo(GameInfo& game_info, const std::string& path) {
    std::ifstream ifs(path);

    if (!ifs.fail()) {
        try {
            boost::archive::text_iarchive ia(ifs);

            game_info = GameInfo();
            ia >> game_info;

            return true;
        }
        catch (const std::exception& e) {
            return false;
        }
    }

    return false;
    // archive and stream closed when destructors are called
}


bool Comms::writeGameInfo(GameInfo& game_info, const std::string& path) {
    std::ofstream ofs;

    try {
        ofs.open(path);

        boost::archive::text_oarchive oa(ofs);
        oa << game_info;
    }
    catch (const std::exception& e) {
        return false;
    }

    return true;
    // archive and stream closed when destructors are called
}


Result Comms::interfaceInfoSending(const InterfaceInfo& info) {
    auto& current_info = (*Window::getInstance())->current_game_info;

    switch (info.game_event) {
    case GameEvent::StartGame: {
        bool ok = false;
        for (int i = 0; i < 10 && !ok; i++) {
            ok = readGameInfo(current_info, GAME_INFO_PATH);
        }
        if (!ok) {
            current_info.game_Feature.MAX_ROW = current_info.game_Feature.MAX_COLUMN = -1;
        }

        break;
    }
    case GameEvent::NewGame: {
        current_info.current_timer = info.current_timer;
        current_info.game_state = GameState::Ongoing;

        switch (info.difficulty) {
        case Difficulty::Beginner: {

            current_info.current_player.level = (int)Difficulty::Beginner;

            //Set_up game_Feature && cell_Board && mine_Board
            set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, BEGINNER_ROW, BEGINNER_COL, BEGINNER_MINE);

            break;
        }
        case Difficulty::Intermediate: {

            current_info.current_player.level = (int)Difficulty::Intermediate;

            //Set_up game_Feature && cell_Board && mine_Board
            set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, INTERMEDIATE_ROW, INTERMEDIATE_COL, INTERMEDIATE_MINE);

            break;
        }
        case Difficulty::Expert: {

            current_info.current_player.level = (int)Difficulty::Expert;

            //Set_up game_Feature && cell_Board && mine_Board
            set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, EXPERT_ROW, EXPERT_COL, EXPERT_MINE);

            break;
        }
        case Difficulty::Custom: {
            int mines = (float)(info.new_row * info.new_col) * CUSTOM_MINE_COEF;
            current_info.current_player.level = (int)Difficulty::Custom;

            //Set_up game_Feature && cell_Board && mine_Board
            set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, info.new_row, info.new_col, mines);

            break;
        }
        }

        //Setting mines into mine_board 
        mine_settingUp(current_info.current_player.level, current_info.game_Feature, current_info.mine_board, current_info.cell_board);

        break;
    }
    case GameEvent::LoadGame: {
        
        break;
    }
    case GameEvent::ShowLeaderboard: {

        break;
    }
    case GameEvent::OpenCell: {
        if (current_info.game_state == GameState::Ongoing) {
            current_info.current_timer = info.current_timer;

            int a = info.cell_pos.r, b = info.cell_pos.c;

            if (!current_info.cell_board[a][b].isFlag && !current_info.cell_board[a][b].isOpened) {
                if (current_info.mine_board[a][b] == '&') {
                    current_info.game_Feature.STOP = false;
                    current_info.game_state = GameState::Lost;
                    open_all_Cell(current_info.cell_board, current_info.game_Feature);
                }
                else {
                    splash_Feature(a, b, current_info.cell_board, current_info.mine_board, current_info.game_Feature);

                    if (has_Won(current_info.cell_board, current_info.mine_board, current_info.game_Feature)) {
                        open_all_Cell(current_info.cell_board, current_info.game_Feature);
                        current_info.game_state = GameState::Won;
                        current_info.current_player.timePlay = current_info.current_timer;
                        addtoRecord(current_info.current_player.level, current_info.current_player, current_info.records);
                    }
                }
            }
        }

        break;
    }
    case GameEvent::FlagCell: {
        if (current_info.game_state == GameState::Ongoing) {
            current_info.current_timer = info.current_timer;

            int a = info.cell_pos.r, b = info.cell_pos.c;

            if (!current_info.cell_board[a][b].isOpened) {
                if (current_info.cell_board[a][b].isFlag) {
                    set_unflagged(current_info.cell_board[a][b], current_info.game_Feature);
                }
                else if (current_info.game_Feature.flags > 0) {
                    set_flagged(current_info.cell_board[a][b], current_info.game_Feature);

                    if (has_Won(current_info.cell_board, current_info.mine_board, current_info.game_Feature)) {
                        open_all_Cell(current_info.cell_board, current_info.game_Feature);
                        current_info.game_state = GameState::Won;
                        current_info.current_player.timePlay = current_info.current_timer;
                        addtoRecord(current_info.current_player.level, current_info.current_player, current_info.records);
                    }
                }
            }
        }

        break;
    }
    case GameEvent::AutoOpenCell: {
        if (current_info.game_state == GameState::Ongoing) {
            current_info.current_timer = info.current_timer;

            int x = info.cell_pos.r, y = info.cell_pos.c;

            if (!auto_open_Cell(x, y, current_info.cell_board, current_info.mine_board, current_info.game_Feature)) {
                current_info.game_state = GameState::Lost;
                open_all_Cell(current_info.cell_board, current_info.game_Feature);
            }
            else if (has_Won(current_info.cell_board, current_info.mine_board, current_info.game_Feature)) {
                open_all_Cell(current_info.cell_board, current_info.game_Feature);
                current_info.game_state = GameState::Won;
                current_info.current_player.timePlay = current_info.current_timer;
                addtoRecord(current_info.current_player.level, current_info.current_player, current_info.records);
            }
        }

        break;
    }
    case GameEvent::QuitToMenu:
    case GameEvent::QuitGame: {
        bool ok = false;
        for (int i = 0; i < 10 && !ok; i++) {
            ok = writeGameInfo(current_info, GAME_INFO_PATH);
        }
        
        if (!ok) std::cout << "Failed to write save to files.";

        break;
    }
    }

    gameInfoSending(current_info);

    return Result::success;
}


Result Comms::gameInfoSending(const GameInfo& info) {
    auto window = Window::getInstance();
    (*window)->updateGameInfo();

    return Result::success;
}
