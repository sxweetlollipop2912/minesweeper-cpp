// Run with configuration: release, x64

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../src/Window/Window.h"
#include "../src/ResourceVault/ResourceVault.h"
#include "../src/Scenes/menu_scene.h"
#include "../src/Scenes/playing_scene.h"
#include "../src/Button/Button.h"

#include <map>

int main() {
    ResourceVault::setTexture(TextureType::DefaultButton, DEFAULT_BUTTON_PATH);
    ResourceVault::setTexture(TextureType::CellClosed, CLOSED_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellFlagged, FLAGGED_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellBlank, BLANK_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellNum1, NUM_1_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellNum2, NUM_2_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellNum3, NUM_3_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellNum4, NUM_4_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellNum5, NUM_5_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellNum6, NUM_6_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellNum7, NUM_7_CELL_IMG_PATH);
    ResourceVault::setTexture(TextureType::CellNum8, NUM_8_CELL_IMG_PATH);

    ResourceVault::setFont(FontType::FontDefault, DEFAULT_FONT_PATH);


    Window window(1500, 1000, "minesweeper");
    window.createWindow();

    sf::Vector2u window_size = window.render_window.getSize();

    window.initializeMenuScene(window_size);
    window.initializePlayingScene(window_size, 30, 30);

    window.setCurrentSceneType(SceneType::Playing);

    while (window.render_window.isOpen()) {
        sf::Event event;
        while (window.render_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.closeWindow();

            switch (event.type) {
            case sf::Event::Closed:
                window.closeWindow();
                break;
            case sf::Event::Resized:
                window.onResize(event.size.width, event.size.height);
                break;
            case sf::Event::LostFocus:
                break;
            case sf::Event::GainedFocus:
                break;

            case sf::Event::MouseMoved:
                window.changeMousePosition(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
                break;
            case sf::Event::MouseButtonPressed:
                window.handleMouseButtonPress(event.mouseButton.button, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                break;
            default:
                break;
            }
        }

        window.render_window.clear();
       
        window.drawCurrentScene();

        window.render_window.display();
    }
}