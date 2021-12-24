#include <iostream>

#include "Slider.h"


Slider::Slider(const int min, const int max, const int init_value, sf::Vector2f top_left_pos, const int axis_width, const int axis_height, const bool visible_numbers, const sf::Color axis_color, const sf::Color slider_color) {
	this->top_left_pos = top_left_pos;
	sliding = false;

	max_value = max;
	min_value = min;
	slider_value = min;
	this->visible_numbers = visible_numbers;

	text.setTextColor(DEFAULT_TEXT_COLOR);

	axis.setPosition(top_left_pos);
	axis.setOrigin(0, axis_height / 2);
	axis.setSize(sf::Vector2f(axis_width, axis_height));
	axis.setFillColor(axis_color);

	float radius = axis_height * 1.5;

	slider.setOrigin(radius, radius);
	slider.setPosition(top_left_pos);
	slider.setRadius(radius);
	slider.setFillColor(slider_color);
	
	int init = std::max(min, std::min(max, init_value));
	setSliderValue(init);
}


void Slider::loadText(sf::Text& SfText, const int x, const int y, const std::string s, const int font_size) {
	text.setFontSize(font_size);
	text.setTopLeftPos(sf::Vector2f(x, y));
	text.setText(s);

	text.getSfText(SfText);
}


bool Slider::changeMousePosition(const sf::Vector2i& position) {
	mouse_pos = position;

	if (sliding == true) {
		float x = std::min(top_left_pos.x + (float)axis.getSize().x, std::max((float)mouse_pos.x, top_left_pos.x));

		if (x == slider.getPosition().x)
			return false;

		slider.setPosition(x, top_left_pos.y);
		slider_value = (min_value + ((slider.getPosition().x - top_left_pos.x) / axis.getSize().x * (max_value - min_value)));
	}

	return sliding;
}


bool Slider::onMouseButtonPressed(const MouseActionType mouse_type) {
	if (mouse_type == MouseActionType::FirstLMB || mouse_type == MouseActionType::SecondLMB) {
		if (slider.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
			sliding = true;
		}
		else if (mouse_pos.x - axis.getPosition().x >= 0 &&
			mouse_pos.x - axis.getPosition().x <= axis.getSize().x &&
			std::abs(mouse_pos.y - axis.getPosition().y) <= slider.getRadius() * 2.0f) {

			sliding = true;
			changeMousePosition(mouse_pos);
		}
		else {
			sliding = false;
		}
	}

	return sliding;
}


void Slider::onMouseButtonReleased(const MouseActionType mouse_type) {
	if (mouse_type == MouseActionType::FirstLMB || mouse_type == MouseActionType::SecondLMB) {
		sliding = false;
	}
}


float Slider::getSliderValue() const {
	return slider_value;
}


void Slider::centerSliderHorizontally(const float space_width, const float left_pos_x) {
	float axis_width = axis.getSize().x;
	top_left_pos.x = left_pos_x + (space_width / 2) - (axis_width / 2);
	setTopLeftPos(top_left_pos);
}


void Slider::setTopLeftPos(const sf::Vector2f& top_left_pos) {
	sf::Vector2f diff;
	diff.x = top_left_pos.x - axis.getPosition().x;
	diff.y = top_left_pos.y - axis.getPosition().y;

	auto slider_pos = slider.getPosition();
	slider_pos.x += diff.x;
	slider_pos.y += diff.y;

	axis.setPosition(top_left_pos);
	slider.setPosition(slider_pos);
}


void Slider::setSliderValue(const float newValue) {
	if (newValue >= min_value && newValue <= max_value) {
		slider_value = newValue;
		float diff = max_value - min_value;
		float diff2 = newValue - min_value;
		float zzz = axis.getSize().x / diff;
		float pos_x = zzz*diff2;
		pos_x += top_left_pos.x;
		slider.setPosition(pos_x, top_left_pos.y);
	}
}


void Slider::setSliderPercentValue(const float new_percent_value) {
	if (new_percent_value >= 0 && new_percent_value <= 100) {
		slider_value = new_percent_value / 100 * max_value;
		slider.setPosition(top_left_pos.x + (axis.getSize().x * new_percent_value / 100), top_left_pos.y);
	}
}


void Slider::draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing) {
	if (visible_numbers) {
		loadText(sfText, top_left_pos.x - slider.getRadius() - 18, top_left_pos.y - (20 / 2), std::to_string(min_value), 20);
		renderer->draw(sfText);

		loadText(sfText, top_left_pos.x + axis.getSize().x + slider.getRadius() + 5, top_left_pos.y - (20 / 2), std::to_string(max_value), 20);
		renderer->draw(sfText);

		loadText(sfText, slider.getPosition().x - slider.getRadius() / (float)2, slider.getPosition().y - slider.getRadius() * 2 - (15 / (float)2), std::to_string((int)slider_value), 15);
		renderer->draw(sfText);
	}

	renderer->draw(axis);
	renderer->draw(slider);
}