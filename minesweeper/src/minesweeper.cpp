﻿// Run with configuration: release, x64

#include <iostream>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game/GameTools.h"
#include "Constants.h"
#include "Interface/Window/Window.h"
#include "Interface/ResourceVault/ResourceVault.h"


void registerResources() {
    if (ResourceVault::setTexture(TextureType::ButtonDefault, DEFAULT_BUTTON_PATH) == Result::failure) {
        std::cout << "Loading ButtonDefault texture failed!";
    }
    if (ResourceVault::setTexture(TextureType::NextSong, DEFAULT_BUTTON_PATH) == Result::failure) {
        std::cout << "Loading NextSong texture failed!";
    }

    // PLAYING SCENE TEXTURES
    {
        if (ResourceVault::setTexture(TextureType::Scoreboard, SCOREBOARD_IMG_PATH) == Result::failure) {
            std::cout << "Loading Scoreboard texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellClosed, CLOSED_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellClosed texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellFlagged, FLAGGED_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellFlagged texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellMine, MINE_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellMine texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellBlank, BLANK_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellBlank texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum1, NUM_1_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum1 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum2, NUM_2_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum2 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum3, NUM_3_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum3 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum4, NUM_4_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum4 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum5, NUM_5_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum5 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum6, NUM_6_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum6 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum7, NUM_7_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum7 texture failed!";
        }
        if (ResourceVault::setTexture(TextureType::CellNum8, NUM_8_CELL_IMG_PATH) == Result::failure) {
            std::cout << "Loading CellNum8 texture failed!";
        }
    }

    // FONTS
    {
        if (ResourceVault::setFont(FontType::FontDefault, DEFAULT_FONT_PATH) == Result::failure) {
            std::cout << "Loading FontDefault font failed!";
        }
    }
}


int main() {
    srand(time(NULL));

    registerResources();

    auto window = Window::getInstance();

    (*window)->initializeMenuScene();
    (*window)->initializeLeaderboardScene();
    (*window)->initializeDifficultiesScene();
    (*window)->initializePlayingScene();

    (*window)->createWindow();

    while ((*window)->render_window->isOpen()) {
        sf::Event event;

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