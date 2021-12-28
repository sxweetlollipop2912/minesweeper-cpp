#pragma once

#include <algorithm>
#include <map>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../Slider/Slider.h"
#include "../../Constants.h"
#include "../../Enums.h"
#include "../../Structs.h"


class Scene {
	friend class Window;

protected:
	const std::string STR_UNKNOWN = "unknown";

	sf::Sprite sprite;
	sf::Text text;

	SceneType scene_type;
	sf::VideoMode window_size;
	sf::Vector2i pos_mouse;
	bool use_double_lmb;

	// Only one pop-up holder for one scene.
	std::shared_ptr<Scene> pop_up;

	std::map <std::string, Button> buttons;
	std::map <std::string, GameEvent> buttons_event;
	std::map <std::string, Text> texts;

	std::map <GameEvent, SceneType> next_scene;
	std::string hovered_button;
	std::string pressed_button;


	void setWindowSize(const sf::VideoMode window_size);

	// Call on a mouse button released event.
	// Base method only handles single clicks, not double clicks or held-buttons.
	// Returns corresponding GameEvent.
	virtual GameEvent onMouseButtonReleased(const MouseActionType mouse_type);
	// Call on a mouse button pressed event.
	// Returns corresponding GameEvent.
	virtual GameEvent onMouseButtonPressed(const MouseActionType mouse_type);
	// Changes window graphics base on new mouse position.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	virtual bool changeMousePosition(const sf::Vector2i& pos);
	// Call on a lost window focus event.
	virtual void onLostFocus();
	// Call on a gained window focus event.
	virtual void onGainedFocus();
	// Call on every frame.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	virtual bool updatePerFrame();
	// Spawn a PopUp in current Scene base on current GameEvent.
	// Returns false if no PopUp is spawned running the method (either because another PopUp has already been spawned or there is no PopUp for the GameEvent.
	// Otherwise, returns true.
	bool spawnPopUp(const GameEvent game_event);

public:
	Scene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode(), const SceneType scene_type = SceneType::Unknown, const bool use_double_lmb = false);


	// Returns SceneType::Unknown if no next scene corresponding with game_event is found.
	SceneType getNextScene(const GameEvent game_event) const;
	
	// Draws all textures and texts in the scene on an sf::RenderTarget object
	virtual void draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing = true);
};