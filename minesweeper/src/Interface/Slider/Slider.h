#pragma once

#include <SFML/Graphics.hpp>

#include "../Text/Text.h"
#include "../Scenes/scene.h"
#include "../../Enums.h"
#include "../../Structs.h"


class Slider {
private:
    sf::Text sfText;

	sf::CircleShape slider;
	sf::RectangleShape axis;
	Text text;

	int min_value;
	int max_value;
	bool visible_numbers;

	sf::Vector2f top_left_pos;

	float slider_value;

	sf::Vector2i mouse_pos;
	bool sliding;


	void loadText(sf::Text& text, const int x, const int y, const std::string s, const int font_size);

public:
	Slider(const int min_value = 0, const int max_value = 0, const int init_value = 0, const sf::Vector2f top_left_pos = sf::Vector2f(0, 0), const int axis_width = 200, const int axis_height = 10, const bool visible_numbers = true, const sf::Color axis_color = sf::Color(63, 63, 63), const sf::Color slider_color = sf::Color(192, 192, 192));

	float getSliderValue() const;

	// Centers slider on X-axis.
	void centerSliderHorizontally(const float space_width, const float left_pos_x = 0);
	void setTopLeftPos(const sf::Vector2f& top_left_pos);

	void setSliderValue(const float new_value);
	void setSliderPercentValue(const float new_percent_value);

	bool changeMousePosition(const sf::Vector2i& position);
	// Returns true if slider is pressed.
	// Otherwise, returns false.
	bool onMouseButtonPressed(const MouseActionType mouse_type);
	void onMouseButtonReleased(const MouseActionType mouse_type);

	// Draws all textures and texts in the scene on an sf::RenderTarget object
	void draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing = true);
};