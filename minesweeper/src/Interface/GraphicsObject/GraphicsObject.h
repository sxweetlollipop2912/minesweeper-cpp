#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "../../Enums.h"
#include "../../Constants.h"


class Graphics {
public:
	Graphics();

	// Loads texture from an external image file to `texture` variable.
	// > Returns `Result::failure` when image cannot be loaded from `img_path`,
	// > otherwise returns `Result::success`.
	static Result loadTextureFromFilepath(sf::Texture& texture, const std::string& img_path);
	// Loads sprite from an existing texture to `sprite` variable.
	// Also, sets its position.
	static void loadSpriteFromTexture(sf::Sprite& sprite, const sf::Texture& texture, const sf::Vector2f& position);

	// Loads font from external file to `font` variable.
	// > Returns `Result::failure` when font cannot be loaded from `font_path`,
	// > otherwise returns `Result::success`.
	static Result loadFont(sf::Font& font, const std::string& font_path);
	// Loads a sf::Text object with content, font, size (optional), color (optional), style (optional).
	static void createText(sf::Text& text,
		const std::string& content,
		const sf::Font& font,
		const int size = DEFAULT_LARGE_FONT_SIZE,
		const sf::Color& color = DEFAULT_TEXT_COLOR,
		const sf::Text::Style& style = sf::Text::Regular,
		const sf::Vector2f top_left_pos = sf::Vector2f(0, 0));
	// Tries to position a text inside a rectangle container.
	// NOTE: The string will be changed permanently. There's no turning back.
	// Shouldn't cost much time if already positioned b4.
	// > Returns `Result::failure` if text's content is too large to be positioned within the rectangle,
	// > otherwise returns `Result::success`.
	//static Result positionTextInRect(sf::Text& text, const int width, const int height);

	// Trims leading whitespaces on the front and back of a string and deletes any consecutive whitespaces.
	static std::string trim(std::string s);
	//static std::string normalizeStr(std::string s);
};