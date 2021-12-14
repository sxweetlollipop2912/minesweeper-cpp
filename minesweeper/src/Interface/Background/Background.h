#pragma once

#include <stdlib.h>
#include <algorithm>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../../Constants.h"
#include "../../Structs.h"

constexpr auto PI = 3.1415926535897932384626;


struct Circle {
	sf::CircleShape shape;
	sf::Vector2f veloc;
	Circle() {}
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
};


class Background {
private:
	sf::VideoMode window_size;

	Color cur_prim_color;
	Color cur_second_color;
	Color des_prim_color;
	Color des_second_color;
	sf::Time transition_duration;
	float circle_speed;

	sf::RectangleShape background;
	std::vector <Circle> circles;

	sf::Clock clock;
	sf::Time last_color_update;
	sf::Time last_pos_update;


	void calCurrentColor();
	void calCurrentCirclesPos();

public:
	Background(const sf::VideoMode window_size = sf::VideoMode::getDesktopMode(), const sf::Color primary_color = BACKGROUMD_COLOR, const sf::Color secondary_color = BACKGROUMD_COLOR, const float circle_speed = 80, const int number_of_circles = 13, const float circle_radius = 150);

	sf::Color getCurrentPrimaryColor() const;
	sf::Color getCurrentSecondaryColor() const;
	int getNumberOfCircles() const;

	void update();

	void setNextColor(const sf::Color next_prim_color, const sf::Color next_second_color, const sf::Time transition_duration);
	void setCircleSpeed(const float speed);
	void setNextConfig(const AudioVisualCfg::Cfg& config);

	DrawableList getDrawableList(const bool is_focusing = true, const int rank = 0);
};