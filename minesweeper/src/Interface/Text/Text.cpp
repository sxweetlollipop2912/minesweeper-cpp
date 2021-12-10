#include <iostream>

#include "Text.h"


void Text::calSpaceTaken() {
    sf::Text text = getSfText();

    width = height = 0;

    for (int i = 0; i < content.size(); i++) {
        sf::Vector2f pos = text.findCharacterPos(i) - top_left_pos;
        width = std::max(width, pos.x);
        height = std::max(height, pos.y);
    }

    height += text.getCharacterSize();
    width += text.getCharacterSize() * 2 / 3;
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
    return top_left_pos;
}


sf::Vector2f Text::getPosRightDown() const {
    return sf::Vector2f(top_left_pos.x + width, top_left_pos.y + height);
}


sf::Text Text::getSfText() const {
    std::shared_ptr<sf::Font> font = ResourceVault::getFont(font_type);

    sf::Text text;
    Graphics::createText(text, content, *font, font_size, text_color, style, top_left_pos);
    return text;
}


int Text::getFontSize() const {
    return font_size;
}


void Text::createText(const std::string& content, const FontType font_type, const int size, const sf::Color& color, const sf::Text::Style& style, const sf::Vector2f top_left_pos) {
    this->content = Graphics::trim(content);
    this->font_type = font_type;
    this->font_size = size;
    this->text_color = color;
    this->style = style;
    this->top_left_pos = top_left_pos;

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


void Text::setTopLeftPos(const sf::Vector2f& top_left_pos) {
    this->top_left_pos = top_left_pos;
}


void Text::setTopLeftPosX(const float& top_left_pos_x) {
    top_left_pos.x = top_left_pos_x;
}


void Text::setTopLeftPosY(const float& top_left_pos_y) {
    top_left_pos.y = top_left_pos_y;
}


void Text::setFontSize(const int size) {
    font_size = size;

    calSpaceTaken();
}


void Text::setTextColor(const sf::Color& color) {
    text_color = color;
}


Result Text::centerTextHorizontally(const float window_width) {
    if (window_width < width)
        return Result::failure;

    top_left_pos.x = (window_width / 2) - (width / 2);

    return Result::success;
}