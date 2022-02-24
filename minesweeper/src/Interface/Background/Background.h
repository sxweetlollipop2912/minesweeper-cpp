#pragma once

#include <stdlib.h>
#include <algorithm>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../Scenes/scene.h"
#include "../ResourceManager/ResourceManager.h"
#include "../../Enums.h"
#include "../../Constants.h"
#include "../../Structs.h"

constexpr auto PI = 3.1415926535897932384626;
constexpr auto TRANSPARENT_ALPHA = 150;


struct Circle {
	sf::Vector2f veloc;
	float radius;
	sf::Vector2f pos;
	Circle() {
		radius = 0;
	}
};


class Background : public Scene {
	friend class Window;

private:
	const std::string STR_NEXT_SONG = "next_song";

	std::shared_ptr<Slider> volume;

	Color cur_prim_color;
	Color cur_second_color;
	Color des_prim_color;
	Color des_second_color;
	sf::Time transition_duration;
	float circle_speed;

	sf::RectangleShape background;
	sf::CircleShape circle_shape;
	std::vector <Circle> circles;

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


	void setDefaultPositionAudioButtons();
	void setCustomPositionAudioButtons(const sf::Vector2f& volume_top_left_pos);
	void centerAudioButtonsHorizontally(const float space_width, const float left_pos_x = 0);

	// Call on a mouse button released event.
	// Returns corresponding GameEvent.
	GameEvent onMouseButtonReleased(const MouseActionType mouse_type) override;
	// Call on a mouse button pressed event.
	// Returns corresponding GameEvent.
	GameEvent onMouseButtonPressed(const MouseActionType mouse_type) override;
	// Changes window graphics base on new mouse position.
	// Returns true if there are visual changes.
	// Otherwise, returns false
	bool changeMousePosition(const sf::Vector2i& pos) override;

	// Draws all textures and texts in background on an sf::RenderTarget object
	void draw(std::shared_ptr<sf::RenderTarget> renderer, const bool is_focusing = true) override;
};