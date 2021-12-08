// Run with configuration: release, x64

#include <iostream>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game/GameTools.h"
#include "Constants.h"

#include "Interface/Window/Window.h"
#include "Interface/ResourceVault/ResourceVault.h"
#include "Interface/Scenes/menu_scene.h"
#include "Interface/Scenes/playing_scene.h"
#include "Interface/Button/Button.h"


void registerResources() {
    // TEXTURES
    {
        if (ResourceVault::setTexture(TextureType::ButtonDefault, DEFAULT_BUTTON_PATH) == Result::failure) {
            std::cout << "Load ButtonDefault texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellClosed, CLOSED_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellClosed texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellFlagged, FLAGGED_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellFlagged texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellBlank, BLANK_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellBlank texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum1, NUM_1_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellNum1 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum2, NUM_2_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellNum2 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum3, NUM_3_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellNum3 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum4, NUM_4_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellNum4 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum5, NUM_5_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellNum5 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum6, NUM_6_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellNum6 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum7, NUM_7_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellNum7 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum8, NUM_8_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Load CellNum8 texture failed!";
        }
    }

    // FONTS
    {
        if (ResourceVault::setFont(FontType::FontDefault, DEFAULT_FONT_PATH) == Result::failure) {
            std::cout << "Load FontDefault font failed!";
        }
    }
}


int main() {
    /*int choice;

    PLAYER newPlayer, oldPlayer;

    GAMEPREDICATE game_Feature, old_game_Feature;

    GAMECELL game_Board[MAX_ROW][MAX_COLUMN], old_game_Board[MAX_ROW][MAX_COLUMN];

    char mine_Board[MAX_ROW][MAX_COLUMN], old_mine_Board[MAX_ROW][MAX_COLUMN];
    do {
        welcomePlayer(choice);
        implementChoice(choice, mine_Board, old_mine_Board, game_Feature, old_game_Feature,
            newPlayer, oldPlayer, game_Board, old_game_Board);
    } while (true);*/

    // Phần này bị warning gì á tui k rõ nữa, ông xem làm gì đc k
    // C6262: Function uses '16396' bytes of stack: exceeds /analyze:stacksize '16384'. Consider moving some data to heap.
    //
    // Comment phần trên để chạy phần dưới
    //*************************************************************************

    registerResources();

    auto window = Window::getInstance();

    (*window)->initializeMenuScene();
    (*window)->initializeLeaderboardScene();
    (*window)->initializeDifficultiesScene();
    (*window)->initializePlayingScene(30, 30);

    (*window)->createWindow();
    bool change = true;

    while ((*window)->render_window.isOpen()) {
        sf::Event event;

        while ((*window)->render_window.pollEvent(event)) {
            change |= (*window)->handleSfEvents(event);
        }

        if (change) {
            (*window)->render_window.clear();
            (*window)->drawCurrentScene();
            (*window)->render_window.display();
        }

        switch ((*window)->getLastGameEvent()) {
        case GameEvent::QuitGame:
        {
            (*window)->closeWindow();
            break;
        }
        default:
            break;
        }

        change = false;

        // Limits frame per sec to 60.
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }
}