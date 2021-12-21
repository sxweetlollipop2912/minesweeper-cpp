#pragma once

#include <SFML/Graphics.hpp>

#include "../Text/Text.h"
#include "../Scenes/scene.h"
#include "../../Enums.h"
#include "../../Structs.h"


class Slider {
private:
	sf::Text sfText;

	sf::RectangleShape slider;
	sf::RectangleShape axis;
	Text text;

	int min_value;
	int max_value;

	sf::Vector2f top_left_pos;

	float slider_value;

	sf::Vector2i mouse_pos;
	bool sliding;


	void loadText(sf::Text& text, const int x, const int y, const std::string s, const int font_size);

public:
	Slider(const int min_value = 0, const int max_value = 0, const sf::Vector2f top_left_pos = sf::Vector2f(0, 0), const sf::Color axis_color = sf::Color(63, 63, 63), const sf::Color slider_color = sf::Color(192, 192, 192));

	float getSliderValue() const;

	// Centers slider on X-axis.
	// > Returns Result::failure if it is unable to center slider (due to out-of-bound top-left position after centering).
	// > otherwise, returns Result::success.
	Result centerSliderHorizontally(const float window_width);

	void setSliderValue(const float new_value);
	void setSliderPercentValue(const float new_percent_value);

	bool changeMousePosition(const sf::Vector2i& position);
	// Returns true if slider is pressed.
	// Otherwise, returns false.
	bool onMousePressed(const MouseActionType mouse_type);
	void onMouseReleased(const MouseActionType mouse_type);

	// Draws all textures and texts in the scene on an sf::RenderTarget object
	void draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing = true);
};