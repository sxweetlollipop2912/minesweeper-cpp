#pragma once

#include <SFML/Graphics.hpp>

#include "../Enums.h"
#include "../Constants.h"
#include "../GraphicsObject/GraphicsObject.h"


class Text : public GraphicsObject {
private:
	std::string content;

	sf::Font font;
	int font_size;
	sf::Color text_color;
	sf::Text::Style style;

	sf::Vector2f pos_top_left;
	float width, height;

	// Calculates width and height of the space taken by text.
	// Call this method when text is changed.
	void calSpaceTaken();

public:
	// Initializes button with:
	// - Default font, font size, text color, text style.
	// - Empty text
	Text() : GraphicsObject() {
		width = 0;
		height = 0;
		pos_top_left.x = pos_top_left.y = 0;

		loadFont(font, DEFAULT_FONT_PATH);
		content.clear();
		font_size = DEFAULT_FONT_SIZE;
		text_color = DEFAULT_TEXT_COLOR;
		style = sf::Text::Style::Regular;
	}

	// Gets text in std::string.
	std::string getString() const;
	// Gets width of the text.
	float getWidth() const;
	// Gets height of the text.
	float getHeight() const;
	// Gets text as sf::Text.
	sf::Text getSfText() const;
	// Gets font size.
	int getFontSize() const;

	// Initializes the text with content, font, size (optional), color (optional), style (optional).
	void createText(const std::string& content,
		const sf::Font& font,
		const unsigned int size = DEFAULT_FONT_SIZE,
		const sf::Color& color = DEFAULT_TEXT_COLOR,
		const sf::Text::Style& style = sf::Text::Regular,
		const sf::Vector2f pos_top_left = sf::Vector2f(0, 0));
	// Initializes the text with content, font (optional), size (optional), color (optional), style (optional).
	// > Returns Result::failure if `font` parameter is present and cannot be loaded,
	// > otherwise, returns Result::success.
	Result createText(const std::string& content,
		const std::string& font_path,
		const unsigned int size,
		const sf::Color& color,
		const sf::Text::Style& style,
		const sf::Vector2f pos_top_left = sf::Vector2f(0, 0));
	// Sets text, size and font. Use default font and size if not provided.
	// > Returns Result::failure if font cannot be loaded,
	// > otherwise, returns Result::success.
	Result setText(const std::string& content, const int size = -1, const std::string& font_path = "");
	// Sets top-left position of text.
	void setTopLeftPosition(const sf::Vector2f& pos_top_left);
	// Sets font size.
	void setFontSize(unsigned int size);

	// Centers text on X-axis.
	// > Returns Result::failure if text is wider than screen,
	// > otherwise, returns Result::success.
	Result centerTextHorizontally(const float window_width);
};