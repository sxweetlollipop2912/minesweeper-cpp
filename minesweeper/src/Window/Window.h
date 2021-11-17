#pragma once

#include <map>

#include <SFML/Window.hpp>
#include <SFML/Window.hpp>

#include "../Enums.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Board/Board.h"
#include "../Scenes/scene.h"


class Window {
private:
	std::map <SceneType, Scene> map_scene;
	SceneType current_scene;

	sf::Vector2i pos_mouse;

	// Draws a scene on the window.
	void draw(Scene& scene);
	// Draws a sprite on the window.
	void draw(const sf::Sprite& sprite);
	// Draws a text on the window.
	void draw(const sf::Text& text);
	// Draws a text on the window.
	void draw(Text& text);
	// Draws a button on the window.
	void draw(Button& button, const bool isHovered = false);

public:
	sf::RenderWindow render_window;
	int width, height;
	std::string title;

	// Initializes an untitled Window object with fullscreen size.
	Window() {
		this->width = sf::VideoMode::getDesktopMode().width;
		this->height = sf::VideoMode::getDesktopMode().height;
		this->title = "";

		map_scene.clear();
		current_scene = SceneType::Unkown;
	}
	// Initializes a Window object with desired width, height, title.
	Window(const int width, const int height, const std::string& title) {
		this->width = width;
		this->height = height;
		this->title = title;

		map_scene.clear();
		current_scene = SceneType::Unkown;
	}

	// Gets current mouse position.
	sf::Vector2i getMousePosition() const;
	// Gets current scene type.
	SceneType getCurrentSceneType() const;

	// Changes window graphics base on new mouse position.
	void changeMousePosition(const sf::Vector2i& pos);
	// Registers a scene.
	void registerScene(const SceneType& type, const Scene& scene);
	// Sets current scene type.
	void setCurrentSceneType(const SceneType& type);

	// Creates (or recreates) the window with previously assigned width, height, title.
	// If the window was already created, closes it first.
	void createWindow();
	// Closes the window.
	void closeWindow();

	// Actions on resizing window event.
	// This method is empty.
	void onResize(const int width, const int height);
	// Call on a mouse button event.
	Result handleMouseButtonPress(const sf::Mouse::Button& button, const sf::Vector2i& position);

	// Draws current scene.
	void drawCurrentScene();
};