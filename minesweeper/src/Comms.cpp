#include "Comms.h"

#include "../Interface/Window/Window.h"


Result Comms::interfaceInfoSending(const InterfaceInfo& info) {
    auto& current_info = (*Window::getInstance())->current_game_info;

    switch (info.game_event) {
        case GameEvent::NewGame: {
            switch (info.difficulty) {
                case Difficulty::Beginner: {

                    current_info.current_player.level = (int)Difficulty::Beginner;

                    //Set_up game_Feature && cell_Board && mine_Board
                    set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, BEGINNER_ROW, BEGINNER_COL, BEGINNER_MINE, BEGINNER_MINE);

                    //Setting mines into mine_board as well as reverse mine_board
                    mine_settingUp(current_info.current_player.level, current_info.game_Feature, current_info.mine_board, current_info.cell_board);

                    //Reverse other data
                    mine_reserveData(current_info.current_player, current_info.cell_board, current_info.game_Feature, current_info.current_timer);

                    break;
                }
                case Difficulty::Intermediate: {

                    current_info.current_player.level = (int)Difficulty::Intermediate;

                    //Set_up game_Feature && cell_Board && mine_Board
                    set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, INTERMEDIATE_ROW, INTERMEDIATE_COL, INTERMEDIATE_MINE, INTERMEDIATE_MINE);

                    //Setting mines into mine_board as well as reverse mine_board
                    mine_settingUp(current_info.current_player.level, current_info.game_Feature, current_info.mine_board, current_info.cell_board);

                    //Reverse other data
                    mine_reserveData(current_info.current_player, current_info.cell_board, current_info.game_Feature, current_info.current_timer);

                    break;
                }
                case Difficulty::Expert: {

                    current_info.current_player.level = (int)Difficulty::Expert;

                    //Set_up game_Feature && cell_Board && mine_Board
                    set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, EXPERT_ROW, EXPERT_COL, EXPERT_MINE, EXPERT_MINE);

                    //Setting mines into mine_board as well as reverse mine_board
                    mine_settingUp(current_info.current_player.level, current_info.game_Feature, current_info.mine_board, current_info.cell_board);

                    //Reverse other data
                    mine_reserveData(current_info.current_player, current_info.cell_board, current_info.game_Feature, current_info.current_timer);

                    break;
                }
                case Difficulty::Custom: {
                    //Set_up mines
                    int mines = (float)(info.new_row * info.new_col) * CUSTOM_MINE_COEF;

                    current_info.current_player.level = (int)Difficulty::Custom;

                    //Set_up game_Feature && cell_Board && mine_Board
                    set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, info.new_row, info.new_col, mines, mines);

                    //Setting mines into mine_board as well as reverse mine_board
                    mine_settingUp(current_info.current_player.level, current_info.game_Feature, current_info.mine_board, current_info.cell_board);

                    //Reverse other data
                    mine_reserveData(current_info.current_player, current_info.cell_board, current_info.game_Feature, current_info.current_timer);

                    break;
                }
            }
            break;
        }
        case GameEvent::LoadGame: {

            //Update data of the previous time from TEXT_FILE
            if (!mine_updateData(current_info.mine_board, current_info.cell_board, current_info.game_Feature, current_info.current_timer, current_info.current_player)) {
                current_info.game_Feature.MAX_ROW = current_info.game_Feature.MAX_COLUMN = -1;
            }

            break;
        }
        case GameEvent::ShowLeaderboard: {

            update_ScoreBoard(*(current_info.records));

            break;
        }
        case GameEvent::OpenCell: {
            int a = info.cell_pos.r, b = info.cell_pos.c;
            mine_updateData(current_info.mine_board, current_info.cell_board, current_info.game_Feature, current_info.current_timer, current_info.current_player);

            if (!current_info.cell_board[a][b].isFlag && !current_info.cell_board[a][b].isOpened) {
                if (current_info.mine_board[a][b] == '&') {
                    current_info.cell_board[a][b].isOpened = true;
                    current_info.game_Feature.STOP = false;
                    current_info.game_state = GameState::Lost;
                }
                else {

                    splash_Feature(a, b, current_info.cell_board, current_info.mine_board, current_info.game_Feature);

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

                    outFile.open(DATA_PATH + "last_Clock.txt");
                    if (outFile.fail()) {
                        cout << " Cannot open last_Clock";
                        exit(1);
                    }                   
                    outFile << current_info.current_timer;
                    outFile.close();

                    bool Full = isFull(current_info.cell_board, current_info.mine_board, current_info.game_Feature);
                    if (Full) {
                        current_info.game_Feature.STOP = true;
                        current_info.game_state = GameState::Won;
                        current_info.current_player.timePlay = current_info.current_timer;
                        addtoRecord(current_info.current_player.level, current_info.current_player, *current_info.records);
                    }
                }
            }
            else {
                ofstream outFile(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                outFile << current_info.current_timer;
                outFile.close();
            }

            break;
        }
        case GameEvent::FlagCell: {
            int a = info.cell_pos.r, b = info.cell_pos.c;
            mine_updateData(current_info.mine_board, current_info.cell_board, current_info.game_Feature, current_info.current_timer, current_info.current_player);

            if (current_info.cell_board[a][b].isOpened) {
                ofstream outFile(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                outFile << current_info.current_timer;
                outFile.close();
            }
            else {
                if (current_info.cell_board[a][b].isFlag) {
                    current_info.cell_board[a][b].isFlag = false;
                    current_info.game_Feature.flags++;
                }
                else {
                    current_info.cell_board[a][b].isFlag = true;
                    current_info.game_Feature.flags--;
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

                outFile.open(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                outFile << current_info.current_timer;
                outFile.close();

                outFile.open(DATA_PATH + "last_Gamefeature.txt");
                if (outFile.fail()) {
                    cout << " Cannot open Game_Feature";
                    exit(1);
                }
                outFile << current_info.game_Feature;
                outFile.close();
            }

            break;
        }
        case GameEvent::AutoOpenCell: {

            mine_updateData(current_info.mine_board, current_info.cell_board, current_info.game_Feature, current_info.current_timer, current_info.current_player);

            for (int i = 0; i < current_info.game_Feature.MAX_ROW; i++) {
                for (int j = 0; j < current_info.game_Feature.MAX_COLUMN; j++) {
                    if (!(current_info.cell_board[i][j].isFlag || current_info.cell_board[i][j].isOpened)) {
                        if (!isMine(i, j, current_info.mine_board)) {
                            current_info.cell_board[i][j].isOpened = true;
                        }
                    }
                }
            }


            break;
        }
        case GameEvent::QuitToMenu: {
            // do nothing 

            break;
        }
        case GameEvent::QuitGame: {
            //do nothing

            break;
        }
    }

    gameInfoSending(current_info);

    return Result::success;
}


Result Comms::gameInfoSending(const GameInfo& info) {
    auto window = Window::getInstance();
    (*window)->updateGameInfo(info);

    return Result::success;
}
