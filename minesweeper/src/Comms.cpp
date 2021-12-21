#include "Comms.h"
#include "../Interface/Window/Window.h"
#include"../Game/GameTools.h"

Result Comms::interfaceInfoSending(const InterfaceInfo info) {
    // Đây là hàm để chuyển info từ bên tui sang bên ông.
    // Tui đã pack lại thành biến info ở trên r á.
    // Ông làm gì đó ở đây để chuyển info về bên ông i.
    // Cần thiết thì return success hay failure để tui xử lí.
    // K thì ông sửa hàm thành void luôn cho tiện :v
    // NOTE: Khi tui gọi hàm này thì ông nhớ luôn gọi lại hàm gameInfoSending, cho dù k có gì để send nha.

    std::cout << "InterfaceInfo sending...\n";

    GameInfo current_info;

    switch (info.game_event) {
        case GameEvent::NewGame: {
            switch (info.difficulty) {
                case Difficulty::Beginner: {

                    current_info.current_player.level = 1;

                    //Set_up game_Feature && cell_Board && mine_Board
                    set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, 9, 9, 10, 10);

                    //Setting mines into mine_board as well as reverse mine_board
                    mine_settingUp(1, current_info.game_Feature, current_info.mine_board, current_info.old_mine_board, current_info.cell_board);

                    //Reverse other data
                    mine_reserveData(current_info.current_player, current_info.old_player, current_info.cell_board, current_info.old_cell_board, current_info.game_Feature, current_info.old_game_Feature, current_info.old_timer, current_info.current_timer);

                    thread cleck;

                    break;
                }
                case Difficulty::Intermediate: {

                    current_info.current_player.level = 2;

                    //Set_up game_Feature && cell_Board && mine_Board
                    set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, 16, 16, 40, 40);

                    //Setting mines into mine_board as well as reverse mine_board
                    mine_settingUp(1, current_info.game_Feature, current_info.mine_board, current_info.old_mine_board, current_info.cell_board);

                    //Reverse other data
                    mine_reserveData(current_info.current_player, current_info.old_player, current_info.cell_board, current_info.old_cell_board, current_info.game_Feature, current_info.old_game_Feature, current_info.old_timer, current_info.current_timer);

                    break;
                }
                case Difficulty::Expert: {

                    current_info.current_player.level = 3;

                    //Set_up game_Feature && cell_Board && mine_Board
                    set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, 16, 30, 99, 99);

                    //Setting mines into mine_board as well as reverse mine_board
                    mine_settingUp(1, current_info.game_Feature, current_info.mine_board, current_info.old_mine_board, current_info.cell_board);

                    //Reverse other data
                    mine_reserveData(current_info.current_player, current_info.old_player, current_info.cell_board, current_info.old_cell_board, current_info.game_Feature, current_info.old_game_Feature, current_info.old_timer, current_info.current_timer);

                    break;
                }
                case Difficulty::Custom: {
                    //Set_up mines
                    int mines = (info.new_row * info.new_col) * 20 / 100;

                    current_info.current_player.level = 0;

                    //Set_up game_Feature && cell_Board && mine_Board
                    set_up_game(current_info.game_Feature, current_info.cell_board, current_info.mine_board, info.new_row, info.new_col, mines, mines);

                    //Setting mines into mine_board as well as reverse mine_board
                    mine_settingUp(1, current_info.game_Feature, current_info.mine_board, current_info.old_mine_board, current_info.cell_board);

                    //Reverse other data
                    mine_reserveData(current_info.current_player, current_info.old_player, current_info.cell_board, current_info.old_cell_board, current_info.game_Feature, current_info.old_game_Feature, current_info.old_timer, current_info.current_timer);

                    break;
                }
            }
            break;
        }
        case GameEvent::LoadGame: {

            //Update data of the previous time from TEXT_FILE
            mine_updateData(current_info.mine_board, current_info.old_mine_board, current_info.cell_board, current_info.old_cell_board, current_info.game_Feature, current_info.old_game_Feature, current_info.current_timer, current_info.old_timer, current_info.current_player, current_info.old_player);

            break;
        }
        case GameEvent::ShowLeaderboard: {

            update_ScoreBoard(*(current_info.records));

            break;
        }
        case GameEvent::OpenCell: {
            int a = info.cell_pos.r, b = info.cell_pos.c;
            mine_updateData(current_info.mine_board, current_info.old_mine_board, current_info.cell_board, current_info.old_cell_board, current_info.game_Feature, current_info.old_game_Feature, current_info.current_timer, current_info.old_timer, current_info.current_player, current_info.old_player);

            if (current_info.mine_board[a][b] == '&') {
                current_info.cell_board[a][b].isOpened = true;
                current_info.game_Feature.STOP = false;
                current_info.game_state = GameState::Lost;
            }
            else if (current_info.cell_board[a][b].isOpened) {
                ofstream outFile(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                current_info.old_timer = current_info.current_timer;
                outFile << current_info.old_timer;
                outFile.close();
            }
            else if (current_info.cell_board[a][b].isFlag) {
                ofstream outFile(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                current_info.old_timer = current_info.current_timer;
                outFile << current_info.old_timer;
                outFile.close();
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
                        current_info.old_cell_board[i][j] = current_info.cell_board[i][j];
                        outFile << current_info.old_cell_board[i][j] << endl;
                    }
                }
                outFile.close();

                outFile.open(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                current_info.old_timer = current_info.current_timer;
                outFile << current_info.old_timer;
                outFile.close();

                bool Full = isFull(current_info.cell_board, current_info.mine_board, current_info.game_Feature);
                if (Full) {
                    current_info.game_Feature.STOP = true;
                    current_info.game_state = GameState::Won;
                    current_info.current_player.timePlay = current_info.current_timer;
                    addtoRecord(current_info.current_player.level, current_info.current_player, *current_info.records);
                }
            }

            break;
        }
        case GameEvent::FlagCell: {
            int a = info.cell_pos.r, b = info.cell_pos.c;
            mine_updateData(current_info.mine_board, current_info.old_mine_board, current_info.cell_board, current_info.old_cell_board, current_info.game_Feature, current_info.old_game_Feature, current_info.current_timer, current_info.old_timer, current_info.current_player, current_info.old_player);

            if (current_info.cell_board[a][b].isOpened) {
                ofstream outFile(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                current_info.old_timer = current_info.current_timer;
                outFile << current_info.old_timer;
                outFile.close();
            }
            else if (current_info.cell_board[a][b].isFlag) {
                ofstream outFile(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                current_info.old_timer = current_info.current_timer;
                outFile << current_info.old_timer;
                outFile.close();
            }
            else {
                current_info.cell_board[a][b].isFlag = true;
                current_info.game_Feature.flags--;

                ofstream outFile(DATA_PATH + "last_Gameboard.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Gameboard";
                    exit(1);
                }
                for (int i = 0; i < current_info.game_Feature.MAX_ROW; i++) {
                    for (int j = 0; j < current_info.game_Feature.MAX_COLUMN; j++) {
                        current_info.old_cell_board[i][j] = current_info.cell_board[i][j];
                        outFile << current_info.old_cell_board[i][j] << endl;
                    }
                }
                outFile.close();

                outFile.open(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                current_info.old_timer = current_info.current_timer;
                outFile << current_info.old_timer;
                outFile.close();

                outFile.open(DATA_PATH + "last_Gamefeature.txt");
                if (outFile.fail()) {
                    cout << " Cannot open Game_Feature";
                    exit(1);
                }
                current_info.old_game_Feature = current_info.game_Feature;
                outFile << current_info.old_game_Feature;
                outFile.close();
            }

            break;
        }
        case GameEvent::AutoOpenCell: {
            mine_updateData(current_info.mine_board, current_info.old_mine_board, current_info.cell_board, current_info.old_cell_board, current_info.game_Feature, current_info.old_game_Feature, current_info.current_timer, current_info.old_timer, current_info.current_player, current_info.old_player);
            int a, b;
            do {
                a = rand() % (current_info.game_Feature.MAX_ROW);
                b = rand() % (current_info.game_Feature.MAX_COLUMN);
            } while (current_info.cell_board[a][b].isOpened || current_info.cell_board[a][b].isFlag);

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
                        current_info.old_cell_board[i][j] = current_info.cell_board[i][j];
                        outFile << current_info.old_cell_board[i][j] << endl;
                    }
                }
                outFile.close();

                outFile.open(DATA_PATH + "last_Clock.txt");
                if (outFile.fail()) {
                    cout << " Cannot open last_Clock";
                    exit(1);
                }
                current_info.old_timer = current_info.current_timer;
                outFile << current_info.old_timer;
                outFile.close();

                bool Full = isFull(current_info.cell_board, current_info.mine_board, current_info.game_Feature);
                if (Full) {
                    current_info.game_Feature.STOP = true;
                    current_info.game_state = GameState::Won;
                    current_info.current_player.timePlay = current_info.current_timer;
                    addtoRecord(current_info.current_player.level, current_info.current_player, *current_info.records);
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


// Ông chỉ gọi hàm này khi tui gọi interfaceInfoSending th nha, tại mình k có làm multithread.
Result Comms::gameInfoSending(const GameInfo info) {
    auto window = Window::getInstance();
    (*window)->updateGameInfo(info);

    return Result::success;
}
