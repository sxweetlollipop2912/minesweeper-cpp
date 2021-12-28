#include "Comms.h"

#include "../Interface/Window/Window.h"


bool Comms::readGameInfo(GameInfo& game_info, const std::string& path) {
    std::ifstream ifs;

    {
        int cnt = 0;
        do {
            ++cnt;
            ifs = std::ifstream(path);
        } while (cnt < 10 && ifs.fail());
    }

    if (!ifs.fail()) {
        boost::archive::text_iarchive ia(ifs);

        game_info = GameInfo();
        ia >> game_info;

        return true;
    }

    return false;
    // archive and stream closed when destructors are called
}


void Comms::writeGameInfo(GameInfo& game_info, const std::string& path) {
    std::ofstream ofs;
    ofs.open(path);

    boost::archive::text_oarchive oa(ofs);

    oa << game_info;
    // archive and stream closed when destructors are called
}


Result Comms::interfaceInfoSending(const InterfaceInfo& info) {
    auto& current_info = (*Window::getInstance())->current_game_info;

    switch (info.game_event) {
    case GameEvent::NewGame: {
        readGameInfo(current_info, GAME_INFO_PATH);

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

        writeGameInfo(current_info, GAME_INFO_PATH);

        break;
    }
    case GameEvent::LoadGame: {
        if (!readGameInfo(current_info, GAME_INFO_PATH)) {
            current_info.game_Feature.MAX_ROW = current_info.game_Feature.MAX_COLUMN = -1;
        }
        
        break;
    }
    case GameEvent::ShowLeaderboard: {
        readGameInfo(current_info, GAME_INFO_PATH);

        break;
    }
    case GameEvent::OpenCell: {
        readGameInfo(current_info, GAME_INFO_PATH);

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

            writeGameInfo(current_info, GAME_INFO_PATH);
        }

        break;
    }
    case GameEvent::FlagCell: {
        readGameInfo(current_info, GAME_INFO_PATH);

        if (current_info.game_state == GameState::Ongoing) {
            current_info.current_timer = info.current_timer;

            int a = info.cell_pos.r, b = info.cell_pos.c;

            if (!current_info.cell_board[a][b].isOpened) {
                if (current_info.cell_board[a][b].isFlag) {
                    current_info.cell_board[a][b].isFlag = false;
                    current_info.game_Feature.flags++;
                }
                else {
                    current_info.cell_board[a][b].isFlag = true;
                    current_info.game_Feature.flags--;
                    if (current_info.game_Feature.flags == 0) {
                        switch (current_info.current_player.level) {
                        case (int)Difficulty::Beginner: {
                            if (fully_Flagged(current_info.cell_board, current_info.mine_board, current_info.game_Feature) == BEGINNER_MINE) {
                                open_all_Cell(current_info.cell_board, current_info.game_Feature);
                                current_info.game_state = GameState::Won;
                            }
                            break;
                        }
                        case (int)Difficulty::Intermediate: {
                            if (fully_Flagged(current_info.cell_board, current_info.mine_board, current_info.game_Feature) == INTERMEDIATE_MINE) {
                                open_all_Cell(current_info.cell_board, current_info.game_Feature);
                                current_info.game_state = GameState::Won;
                            }
                            break;
                        }
                        case (int)Difficulty::Expert: {
                            if (fully_Flagged(current_info.cell_board, current_info.mine_board, current_info.game_Feature) == EXPERT_MINE) {
                                open_all_Cell(current_info.cell_board, current_info.game_Feature);
                                current_info.game_state = GameState::Won;
                            }
                            break;
                        }
                        case (int)Difficulty::Custom: {
                            if (fully_Flagged(current_info.cell_board, current_info.mine_board, current_info.game_Feature) == current_info.game_Feature.maxMine) {
                                open_all_Cell(current_info.cell_board, current_info.game_Feature);
                                current_info.game_state = GameState::Won;
                            }
                            break;
                        }
                        }
                    }
                }

                ofstream outFile(DATA_PATH + "last_Gameboard.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Gameboard";
                    exit(1);
                }
                for (int i = 0; i < current_info.game_Feature.MAX_ROW; i++) {
                    for (int j = 0; j < current_info.game_Feature.MAX_COLUMN; j++) {
                        outFile << current_info.cell_board[i][j] << endl;
                    }
                }
                outFile.close();

            writeGameInfo(current_info, GAME_INFO_PATH);
        }

        break;
    }
    case GameEvent::AutoOpenCell: {
        readGameInfo(current_info, GAME_INFO_PATH);

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

            writeGameInfo(current_info, GAME_INFO_PATH);
        }

        break;
    }
    case GameEvent::QuitToMenu: {

        break;
    }
    case GameEvent::QuitGame: {

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
