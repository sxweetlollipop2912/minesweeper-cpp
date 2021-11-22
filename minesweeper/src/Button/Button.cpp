#include <iostream>

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "../Enums.h"
#include "../ResourceVault/ResourceVault.h"
#include "../GraphicsObject/GraphicsObject.h"


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

    if (button1.centerTextInButton() == Result::failure) {
        return Result::failure;
    }
    if (button2.centerTextInButton() == Result::failure) {
        return Result::failure;
    }

    return Result::success;
}


sf::Vector2f Button::getSize() const {
    sf::Vector2u original_size = getImageSize();

    return sf::Vector2f(original_size.x * scale.x, original_size.y * scale.y);
}

sf::Vector2u Button::getImageSize() const {
    auto texture = ResourceVault::getTexture(texture_type);

    return texture->getSize();
}


sf::Vector2f Button::getPosTopLeft() const {
    return pos_top_left;
}


sf::Vector2f Button::getPosRightDown() const {
    return pos_top_left + getSize();
}


sf::Vector2f Button::getPadding() const {
    return padding;
}


sf::Sprite Button::getDefaultSprite() const {
    auto texture = ResourceVault::getTexture(texture_type);

    sf::Sprite sprite;
    Graphics::loadSpriteFromTexture(sprite, *texture, pos_top_left);
    sprite.setScale(scale);

    return std::move(sprite);
}


sf::Sprite Button::getHoveredSprite() const {
    auto texture = ResourceVault::getTexture(texture_type);

    sf::Sprite sprite;
    Graphics::loadSpriteFromTexture(sprite, *texture, pos_top_left);
    sprite.setScale(scale);

    // Darken the hovered sprite a bit.
    sf::Color grey(100, 100, 100);
    sprite.setColor(grey);

    return std::move(sprite);
}


bool Button::isMouseHovering(const sf::Vector2i& mouse_position) const {
    sf::Vector2f pos_right_down = getPosRightDown();

    if (mouse_position.x < pos_top_left.x || mouse_position.x > pos_right_down.x) {
        return false;
    }
    if (mouse_position.y < pos_top_left.y || mouse_position.y > pos_right_down.y) {
        return false;
    }
    return true;
}


Result Button::setImage(const TextureType texture_type, const sf::Vector2f& pos_top_left, const sf::Vector2f& scale) {
    if (!ResourceVault::findTexture(texture_type)) {
        std::cout << "NOT FOUND\n";
        return Result::failure;
    }

    this->texture_type = texture_type;
    this->scale = scale;

    if (pos_top_left.x != -1) {
        this->pos_top_left = pos_top_left;
    }

    return Result::success;
}


void Button::setTopLeftPosition(const sf::Vector2f& pos_top_left) {
    this->pos_top_left = pos_top_left;
}


void Button::setPadding(const sf::Vector2f& padding) {
    this->padding = padding;
}


void Button::setScale(const sf::Vector2f& scale) {
    this->scale = scale;
}


void Button::alignImageAndText() {
    float text_width = label.getWidth();
    float text_height = label.getHeight();

    float desired_width = text_width + 2 * padding.x;
    float desired_height = text_height + 2 * padding.y;

    scale.x = desired_width / getImageSize().x;
    scale.y = desired_height / getImageSize().y;

    label.setTopLeftPosition(pos_top_left + padding);
}


Result Button::centerButtonHorizontally(const float window_width) {
    float texture_width = getImageSize().x * scale.x;

    if (window_width < texture_width)
        return Result::failure;

    pos_top_left.x = (window_width / 2) - (texture_width / 2);

    if (centerTextInButton() == Result::failure) {
        return Result::failure;
    }

    return Result::success;
}


Result Button::centerTextInButton() {
    float text_width = label.getWidth();
    float text_height = label.getHeight();

    sf::Vector2f pos_right_down = getPosRightDown();

    sf::Vector2f desired_pos;
    desired_pos.x = ((pos_top_left.x + pos_right_down.x) / 2) - (text_width / 2);
    desired_pos.y = ((pos_top_left.y + pos_right_down.y) / 2) - (text_height / 2);
    label.setTopLeftPosition(desired_pos);

    return Result::success;
}
