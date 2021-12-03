#pragma once

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Text/Text.h"
#include "../../Constants.h"


class Scene {
	friend class Window;
	friend class MenuScene;
	friend class PlayingScene;
	friend class PopUp;

protected:
	const std::string STR_UNKNOWN = "unknown";

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
	// Returns true if there are changes in the scene.
	// Otherwise, returns false
	virtual bool changeMousePosition(const sf::Vector2i& pos);
	// Spawn a PopUp in current Scene base on current GameEvent.
	// Returns false if no PopUp is spawned running the method (either because another PopUp has already been spawned or there is no PopUp for the GameEvent.
	// Otherwise, returns true.
	bool spawnPopUp(const GameEvent game_event);

public:
	Scene(const SceneType scene_type = SceneType::Unkown) {
		this->scene_type = scene_type;

		pop_up = nullptr;
		buttons.clear();
		texts.clear();
		next_scene.clear();

		buttons_event[STR_UNKNOWN] = GameEvent::Unknown;
		hovered_button = STR_UNKNOWN;
		pos_mouse = sf::Vector2i(-1, -1);
	}


	// Returns SceneType::Unknown if no next scene corresponding with game_event is found.
	SceneType getNextScene(const GameEvent game_event) const;


	struct DrawableList {
		struct DrawableSprite {
			std::shared_ptr<sf::Sprite> sprite;

			// higher rank drawables overwrite lower ones.
			int rank;

			DrawableSprite(const std::shared_ptr<sf::Sprite> sprite = nullptr, const int rank = 0) {
				this->sprite = sprite;
				this->rank = rank;
			}
		};
		struct DrawableRect {
			std::shared_ptr<sf::RectangleShape> rect;

			// higher rank drawables overwrite lower ones.
			int rank;

			DrawableRect(const std::shared_ptr<sf::RectangleShape> rect = nullptr, const int rank = 0) {
				this->rect = rect;
				this->rank = rank;
			}
		};
		struct DrawableText {
			std::shared_ptr<sf::Text> text;

			// higher rank drawables overwrite lower ones.
			int rank;

			DrawableText(const std::shared_ptr<sf::Text> text = nullptr, const int rank = 0) {
				this->text = text;
				this->rank = rank;
			}
		};

		std::vector <DrawableSprite> sprites;
		std::vector <DrawableText> texts;
		std::vector <DrawableRect> rects;

		DrawableList() {
			sprites.clear();
			texts.clear();
			rects.clear();
		}

		void append(const DrawableList& list) {
			for (auto e : list.sprites) {
				sprites.push_back(e);
			}
			for (auto e : list.texts) {
				texts.push_back(e);
			}
			for (auto e : list.rects) {
				rects.push_back(e);
			}
		}
	};
	
	// Gets a DrawableList object that contains all sprites and texts in the scene.
	virtual DrawableList getDrawableList(const bool is_focusing = true, const int rank = 0);
};