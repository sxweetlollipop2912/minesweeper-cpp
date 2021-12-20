#pragma once

#include <stdlib.h>
#include <algorithm>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../../Constants.h"
#include "../../Structs.h"

constexpr auto PI = 3.1415926535897932384626;
constexpr auto TRANSPARENT_ALPHA = 150;


struct Circle {
	sf::CircleShape shape;
	sf::Vector2f veloc;
	Circle() {}
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
	Background(const sf::VideoMode window_size = sf::VideoMode::getDesktopMode(), 
		const sf::Color primary_color = DEFAULT_VISUAL_CONFIG.primary_color, 
		const sf::Color secondary_color = DEFAULT_VISUAL_CONFIG.secondary_color, 
		const float circle_speed = DEFAULT_VISUAL_CONFIG.bubble_speed, 
		const int number_of_circles = NUMBER_OF_BUBBLES, 
		const float circle_radius = BUBBLE_RADIUS);

	sf::Color getCurrentPrimaryColor() const;
	sf::Color getCurrentSecondaryColor() const;
	int getNumberOfCircles() const;

	void update();

	void setNextColor(const Color next_prim_color, const Color next_second_color, const sf::Time transition_duration);
	void setCircleSpeed(const float speed);
	void setNextConfig(const AudioVisualCfg::Cfg& config);

	DrawableList getDrawableList(const bool is_focusing = true, const int rank = 0);
};