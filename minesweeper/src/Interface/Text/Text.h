#pragma once

#include <SFML/Graphics.hpp>

#include "../GraphicsObject/GraphicsObject.h"
#include "../ResourceManager/ResourceManager.h"
#include "../../Enums.h"
#include "../../Constants.h"


class Text {
private:
	std::string content;

	FontType font_type;
	int font_size;
	sf::Color text_color;
	sf::Text::Style style;

	sf::Vector2f top_left_pos;
	float width, height;

	// Calculates width and height of the space taken by text.
	// Call this method when text is changed.
	void calSpaceTaken();

public:
	// Initializes button with:
	// - Default font, font size, text color, text style.
	// - Empty text
	Text();

	// Gets text in std::string.
	std::string getString() const;
	// Gets width of the text.
	float getWidth() const;
	// Gets height of the text.
	float getHeight() const;
	// Gets top-left position of button.
	sf::Vector2f getPosTopLeft() const;
	// Gets right-down position of button.
	sf::Vector2f getPosRightDown() const;
	// Gets text as sf::Text.
	void getSfText(sf::Text& text) const;
	// Gets font size.
	int getFontSize() const;

	// Initializes the text with content, font, size (optional), color (optional), style (optional).
	void createText(const std::string& content,
		const FontType font_type = FontType::FontDefault,
		const int size = DEFAULT_LARGE_FONT_SIZE,
		const sf::Color& color = DEFAULT_TEXT_COLOR,
		const sf::Text::Style& style = sf::Text::Regular,
		const sf::Vector2f top_left_pos = sf::Vector2f(0, 0));

	void setText(const std::string& content);
	void setFontType(const FontType font_type);
	// Sets top-left position of text.
	void setTopLeftPos(const sf::Vector2f& top_left_pos);
	// Sets top-left position of text on X-axis.
	virtual void setTopLeftPosX(const float& top_left_pos_x);
	// Sets top-left position of text on Y-axis.
	virtual void setTopLeftPosY(const float& top_left_pos_y);
	// Sets font size.
	void setFontSize(const int size);
	// Sets text color.
	void setTextColor(const sf::Color& color);

	// Centers text on X-axis.
	// > Returns Result::failure if text is wider than screen,
	// > otherwise, returns Result::success.
	Result centerTextHorizontally(const float window_width);
};