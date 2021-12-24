#include <iostream>

#include "Button.h"


Button::Button() {
    texture_type = TextureType::Unknown;

    top_left_pos = sf::Vector2f(0, 0);
    padding = DEFAULT_PADDING_SIZE;
    scale = sf::Vector2f(1, 1);
    transparent = false;
}


Result Button::equalizeButtonsSize(Button& button1, Button& button2) {
    float width = std::max(button1.getSize().x, button2.getSize().x);
    float height = std::max(button1.getSize().y, button2.getSize().y);
    button1.setScale(sf::Vector2f(width / button1.getImageSize().x, height / button1.getImageSize().y));
    button2.setScale(sf::Vector2f(width / button2.getImageSize().x, height / button2.getImageSize().y));

    int font_size = std::max(button1.label.getFontSize(), button2.label.getFontSize());
    button1.label.setFontSize(font_size);
    button2.label.setFontSize(font_size);

    sf::Vector2f padding;
    padding.x = std::min(button1.getPadding().x, button2.getPadding().x);
    padding.y = std::min(button1.getPadding().y, button2.getPadding().y);
    button1.setPadding(padding);
    button2.setPadding(padding);

    button1.centerTextInButton();
    button2.centerTextInButton();
}


sf::Vector2f Button::getSize() const {
    auto original_size = getImageSize();

    return sf::Vector2f(original_size.x * scale.x, original_size.y * scale.y);
}

sf::Vector2u Button::getImageSize() const {
    auto texture = (*ResourceManager::getInstance())->getTexture(texture_type);

    return texture->getSize();
}


sf::Vector2f Button::getPosTopLeft() const {
    return top_left_pos;
}


sf::Vector2f Button::getPosRightDown() const {
    return top_left_pos + getSize();
}


sf::Vector2f Button::getPadding() const {
    return padding;
}


void Button::getDefaultSprite(sf::Sprite& sprite) const {
    auto texture = (*ResourceManager::getInstance())->getTexture(texture_type);

    Graphics::loadSpriteFromTexture(sprite, *texture, top_left_pos);
    sprite.setScale(scale);

    if (transparent)
        sprite.setColor(sf::Color(255, 255, 255, DEFAULT_TRANSPARENT_ALPHA_VALUE));
    else
        sprite.setColor(sf::Color(255, 255, 255, 255));
}


void Button::getHoveredSprite(sf::Sprite& sprite) const {
    auto texture = (*ResourceManager::getInstance())->getTexture(texture_type);

    Graphics::loadSpriteFromTexture(sprite, *texture, top_left_pos);
    sprite.setScale(scale);

    // Darken the hovered sprite a bit.
    if (transparent) {
        auto color = HOVERED_COLOR;
        color.a = DEFAULT_TRANSPARENT_ALPHA_VALUE;
        sprite.setColor(color);
    }
    else {
        auto color = HOVERED_COLOR;
        color.a = 255;
        sprite.setColor(color);
    }
}


bool Button::isMouseHovering(const sf::Vector2i& mouse_position) const {
    sf::Vector2f pos_right_down = getPosRightDown();

    if (mouse_position.x < top_left_pos.x || mouse_position.x > pos_right_down.x) {
        return false;
    }
    if (mouse_position.y < top_left_pos.y || mouse_position.y > pos_right_down.y) {
        return false;
    }
    return true;
}


Result Button::setImage(const TextureType texture_type, const sf::Vector2f& top_left_pos, const sf::Vector2f& scale) {
    if (!(*ResourceManager::getInstance())->findTexture(texture_type)) {
        return Result::failure;
    }

    this->texture_type = texture_type;
    this->scale = scale;

    if (top_left_pos.x != -1) {
        this->top_left_pos = top_left_pos;
    }

    return Result::success;
}


void Button::setTopLeftPos(const sf::Vector2f& top_left_pos) {
    this->top_left_pos = top_left_pos;
}


void Button::setTopLeftPosX(const float& top_left_pos_x) {
    top_left_pos.x = top_left_pos_x;
}


void Button::setTopLeftPosY(const float& top_left_pos_y) {
    top_left_pos.y = top_left_pos_y;
}


void Button::setPadding(const sf::Vector2f& padding) {
    this->padding = padding;
}


void Button::setScale(const sf::Vector2f& scale) {
    this->scale = scale;
}


void Button::setSize(const sf::Vector2f& size) {
    auto img_size = getImageSize();

    scale.x = size.x / (float)img_size.x;
    scale.y = size.y / (float)img_size.y;
}


void Button::setTransparent(const bool set) {
    transparent = set;
}


void Button::alignImageAndText() {
    float text_width = label.getWidth();
    float text_height = label.getHeight();

    float desired_width = text_width + 2 * padding.x;
    float desired_height = text_height + 2 * padding.y;

    scale.x = desired_width / getImageSize().x;
    scale.y = desired_height / getImageSize().y;

    label.setTopLeftPos(top_left_pos + padding);
}


void Button::centerButtonHorizontally(const float space_width, const float left_pos_x) {
    float button_width = getSize().x;
    top_left_pos.x = left_pos_x + (space_width / 2) - (button_width / 2);
    centerTextInButton();
}


void Button::centerButtonVertically(const float space_height, const float top_pos_y) {
    float button_height = getSize().y;
    top_left_pos.y = top_pos_y + (space_height / 2) - (button_height / 2);
    centerTextInButton();
}


void Button::centerTextInButton() {
    float text_width = label.getWidth();
    float text_height = label.getHeight();

    sf::Vector2f pos_right_down = getPosRightDown();

    sf::Vector2f desired_pos;
    desired_pos.x = ((top_left_pos.x + pos_right_down.x) / 2) - (text_width / 2);
    desired_pos.y = ((top_left_pos.y + pos_right_down.y) / 2) - (text_height / 2);

    label.setTopLeftPos(desired_pos);
}
