#include <iostream>

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "../../Enums.h"
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
    auto original_size = getImageSize();

    return sf::Vector2f(original_size.x * scale.x, original_size.y * scale.y);
}

sf::Vector2u Button::getImageSize() const {
    auto texture = ResourceVault::getTexture(texture_type);

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


sf::Sprite Button::getDefaultSprite() const {
    auto texture = ResourceVault::getTexture(texture_type);

    sf::Sprite sprite;
    Graphics::loadSpriteFromTexture(sprite, *texture, top_left_pos);
    sprite.setScale(scale);

    return sprite;
}


sf::Sprite Button::getHoveredSprite() const {
    auto texture = ResourceVault::getTexture(texture_type);

    sf::Sprite sprite;
    Graphics::loadSpriteFromTexture(sprite, *texture, top_left_pos);
    sprite.setScale(scale);

    // Darken the hovered sprite a bit.
    sf::Color grey(100, 100, 100);
    sprite.setColor(grey);

    return sprite;
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
    if (!ResourceVault::findTexture(texture_type)) {
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


void Button::alignImageAndText() {
    float text_width = label.getWidth();
    float text_height = label.getHeight();

    float desired_width = text_width + 2 * padding.x;
    float desired_height = text_height + 2 * padding.y;

    scale.x = desired_width / getImageSize().x;
    scale.y = desired_height / getImageSize().y;

    label.setTopLeftPos(top_left_pos + padding);
}


Result Button::centerButtonHorizontally(const float window_width) {
    float button_width = getSize().x;

    if (window_width < button_width)
        return Result::failure;

    float old_x = top_left_pos.x;
    top_left_pos.x = (window_width / 2) - (button_width / 2);

    if (top_left_pos.x < 0 || centerTextInButton() == Result::failure) {
        top_left_pos.x = old_x;

        return Result::failure;
    }

    return Result::success;
}


Result Button::centerButtonVertically(const float window_height) {
    float button_height = getSize().y;

    if (window_height < button_height)
        return Result::failure;

    float old_y = top_left_pos.y;
    top_left_pos.y = (window_height / 2) - (button_height / 2);

    if (top_left_pos.y < 0 || centerTextInButton() == Result::failure) {
        top_left_pos.y = old_y;

        return Result::failure;
    }

    return Result::success;
}


//Result Button::fitTextInsideButton() {
//    int width = getSize().x - getPadding().x * 2;
//    int height = getSize().y - getPadding().y * 2;
//
//    sf::Text text = label.getSfText();
//
//    {
//        std::string s = text.getString();
//        Graphics::normalizeStr(s);
//        text.setString(s);
//    }
//
//    int size = text.getString().getSize();
//
//    for (int space_1 = -1, space_2 = 0; space_2 < size; space_2++) {
//        if (space_2 < 1 || text.getString()[space_2] != ' ')
//            continue;
//        if (text.findCharacterPos(space_2 - 1).x <= width)
//            continue;
//        if (space_1 == -1)
//            return Result::failure;
//
//        std::string s = text.getString();
//        // Deletes whitespace at space_1
//        s.erase(s.begin() + space_1);
//        // Inserts newline.
//        s.insert(s.begin() + space_1, '\n');
//        text.setString(s);
//
//        if (text.findCharacterPos(space_2 - 1).x > width || text.findCharacterPos(space_2 - 1).y > height)
//            return Result::failure;
//
//        space_1 = space_2;
//    }
//
//    label.setText(text.getString());
//
//}


Result Button::centerTextInButton() {
    float text_width = label.getWidth();
    float text_height = label.getHeight();

    sf::Vector2f pos_right_down = getPosRightDown();

    sf::Vector2f desired_pos;
    desired_pos.x = ((top_left_pos.x + pos_right_down.x) / 2) - (text_width / 2);
    desired_pos.y = ((top_left_pos.y + pos_right_down.y) / 2) - (text_height / 2);

    if (desired_pos.x < 0 || desired_pos.y < 0)
        return Result::failure;

    label.setTopLeftPos(desired_pos);

    return Result::success;
}
