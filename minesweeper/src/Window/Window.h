#pragma once

#include <map>

#include <SFML/Window.hpp>
#include <SFML/Window.hpp>

#include "../Enums.h"
#include "../ResourceVault/ResourceVault.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Board/Board.h"
#include "../Scenes/scene.h"
#include "../Scenes/menu_scene.h"
#include "../Scenes/playing_scene.h"


class Window {
private:
	std::map <SceneType, std::shared_ptr<Scene>> map_scene;

	SceneType current_scene_type;
	GameEvent last_game_event;

	sf::Vector2i pos_mouse;
	// Locks mouse button when it is in use, i.e, a RMB won't be detected while a LMB is pressed and hasn't been released.
	MouseActionType lock_mouse_button;

	// Draws a menu scene on the window.
	void draw(MenuScene& scene);
	// Draws a playing scene on the window.
	void draw(PlayingScene& scene);
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

	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool handleGameEvents(const GameEvent game_event);

public:
	sf::RenderWindow render_window;
	int width, height;
	std::string title;

	// Initializes an untitled Window object with fullscreen size.
	Window() {
		this->width = sf::VideoMode::getDesktopMode().width;
		this->height = sf::VideoMode::getDesktopMode().height;
		this->title = "";

		auto menu_scene = std::shared_ptr<MenuScene>(new MenuScene());
		auto playing_scene = std::shared_ptr<PlayingScene>(new PlayingScene());
		menu_scene->initialize(sf::Vector2u(width, height));
		playing_scene->initialize(sf::Vector2u(width, height), 0, 0);

		map_scene[SceneType::Menu] = std::static_pointer_cast<Scene>(menu_scene);
		map_scene[SceneType::Playing] = std::static_pointer_cast<Scene>(playing_scene);

		current_scene_type = SceneType::Unkown;
		last_game_event = GameEvent::Unknown;
		lock_mouse_button = MouseActionType::Unknown;
	}

	// Initializes a Window object with desired width, height, title.
	Window(const int width, const int height, const std::string& title) {
		this->width = width;
		this->height = height;
		this->title = title;

		auto menu_scene = std::make_shared<MenuScene>();
		auto playing_scene = std::make_shared<PlayingScene>();
		menu_scene->initialize(sf::Vector2u(width, height));
		playing_scene->initialize(sf::Vector2u(width, height), 0, 0);

		map_scene[SceneType::Menu] = std::static_pointer_cast<Scene>(menu_scene);
		map_scene[SceneType::Playing] = std::static_pointer_cast<Scene>(playing_scene);

		current_scene_type = SceneType::Unkown;
		last_game_event = GameEvent::Unknown;
		lock_mouse_button = MouseActionType::Unknown;
	}


	// Creates (or recreates) the window with previously assigned width, height, title.
	// If the window was already created, closes it first.
	void createWindow();
	// Closes the window.
	void closeWindow();

	// Gets current mouse position.
	sf::Vector2i getMousePosition() const;
	// Gets current scene type.
	SceneType getCurrentSceneType() const;
	// Gets last game event.
	GameEvent getLastGameEvent() const;
	// Gets current scene as Scene object.
	std::shared_ptr<Scene> getCurrentScene();

	// Initializes menu scene for window.
	void initializeMenuScene(sf::Vector2u window_size);
	// Initializes playing scene for window.
	void initializePlayingScene(sf::Vector2u window_size, int board_rows, int board_cols);
	// Changes window graphics base on new mouse position.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos);
	// Sets current scene type.
	void setCurrentSceneType(const SceneType& type);

	// Actions on resizing window event.
	// This method is empty.
	void onResize(const int width, const int height);
	// Call upon a mouse button PRESS event.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool handleMouseButtonPress(const sf::Mouse::Button& button, const sf::Vector2i& position);
	// Call upon a mouse button RELEASE event.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool handleMouseButtonRelease(const sf::Mouse::Button& button, const sf::Vector2i& position);

	// Draws current scene.
	void drawCurrentScene();
};