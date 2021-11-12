#pragma once

#include <SFML/Graphics.hpp>

#include "../Enums.h"
#include "../Constants.h"


class GraphicsObject {
protected:
	// Loads texture from an external image file to `texture` variable.
	// > Returns `Result::failure` when image cannot be loaded from `img_path`,
	// > otherwise returns `Result::success`.
	Result loadTextureFromFilepath(sf::Texture& texture, const std::string& img_path) const;
	// Loads sprite from an existing texture to `sprite` variable.
	// Also, sets its position.
	void loadSpriteFromTexture(sf::Sprite& sprite, const sf::Texture& texture, const sf::Vector2f& position) const;

	// Loads font from external file to `font` variable.
	// > Returns `Result::failure` when font cannot be loaded from `font_path`,
	// > otherwise returns `Result::success`.
	Result loadFont(sf::Font& font, const std::string& font_path) const;
	// Loads a sf::Text object with content, font, size (optional), color (optional), style (optional).
	void createText(sf::Text& text, 
		const std::string& content, 
		const sf::Font& font,
		const unsigned int size = DEFAULT_FONT_SIZE, 
		const sf::Color& color = DEFAULT_TEXT_COLOR,
		const sf::Text::Style& style = sf::Text::Regular,
		const sf::Vector2f pos_top_left = sf::Vector2f(0, 0)) const;
	// Tries to position a text inside a rectangle container.
	// NOTE: The string will be changed permanently. There's no going back.
	// Shouldn't cost much time if already positioned b4.
	// > Returns `Result::failure` if text's content is too large to be positioned within the rectangle,
	// > otherwise returns `Result::success`.
	Result positionTextInRect(sf::Text& text, const int width, const int height) const;

	// Trims leading whitespaces on the front and back of a string.
	std::string trim(std::string s) const;

public:

};