#include "GraphicsObject.h"


Graphics::Graphics() {}


Result Graphics::loadTextureFromFilepath(sf::Texture& texture, const std::string& img_path) {
    if (!texture.loadFromFile(img_path)) {
        return Result::failure;
    }
    return Result::success;
}


void Graphics::loadSpriteFromTexture(sf::Sprite& sprite, const sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture, true);
    sprite.setPosition(position.x, position.y);
}


Result Graphics::loadFont(sf::Font& font, const std::string& font_path) {
    if (!font.loadFromFile(font_path)) {
        return Result::failure;
    }
    return Result::success;
}


void Graphics::createText(sf::Text& text, const std::string& content, const sf::Font& font, const int size, const sf::Color& color, const sf::Text::Style& style, const sf::Vector2f top_left_pos) {
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(style);
    text.setPosition(top_left_pos);
}


std::string Graphics::trim(std::string s) {
    int l = 0, r = s.size();
    while (l < s.size() && s[l] == ' ') ++l;
    while (r >= 0 && s[r] == ' ') --r;
    s = s.substr(l, std::max(l, r - l + 1));

    for (int i = 1; i < s.size(); i++) {
        if (s[i] == ' ' && s[i - 1] == ' ') {
            s.erase(s.begin() + i);
        }
    }

    return s;
}