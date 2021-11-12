#include <iostream>

#include <SFML/Graphics.hpp>

#include "Text.h"
#include "../Enums.h"
#include "../GraphicsObject/GraphicsObject.h"
#include "../Window/Window.h"


void Text::calSpaceTaken() {
    sf::Text text = getSfText();

    width = height = 0;

    for (int i = 0; i < content.size(); i++) {
        sf::Vector2f pos = text.findCharacterPos(i);
        width = std::max(width, pos.x);
        height = std::max(height, pos.y);
    }

    height += text.getCharacterSize();
    width += text.getCharacterSize();
}


std::string Text::getString() const {
    return content;
}


float Text::getWidth() const {
    return width;
}


float Text::getHeight() const {
    return height;
}


sf::Text Text::getSfText() const {
    sf::Text text;
    GraphicsObject::createText(text, content, font, font_size, text_color, style, pos_top_left);
    return text;
}


int Text::getFontSize() const {
    return font_size;
}


void Text::createText(const std::string& content, const sf::Font& font, const unsigned int size, const sf::Color& color, const sf::Text::Style& style, const sf::Vector2f pos_top_left) {
    this->content = trim(content);
    this->font = font;
    this->font_size = size;
    this->text_color = color;
    this->style = style;
    this->pos_top_left = pos_top_left;

    calSpaceTaken();
}


Result Text::createText(const std::string& content, const std::string& font_path, const unsigned int size, const sf::Color& color, const sf::Text::Style& style, const sf::Vector2f pos_top_left) {
    if (!font_path.empty() && loadFont(font, font_path) == Result::failure) {
        return Result::failure;
    }
    this->content = trim(content);
    this->font_size = size;
    this->text_color = color;
    this->style = style;
    this->pos_top_left = pos_top_left;

    calSpaceTaken();

    return Result::success;
}


Result Text::setText(const std::string& text, const int size, const std::string& font_path) {
    if (!font_path.empty() && loadFont(font, font_path) == Result::failure) {
        return Result::failure;
    }
    if (size != -1) {
        font_size = size;
    }
    content = trim(text);

    calSpaceTaken();

    return Result::success;
}


void Text::setTopLeftPosition(const sf::Vector2f& pos_top_left) {
    this->pos_top_left = pos_top_left;
}


void Text::setFontSize(unsigned int size) {
    font_size = size;
}


Result Text::centerTextHorizontally(const float window_width) {
    if (window_width < width)
        return Result::failure;

    pos_top_left.x = (window_width / 2) - (width / 2);

    return Result::success;
}
