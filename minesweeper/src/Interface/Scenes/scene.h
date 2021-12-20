#pragma once

#include <algorithm>
#include <map>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../../Constants.h"
#include "../../Enums.h"
#include "../../Structs.h"


class Scene {
	friend class Window;

protected:
	const std::string STR_UNKNOWN = "unknown";
	const std::string STR_NEXT_SONG = "next_song";

	SceneType scene_type;
	sf::VideoMode window_size;
	sf::Vector2i pos_mouse;

	// Only one pop-up holder for one scene.
	std::shared_ptr<Scene> pop_up;

	std::map <std::string, Button> buttons;
	std::map <std::string, GameEvent> buttons_event;
	std::map <std::string, Text> texts;

	std::map <GameEvent, SceneType> next_scene;
	std::string hovered_button;


	void setWindowSize(const sf::VideoMode window_size);

	// Call on a mouse button released event.
	// Returns corresponding GameEvent.
	virtual GameEvent onMouseButtonReleased(const MouseActionType mouse_type);
	// Call on a mouse button pressed event.
	// Returns corresponding GameEvent.
	virtual GameEvent onMouseButtonPressed(const MouseActionType mouse_type);
	// Changes window graphics base on new mouse position.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	virtual bool changeMousePosition(const sf::Vector2i& pos);
	// Spawn a PopUp in current Scene base on current GameEvent.
	// Returns false if no PopUp is spawned running the method (either because another PopUp has already been spawned or there is no PopUp for the GameEvent.
	// Otherwise, returns true.
	bool spawnPopUp(const GameEvent game_event);

public:
	Scene(const sf::VideoMode& window_size = sf::VideoMode::getDesktopMode(), const SceneType scene_type = SceneType::Unknown);


	// Returns SceneType::Unknown if no next scene corresponding with game_event is found.
	SceneType getNextScene(const GameEvent game_event) const;
	
	// Gets a DrawableList object that contains all sprites and texts in the scene.
	virtual DrawableList getDrawableList(const bool is_focusing = true, const int rank = 0);
};