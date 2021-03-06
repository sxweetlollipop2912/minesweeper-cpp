// Run with configuration: release, x64

#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "Interface/Window/Window.h"
#include "Interface/ResourceManager/ResourceManager.h"
#include "Constants.h"


void registerResources() {
    if ((*ResourceManager::getInstance())->setTexture(TextureType::DefaultButton, DEFAULT_BUTTON_PATH) == Result::failure) {
        std::cout << "Loading ButtonDefault texture failed!";
    }
    if ((*ResourceManager::getInstance())->setTexture(TextureType::ReturnButton, RETURN_BUTTON_PATH) == Result::failure) {
        std::cout << "Loading ReturnButton texture failed!";
    }
    if ((*ResourceManager::getInstance())->setTexture(TextureType::YesNoButton, YES_NO_BUTTON_PATH) == Result::failure) {
        std::cout << "Loading YesNoButton texture failed!";
    }
    if ((*ResourceManager::getInstance())->setTexture(TextureType::PopUpBackground, POP_UP_BACKGROUND) == Result::failure) {
        std::cout << "Loading PopUpBackground texture failed!";
    }
    if ((*ResourceManager::getInstance())->setTexture(TextureType::SkipSong, SKIP_SONG_BUTTON_PATH) == Result::failure) {
        std::cout << "Loading SkipSong texture failed!";
    }

    // PLAYING SCENE TEXTURES
    {
        if ((*ResourceManager::getInstance())->setTexture(TextureType::Scoreboard, SCOREBOARD_IMG_PATH) == Result::failure) {
            std::cout << "Loading Scoreboard texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellClosed, CLOSED_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellClosed texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellFlagged, FLAGGED_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellFlagged texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellMine, MINE_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellMine texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellBlank, BLANK_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellBlank texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellNum1, NUM_1_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum1 texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellNum2, NUM_2_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum2 texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellNum3, NUM_3_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum3 texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellNum4, NUM_4_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum4 texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellNum5, NUM_5_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum5 texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellNum6, NUM_6_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum6 texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellNum7, NUM_7_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum7 texture failed!";
        }
        if ((*ResourceManager::getInstance())->setTexture(TextureType::CellNum8, NUM_8_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum8 texture failed!";
        }
    }

    // FONTS
    {
        if ((*ResourceManager::getInstance())->setFont(FontType::FontDefault, DEFAULT_FONT_PATH) == Result::failure) {
            std::cout << "Loading FontDefault font failed!";
        }
    }
}


int main(int argc, char** argv) {
    // Add `assets` and `data` folder next to `.exe` file, or remove these 2 lines.
    // This sets working directory the same location as `.exe` file.
    // This is a workaround on Linux-based OS.
    {
        //std::string path = argv[0];
        //std::filesystem::current_path(path.substr(0, path.find_last_of('/')));
    }

    srand(time(nullptr));

    registerResources();

    auto window = Window::getInstance();
    (*window)->initialize();

    (*window)->createWindow();

    while ((*window)->render_window->isOpen()) {
        sf::Event event{};

        while ((*window)->render_window->pollEvent(event)) {
            (*window)->handleSfEvents(event);
        }

        (*window)->updatePerFrame();
        (*window)->drawCurrentScene();

        switch ((*window)->getLastGameEvent()) {
        case GameEvent::QuitGame:
        {
            (*window)->closeWindow();
            break;
        }
        default:
            break;
        }

        // Limits receiving event and responding rate to about 120 times per sec.
        // Last benchmark: about 75 fps on average.
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 120));
    }
}