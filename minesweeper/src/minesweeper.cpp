// Run with configuration: release, x64

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../src/Window/Window.h"
#include "../src/ResourceVault/ResourceVault.h"
#include "../src/Scenes/menu_scene.h"
#include "../src/Scenes/playing_scene.h"
#include "../src/Button/Button.h"


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
    registerResources();

    Window window(sf::VideoMode(1500, 1000), "minesweeper");
    window.createWindow();

    sf::VideoMode window_size = sf::VideoMode(window.render_window.getSize().x, window.render_window.getSize().y, sf::Style::Close);

    window.initializeMenuScene();
    window.initializePlayingScene(30, 30);

    window.setCurrentSceneType(SceneType::Menu);

    bool change = true;
    while (window.render_window.isOpen()) {
        sf::Event event;

        while (window.render_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.closeWindow();

            switch (event.type) {
            case sf::Event::Closed:
                window.closeWindow();
                break;
            case sf::Event::LostFocus:
                break;
            case sf::Event::GainedFocus:
                break;

            case sf::Event::MouseMoved:
                change |= window.changeMousePosition(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                break;
            case sf::Event::MouseButtonPressed:
                change |= window.handleMouseButtonPress(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                break;
            case sf::Event::MouseButtonReleased:
                change |= window.handleMouseButtonRelease(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                break;
            default:
                break;
            }
        }

        switch (window.getLastGameEvent()) {
        case GameEvent::QuitGame:
        {
            window.closeWindow();
            break;
        }

        default:
            break;
        }

        if (change) {
            window.render_window.clear();
            window.drawCurrentScene();
            window.render_window.display();
        }

        change = false;
    }
}