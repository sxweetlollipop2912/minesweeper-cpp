#pragma once

#include <map>
#include <set>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../ResourceVault/ResourceVault.h"
#include "../AudioManager/AudioManager.h"
#include "../Background/Background.h"
#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Board/Board.h"
#include "../Scenes/scene.h"
#include "../Scenes/menu_scene.h"
#include "../Scenes/playing_scene.h"
#include "../Scenes/leaderboard_scene.h"
#include "../Scenes/difficulties_scene.h"
#include "../../Comms/Comms.h"
#include "../../Enums.h"
#include "../../Constants.h"
#include "../../Structs.h"


// This is a singleton.
class Window {
	friend Result Comms::gameInfoSending(const GameInfo info);

private:
	static Window* instance;

	Background background;
	AudioManager audio_manager;

	std::map <SceneType, std::shared_ptr<Scene>> scenes;
	std::set <SceneType> constantly_changing_scenes;

	Comms::GameInfo current_game_info;
	Comms::InterfaceInfo current_interface_info;

	SceneType current_scene_type;
	GameEvent last_game_event;

	sf::Vector2i pos_mouse;
	// Locks mouse button when it is in use, i.e, a RMB won't be detected while a LMB is pressed and hasn't been released.
	MouseActionType lock_mouse_button;

	Window(const sf::VideoMode& window_size = sf::VideoMode(1500, 1000), const std::string& title = TITLE, const int window_style = sf::Style::Close);

	// Draws a list of drawable objects on the window.
	void draw(const DrawableList& list);
	// Draws a sf::Sprite on the window.
	void draw(const sf::Sprite& sprite);
	// Draws a sf::Text on the window.
	void draw(const sf::Text& text);
	// Draws a RectangleShape on window.
	void draw(const sf::RectangleShape& rect);
	// Draws a CircleShape on window.
	void draw(const sf::CircleShape& circle);
	// Draws a text on the window.
	void draw(Text& text);
	// Draws a button on the window.
	void draw(Button& button, const bool isHovered = false);

	void updateGameInfo(const Comms::GameInfo info);
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool handleGameEvents(const GameEvent game_event);
	// Changes window graphics base on new mouse position.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos);
	// Sets current scene type.
	void setCurrentSceneType(const SceneType& type);

	// Call upon a mouse button PRESS event.
	// Cannot detect a DoubleLMB at this stage.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool onMouseButtonPressed(const sf::Mouse::Button& button, const sf::Vector2i& position);
	// Call upon a mouse button RELEASE event.
	// Returns true if there are visual changes.
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
	// Returns true if there are visual changes.
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
	// Initializes/Resets showing difficulties scene for window.
	void initializeDifficultiesScene();
	// Initializes/Resets playing scene for window.
	void initializePlayingScene(const int board_rows = -1, const int board_cols = -1);

	// Call to update automatic features (i.e. timer while playing) at each frame.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool updatePerFrame();
	// Draws current scene.
	void drawCurrentScene();
};