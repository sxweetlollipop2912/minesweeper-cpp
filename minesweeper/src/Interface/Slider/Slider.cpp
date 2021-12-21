#include <iostream>

#include "Slider.h"


Slider::Slider(const int min, const int max, sf::Vector2f top_left_pos, const sf::Color axis_color, const sf::Color slider_color) {
	this->top_left_pos = top_left_pos;
	sliding = false;

	max_value = max;
	min_value = min;
	slider_value = min;

	text.setTextColor(DEFAULT_TEXT_COLOR);

	int axis_height = 10;
	int axis_width = 200;

	axis.setPosition(top_left_pos);
	axis.setOrigin(0, axis_height / 2);
	axis.setSize(sf::Vector2f(axis_width, axis_height));
	axis.setFillColor(axis_color);

	int slider_width = 20;
	int slider_height = 30;

	slider.setPosition(top_left_pos);
	slider.setOrigin(slider_width / 2, slider_height / 2);
	slider.setSize(sf::Vector2f(slider_width, slider_height));
	slider.setFillColor(slider_color);
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


bool Slider::onMousePressed(const MouseActionType mouse_type) {
	if (mouse_type == MouseActionType::LMB || mouse_type == MouseActionType::DoubleLMB) {

		if (slider.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
			sliding = true;
		}
		else {
			sliding = false;
		}
	}

	return sliding;
}


void Slider::onMouseReleased(const MouseActionType mouse_type) {
	if (mouse_type != MouseActionType::LMB && mouse_type != MouseActionType::DoubleLMB)
		return;

	sliding = false;
}


float Slider::getSliderValue() const {
	return slider_value;
}


Result Slider::centerSliderHorizontally(const float window_width) {
	float axis_width = axis.getSize().x;

	if (window_width < axis_width)
		return Result::failure;

	float old_x = top_left_pos.x;
	top_left_pos.x = (window_width / 2) - (axis_width / 2);

	if (top_left_pos.x < 0) {
		top_left_pos.x = old_x;

		return Result::failure;
	}

	axis.setPosition(top_left_pos);
	slider.setPosition(top_left_pos);

	return Result::success;
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
	loadText(sfText, top_left_pos.x - 10, top_left_pos.y + 5, std::to_string(min_value), 20);
	renderer->draw(sfText);

	loadText(sfText, top_left_pos.x + axis.getSize().x - 10, top_left_pos.y + 5, std::to_string(max_value), 20);
	renderer->draw(sfText);

	loadText(sfText, slider.getPosition().x - slider.getSize().x, slider.getPosition().y - slider.getSize().y, std::to_string((int)slider_value), 15);
	renderer->draw(sfText);

	renderer->draw(axis);
	renderer->draw(slider);
}