#include <iostream>

#include "Background.h"


float calDist(const sf::Vector2f p1, const sf::Vector2f p2 = sf::Vector2f(0, 0)) {
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	return sqrt(x * x + y * y);
}


Background::Background(const sf::VideoMode window_size, const sf::Color primary_color, const sf::Color secondary_color, const float circle_speed, const int number_of_circles, const float circle_radius) {

	this->window_size = window_size;

	cur_prim_color = des_prim_color = primary_color;
	cur_second_color = des_second_color = secondary_color;
	this->circle_speed = circle_speed;
	transition_duration = sf::microseconds(0);

	last_color_update = sf::microseconds(0);
	last_pos_update = sf::microseconds(0);
	clock.restart();

	background.setSize(sf::Vector2f(window_size.width, window_size.height ));
	background.setFillColor(cur_prim_color);

	circles.resize(number_of_circles);
	{
		for (int i = 0; i < circles.size(); i++) {
			auto& circle = circles[i];
			auto& shape = circle.shape;

			shape.setRadius(circle_radius);
			shape.setOrigin(sf::Vector2f(circle_radius, circle_radius));

			sf::Color color = secondary_color;
			color.a = 150;
			shape.setFillColor(color);

			{
				sf::Vector2f pos;
				pos.x = 1.2 * circle_radius + (rand() % (window_size.width - (int)(circle_radius * 2.2)));
				pos.y = 1.2 * circle_radius + (rand() % (window_size.height - (int)(circle_radius * 2.2)));
				shape.setPosition(pos);
			}
		}
	}

	{
		float angle = ((90 / (float)(number_of_circles + 1)) / 180) * PI;
		for(int i = 0; i < circles.size(); i++) {
			auto& veloc = circles[i].veloc;

			veloc.x = cos(angle * (float)(i + 1));
			veloc.y = sqrt(1 - veloc.x * veloc.x);

			veloc.x *= ((rand() % 2 == 0) ? -1 : 1);
			veloc.y *= ((rand() % 2 == 0) ? -1 : 1);
		}
	}
}


void Background::calCurrentColor() {
	if (transition_duration.asMilliseconds() < 0)
		return;

	auto time_elapsed = clock.getElapsedTime() - last_color_update;
	transition_duration -= time_elapsed;
	float rate = (1 / (float)transition_duration.asMilliseconds()) * (float)time_elapsed.asMilliseconds();

	{
		Color color = cur_prim_color;
		color.r = (des_prim_color.r - color.r) * rate + color.r;
		color.g = (des_prim_color.g - color.g) * rate + color.g;
		color.b = (des_prim_color.b - color.b) * rate + color.b;

		if ((des_prim_color.r - color.r) * (des_prim_color.r - cur_prim_color.r) > 0 &&
			(des_prim_color.g - color.g) * (des_prim_color.g - cur_prim_color.g) > 0 &&
			(des_prim_color.b - color.b) * (des_prim_color.b - cur_prim_color.b) > 0) {

			cur_prim_color = color;
		}
	}
	background.setFillColor(cur_prim_color);

	{
		Color color = cur_second_color;
		color.r = (des_second_color.r - color.r) * rate + color.r;
		color.g = (des_second_color.g - color.g) * rate + color.g;
		color.b = (des_second_color.b - color.b) * rate + color.b;
		color.a = 150;

		if ((des_second_color.r - color.r) * (des_second_color.r - cur_second_color.r) > 0 &&
			(des_second_color.g - color.g) * (des_second_color.g - cur_second_color.g) > 0 &&
			(des_second_color.b - color.b) * (des_second_color.b - cur_second_color.b) > 0) {

			cur_second_color = color;
		}
	}
	for (auto& circle : circles) {
		auto& shape = circle.shape;
		shape.setFillColor(cur_second_color);
	}

	last_color_update = clock.getElapsedTime();
}


void Background::calCurrentCirclesPos() {
	for (auto& circle : circles) {
		auto pos = circle.shape.getPosition();;
		auto radius = circle.shape.getRadius();

		auto& veloc = circle.veloc;
		
		if (((pos.x - radius) < EPS && veloc.x < 0) || ((float)(window_size.width - radius - pos.x) < EPS && veloc.x > 0)) {
			veloc.x = -veloc.x;
		}
		if (((pos.y - radius) < EPS && veloc.y < 0) || ((float)(window_size.height - radius - pos.y) < EPS && veloc.y > 0)) {
			veloc.y = -veloc.y;
		}
	}

	auto time_elapsed = (clock.getElapsedTime() - last_pos_update).asMilliseconds();
	float distance = circle_speed * (time_elapsed / (float)sf::seconds(1).asMilliseconds());

	for (auto& circle : circles) {
		auto veloc = circle.veloc;

		sf::Vector2f pos = circle.shape.getPosition();
		pos.x += veloc.x * distance;
		pos.y += veloc.y * distance;

		circle.shape.setPosition(pos);
	}

	last_pos_update = clock.getElapsedTime();
}


sf::Color Background::getCurrentPrimaryColor() const {
	return cur_prim_color;
}


sf::Color Background::getCurrentSecondaryColor() const {
	return cur_second_color;
}


int Background::getNumberOfCircles() const {
	return circles.size();
}


void Background::update() {
	calCurrentColor();
	calCurrentCirclesPos();
}


void Background::setNextColor(const sf::Color next_prim_color, const sf::Color next_second_color, const sf::Time transition_duration) {
	this->des_prim_color = next_prim_color;
	
	this->des_second_color = next_second_color;

	if (transition_duration.asSeconds() > 0) {
		this->transition_duration = transition_duration;
		last_color_update = clock.getElapsedTime();
	}
}


void Background::setCircleSpeed(const float speed) {
	if (speed > 0) {
		this->circle_speed = speed;
	}
}


void Background::setNextConfig(const AudioVisualCfg::Cfg& cfg) {
	setNextColor(cfg.primary_color, cfg.secondary_color, cfg.transition_duration);
	setCircleSpeed(cfg.bubble_speed);
}


DrawableList Background::getDrawableList(const bool is_focusing, const int rank) {
	DrawableList list;

	list.rects.push_back(DrawableList::DrawableRect(std::make_shared<sf::RectangleShape>(background), rank));
	
	for (auto& circle : circles) {
		list.circles.push_back(DrawableList::DrawableCircle(std::make_shared<sf::CircleShape>(circle.shape), rank + 1));
	}

	return list;
}
