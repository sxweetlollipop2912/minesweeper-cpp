#include <iostream>

#include "Background.h"


float dist2Points(const sf::Vector2f p1, const sf::Vector2f p2 = sf::Vector2f(0, 0)) {
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	return sqrt(x * x + y * y);
}


Background::Background(const sf::VideoMode window_size, const sf::Color primary_color, const sf::Color secondary_color, const float color_changing_rate, const float circle_speed, const int number_of_circles, const float circle_radius) {

	this->window_size = window_size;

	cur_prim_color = des_prim_color = primary_color;
	cur_second_color = des_second_color = secondary_color;
	this->circle_speed = circle_speed;
	this->color_changing_rate = color_changing_rate;

	last_color_update = sf::microseconds(0);
	last_pos_update = sf::microseconds(0);
	clock.restart();

	background.setSize(sf::Vector2f(window_size.width, window_size.height ));
	background.setFillColor(cur_prim_color);

	circles.resize(number_of_circles);
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

		{
			auto& veloc = circle.veloc;
			
			bool ok = false;
			while (!ok) {
				do {
					veloc.x = ((rand() % 2 == 0) ? -1 : 1) * (1 + rand() % 10000);
					veloc.y = ((rand() % 2 == 0) ? -1 : 1) * (1 + rand() % 10000);
					// normalizing
					float len = sqrt(veloc.x * veloc.x + veloc.y * veloc.y);
					veloc.x /= len;
					veloc.y /= len;
				} while (atan(veloc.x / veloc.y) < ((20 / (float)180) * PI) || atan(veloc.y / veloc.x) < ((20 / (float)180) * PI));

				ok = true;
				for (int j = 0; j < i && ok; j++) {
					auto v1 = veloc;
					v1.x = std::abs(v1.x), v1.y = std::abs(v1.y);
					auto v2 = circles[j].veloc;
					v2.x = std::abs(v2.x), v2.y = std::abs(v2.y);
					auto cos = ((v1.x * v2.x + v1.y * v2.y) / (float)(dist2Points(v1) * dist2Points(v2)));

					//std::cout << std::abs(acos(cos)) << ' ' << ((30 / (float)180) * PI) << '\n';
					if (std::abs(acos(cos)) < ((20 / (float)180) * PI)) ok = false;
				}
			}
		}
	}
}


void Background::calCurrentColor() {
	auto time_elapsed = (clock.getElapsedTime() - last_color_update).asMilliseconds();
	float rate = color_changing_rate * (time_elapsed / sf::seconds(1).asMilliseconds());

	sf::Color color = background.getFillColor();
	color.r = (des_prim_color.r - color.r) * rate + color.r;
	color.g = (des_prim_color.r - color.g) * rate + color.g;
	color.b = (des_prim_color.r - color.b) * rate + color.b;
	background.setFillColor(color);

	for (auto& circle : circles) {
		auto& shape = circle.shape;

		color = shape.getFillColor();
		color.r = (des_second_color.r - color.r) * rate + color.r;
		color.g = (des_second_color.r - color.g) * rate + color.g;
		color.b = (des_second_color.r - color.b) * rate + color.b;
		color.a = 150;
		shape.setFillColor(color);
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
	float distance = (float)circle_speed * (float)(time_elapsed / (float)sf::seconds(1).asMilliseconds());

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


void Background::setNextColor(const sf::Color next_prim_color, const sf::Color next_second_color, const sf::Time transition_time) {
	this->des_prim_color = next_prim_color;
	this->des_second_color = next_second_color;

	auto sec = transition_time.asSeconds();
	color_changing_rate = 1 / (float)sec;
}


void Background::setCircleSpeed(const float speed) {
	this->circle_speed = speed;
}


DrawableList Background::getDrawableList(const bool is_focusing, const int rank) {
	DrawableList list;

	list.rects.push_back(DrawableList::DrawableRect(std::make_shared<sf::RectangleShape>(background), rank));
	
	for (auto& circle : circles) {
		list.circles.push_back(DrawableList::DrawableCircle(std::make_shared<sf::CircleShape>(circle.shape), rank + 1));
	}

	return list;
}
