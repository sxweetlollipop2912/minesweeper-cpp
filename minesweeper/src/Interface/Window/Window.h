#pragma once

#include <map>

#include <SFML/Window.hpp>
#include <SFML/Window.hpp>

#include "../../Enums.h"
#include "../ResourceVault/ResourceVault.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Board/Board.h"
#include "../Scenes/scene.h"
#include "../Scenes/menu_scene.h"
#include "../Scenes/playing_scene.h"
#include "../Scenes/leaderboard_scene.h"
#include "../../Comms/Comms.h"


// This is a singleton.
class Window {
	friend Result Comms::gameInfoSending(const GameInfo info);

private:
	static Window* instance;


	Window(const sf::VideoMode& window_size = sf::VideoMode(1500, 1000), const std::string& title = TITLE, const int window_style = sf::Style::Close) {
		this->window_size = window_size;
		this->title = title;
		this->window_style = window_style;

		auto menu_scene = std::shared_ptr<MenuScene>(new MenuScene(window_size));
		auto playing_scene = std::shared_ptr<PlayingScene>(new PlayingScene(window_size, 0, 0));

		map_scene[SceneType::Menu] = std::static_pointer_cast<Scene>(menu_scene);
		map_scene[SceneType::Playing] = std::static_pointer_cast<Scene>(playing_scene);

		current_scene_type = SceneType::Menu;
		last_game_event = GameEvent::Unknown;
		lock_mouse_button = MouseActionType::Unknown;
		pos_mouse = sf::Vector2i(-1, -1);
	}


	std::map <SceneType, std::shared_ptr<Scene>> map_scene;

	SceneType current_scene_type;
	GameEvent last_game_event;

	sf::Vector2i pos_mouse;
	// Locks mouse button when it is in use, i.e, a RMB won't be detected while a LMB is pressed and hasn't been released.
	MouseActionType lock_mouse_button;

	// Draws a scene on the window.
	void draw(Scene& scene);
	// Draws a sf::Sprite on the window.
	void draw(const sf::Sprite& sprite);
	// Draws a sf::Text on the window.
	void draw(const sf::Text& text);
	// Draws a text on the window.
	void draw(Text& text);
	// Draws a button on the window.
	void draw(Button& button, const bool isHovered = false);

	Result updateGameInfo(const Comms::GameInfo info);
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool handleGameEvents(const GameEvent game_event);
	// Changes window graphics base on new mouse position.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos);
	// Sets current scene type.
	void setCurrentSceneType(const SceneType& type);

	// Call upon a mouse button PRESS event.
	// Cannot detect a DoubleLMB at this stage.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool onMouseButtonPressed(const sf::Mouse::Button& button, const sf::Vector2i& position);
	// Call upon a mouse button RELEASE event.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool onMouseButtonReleased(const sf::Mouse::Button& button, const sf::Vector2i& position);

public:
	sf::RenderWindow render_window;
	sf::VideoMode window_size;
	int window_style;
	std::string title;


	/**
	 * Singletons should not be cloneable.
	 */
	Window(Window& other) = delete;
	/**
	 * Singletons should not be assignable.
	 */
	void operator=(const Window&) = delete;

	static std::shared_ptr<Window*> getInstance();


	// Creates (or recreates) the window with previously assigned width, height, title.
	// If the window was already created, closes it first.
	void createWindow();
	// Closes the window.
	void closeWindow();
	// Makes changes in the game according to sf::Event.
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	bool handleSfEvents(const sf::Event& event);

	// Gets current mouse position.
	sf::Vector2i getMousePosition() const;
	// Gets current scene type.
	SceneType getCurrentSceneType() const;
	// Gets last game event.
	GameEvent getLastGameEvent() const;
	// Gets current scene as Scene object.
	std::shared_ptr<Scene> getCurrentScene();

	// Initializes/Resets menu scene for window.
	void initializeMenuScene();
	// Initializes/Resets menu scene for window.
	void initializeLeaderboardScene();
	// Initializes/Resets playing scene for window.
	void initializePlayingScene(const int board_rows, const int board_cols);

	// Draws current scene.
	void drawCurrentScene();
};