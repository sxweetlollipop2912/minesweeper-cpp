#include "Background.h"


float dist2Points(const sf::Vector2f p1, const sf::Vector2f p2) {
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	return sqrt(x * x + y * y);
}


void Background::calCurrentColor() {
	auto time_elapsed = (clock.getElapsedTime() - last_color_update).asMilliseconds();
	float rate = color_changing_rate * (time_elapsed / sf::seconds(1).asMilliseconds());

	sf::Color color = background.getFillColor();
	color.r = (des_prim_color.r - color.r) * rate + color.r;
	color.g = (des_prim_color.r - color.g) * rate + color.g;
	color.b = (des_prim_color.r - color.b) * rate + color.b;
	background.setFillColor(color);

	for (auto circle : circles) {
		auto& shape = circle.shape;

		color = shape.getFillColor();
		color.r = (des_second_color.r - color.r) * rate + color.r;
		color.g = (des_second_color.r - color.g) * rate + color.g;
		color.b = (des_second_color.r - color.b) * rate + color.b;
		color.a = 220;
		shape.setFillColor(color);
	}

	last_color_update = clock.getElapsedTime();
}


void Background::calCurrentCirclesPos() {
	for (int i = 0; i < circles.size(); i++) for (int j = i + 1; j < circles.size(); j++) {
		auto& c1 = circles[i];
		auto& c2 = circles[j];
		if (std::abs(dist2Points(c1.shape.getPosition(), c2.shape.getPosition()) - 2 * c1.shape.getRadius()) > EPS) continue;

		auto tmp = c1.veloc;
		c1.veloc = c2.veloc;
		c2.veloc = tmp;
	}

	for (auto circle : circles) {
		auto pos = circle.shape.getPosition();
		auto radius = circle.shape.getRadius();

		auto& veloc = circle.veloc;
		
		if ((pos.x - radius < EPS) || (window_size.width - radius - pos.x < EPS)) {
			veloc.x = -veloc.x;
		}
		if ((pos.y - radius < EPS) || (window_size.height - radius - pos.y < EPS)) {
			veloc.y = -veloc.y;
		}
	}

	auto time_elapsed = (clock.getElapsedTime() - last_pos_update).asMilliseconds();
	float distance = circle_speed * (time_elapsed / sf::seconds(1).asMilliseconds());

	for (auto circle : circles) {
		auto veloc = circle.veloc;

		sf::Vector2f pos;
		pos.x += veloc.x * distance;
		pos.y += veloc.y * distance;

		circle.shape.setPosition(pos);
	}
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

	background.setSize(sf::Vector2f(window_size.width, window_size.height));
	background.setFillColor(cur_prim_color);

	circles.resize(number_of_circles);
	for (auto circle : circles) {
		auto& shape = circle.shape;

		shape.setRadius(circle_radius);
		shape.setOrigin(sf::Vector2f(circle_radius, circle_radius));

		sf::Color color = secondary_color;
		color.a = 220;
		shape.setFillColor(color);

		sf::Vector2f pos;
		pos.x = circle_radius + (rand() % (window_size.width - (int)circle_radius * 2));
		pos.y = circle_radius + (rand() % (window_size.height - (int)circle_radius * 2));
		shape.setPosition(pos);

		auto& veloc = circle.veloc;
		veloc.x = -1 + (rand() % 3);
		veloc.y = -1 + (rand() % 3);
		// normalizing
		float len = sqrt(veloc.x * veloc.x + veloc.y * veloc.y);
		veloc.x /= len;
		veloc.y /= len;
	}
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

	//list.drawables.push_back(DrawableList::Drawable(std::make_shared<sf::Drawable>(background), rank));
	
	for (auto circle : circles) {
		list.drawables.push_back(DrawableList::Drawable(std::make_shared<sf::Drawable>(circle.shape), rank + 1));
	}

	return list;
}
