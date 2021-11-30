#include <iostream>

#include <SFML/Graphics.hpp>

#include "Text.h"
#include "../Enums.h"
#include "../GraphicsObject/GraphicsObject.h"
#include "../ResourceVault/ResourceVault.h"
#include "../Window/Window.h"


void Text::calSpaceTaken() {
    sf::Text text = getSfText();

    width = height = 0;

    for (int i = 0; i < content.size(); i++) {
        sf::Vector2f pos = text.findCharacterPos(i) - pos_top_left;
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


sf::Vector2f Text::getPosTopLeft() const {
    return pos_top_left;
}


sf::Vector2f Text::getPosRightDown() const {
    return sf::Vector2f(pos_top_left.x + width, pos_top_left.y + height);
}


sf::Text Text::getSfText() const {
    std::shared_ptr<sf::Font> font = ResourceVault::getFont(font_type);

    sf::Text text;
    Graphics::createText(text, content, *font, font_size, text_color, style, pos_top_left);
    return text;
}


int Text::getFontSize() const {
    return font_size;
}


void Text::createText(const std::string& content, const FontType font_type, const int size, const sf::Color& color, const sf::Text::Style& style, const sf::Vector2f pos_top_left) {
    this->content = Graphics::trim(content);
    this->font_type = font_type;
    this->font_size = size;
    this->text_color = color;
    this->style = style;
    this->pos_top_left = pos_top_left;

    calSpaceTaken();
}


void Text::setText(const std::string& content) {
    this->content = Graphics::trim(content);

    calSpaceTaken();
}


void Text::setFontType(const FontType font_type) {
    this->font_type = font_type;

    calSpaceTaken();
}


void Text::setTopLeftPos(const sf::Vector2f& pos_top_left) {
    this->pos_top_left = pos_top_left;
}


void Text::setTopLeftPosX(const float& pos_top_left_x) {
    pos_top_left.x = pos_top_left_x;
}


void Text::setTopLeftPosY(const float& pos_top_left_y) {
    pos_top_left.y = pos_top_left_y;
}


void Text::setFontSize(int size) {
    font_size = size;

    calSpaceTaken();
}


Result Text::centerTextHorizontally(const float window_width) {
    if (window_width < width)
        return Result::failure;

    pos_top_left.x = (window_width / 2) - (width / 2);

    return Result::success;
}