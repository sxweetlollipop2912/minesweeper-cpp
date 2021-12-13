#pragma once

#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../../Constants.h"
#include "../../Structs.h"


struct Circle {
	sf::CircleShape shape;
	sf::Vector2f veloc;
	Circle() {}
};


class Background {
private:
	sf::VideoMode window_size;

	sf::Color cur_prim_color;
	sf::Color cur_second_color;
	sf::Color des_prim_color;
	sf::Color des_second_color;
	float color_changing_rate;
	float circle_speed;

	sf::RectangleShape background;
	std::vector <Circle> circles;

	sf::Clock clock;
	sf::Time last_color_update;
	sf::Time last_pos_update;


	void calCurrentColor();
	void calCurrentCirclesPos();

public:
	Background(const sf::VideoMode window_size = sf::VideoMode::getDesktopMode(), const sf::Color primary_color = BACKGROUMD_COLOR, const sf::Color secondary_color = BACKGROUMD_COLOR, const float color_changing_rate = 0, const float circle_speed = 50, const int number_of_circles = 10, const float circle_radius = 30);

	sf::Color getCurrentPrimaryColor() const;
	sf::Color getCurrentSecondaryColor() const;
	int getNumberOfCircles() const;

	void setNextColor(const sf::Color next_prim_color, const sf::Color next_second_color, const sf::Time transition_time);
	void setCircleSpeed(const float speed);

	DrawableList getDrawableList(const bool is_focusing = true, const int rank = 0);
};