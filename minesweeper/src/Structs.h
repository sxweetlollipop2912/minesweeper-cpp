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


struct Color {
	float r;
	float g;
	float b;
	float a;
	Color(const float red = 0, const float green = 0, const float blue = 0, const float alpha = 255) {
		r = red, g = green, b = blue, a = alpha;
	}
	Color(const sf::Color& color) {
		r = color.r, g = color.g, b = color.b, a = color.a;
	}
	operator sf::Color() const { return sf::Color(r, g, b, a); }

	bool isValid() const {
		return r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255 && a >= 0 && a <= 255;
	}
};


struct AudioVisualCfg {
	struct Cfg {
		Color primary_color;
		Color secondary_color;
		sf::Time time;
		sf::Time transition_duration;
		float bubble_speed;

		Cfg(const Color primary_color = Color(-1, -1, -1),
			const Color secondary_color = Color(-1, -1, -1),
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
		std::sort(v.begin(), v.end(), [](const Cfg& e1, const Cfg& e2) {
			return e1.time < e2.time;
			});
	}
};