#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../src/Window/Window.h"
#include "../src/Scenes/menu_scene.h"
#include "../src/Button/Button.h"


int main() {
    Window window(800, 600, "minesweeper");
    window.createWindow();

    sf::Vector2u window_size = window.render_window.getSize();

    window.registerScene(SceneType::Menu, MenuScene(window_size));
    window.setCurrentSceneType(SceneType::Menu);

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
                window.setMousePosition(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
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