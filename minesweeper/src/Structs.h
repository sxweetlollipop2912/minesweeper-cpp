#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
 
using std::string;


struct Timer {
	int hours;
	int minutes;
	int seconds;
	bool STOP = false;
};

struct PLAYER {
	std::string name;
	Timer timePlay = { 0,0,0, false };
	int level;
};

struct Records {
	std::vector <PLAYER> beginner;
	std::vector <PLAYER> intermediate;
	std::vector <PLAYER> expert;

	Records() {
		beginner.clear();
		intermediate.clear();
		expert.clear();
	}
};

struct GAMEPREDICATE {
	int MAX_ROW;
	int MAX_COLUMN;
	int maxMine;
	int flags;
	bool STOP = false;
};

struct GAMECELL {
	bool isOpened;
	bool isFlag;
	int mine_Count;
};


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
	struct DrawableCircle {
		std::shared_ptr<sf::CircleShape> circle;

		// higher rank drawables overwrite lower ones.
		int rank;

		DrawableCircle(const std::shared_ptr<sf::CircleShape> circle = nullptr, const int rank = 0) {
			this->circle = circle;
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
	std::vector <DrawableCircle> circles;

	DrawableList() {
		sprites.clear();
		texts.clear();
		rects.clear();
		circles.clear();
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
		for (auto e : list.circles) {
			circles.push_back(e);
		}
	}
};


struct AudioVisualCfg {
	struct Cfg {
		sf::Color primary_color;
		sf::Color secondary_color;
		sf::Time time;
		sf::Time transition_duration;
		float bubble_speed;

		Cfg(const sf::Color primary_color = sf::Color(0, 0, 0),
			const sf::Color secondary_color = sf::Color(0, 0, 0),
			const sf::Time transition_duration = sf::seconds(-1),
			const float bubble_speed = -1,
			const sf::Time time = sf::seconds(-1)) {
			this->primary_color = primary_color;
			this->secondary_color = secondary_color;
			this->time = time;
			this->transition_duration = transition_duration;
			this->bubble_speed = bubble_speed;
		}
	};
	std::vector <Cfg> v;

	// Sorts config vector base on time.
	void sort() {
		std::sort(v.begin(), v.end(), [&](const Cfg& e1, const Cfg& e2) {
			return e1.time < e2.time;
			});
	}
};