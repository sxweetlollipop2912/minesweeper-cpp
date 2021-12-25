#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Interface/Timer/Timer.h"
 
using std::string;


struct Time {
	int hours;
	int minutes;
	int seconds;
	bool STOP;

	Time(const int hours = 0, const int minutes = 0, const int seconds = 0, const bool STOP = false) {
		this->hours = hours;
		this->minutes = minutes;
		this->seconds = seconds;
		this->STOP = STOP;
	}

	Time(const sf::Time& time) {
		int sec = time.asSeconds();
		hours = sec / 3600;
		sec %= 3600;
		minutes = sec / 60;
		sec %= 60;
		seconds = sec;
		STOP = false;
	}

	operator sf::Time() const {
		return sf::seconds(seconds + minutes * 60 + hours * 3600);
	}
};

struct PLAYER {
	Time timePlay = Time(0, 0, 0, false);
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
