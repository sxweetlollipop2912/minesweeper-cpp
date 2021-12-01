#include <string>

#include <SFML/Graphics.hpp>

#include "GraphicsObject.h"
#include "../../Enums.h"


Result Graphics::loadTextureFromFilepath(sf::Texture& texture, const std::string& img_path) {
    if (!texture.loadFromFile(img_path)) {
        return Result::failure;
    }
    return Result::success;
}


void Graphics::loadSpriteFromTexture(sf::Sprite& sprite, const sf::Texture& texture, const sf::Vector2f& position) {
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);
}


Result Graphics::loadFont(sf::Font& font, const std::string& font_path) {
    if (!font.loadFromFile(font_path)) {
        return Result::failure;
    }
    return Result::success;
}


void Graphics::createText(sf::Text& text, const std::string& content, const sf::Font& font, const int size, const sf::Color& color, const sf::Text::Style& style, const sf::Vector2f pos_top_left) {
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(style);
    text.setPosition(pos_top_left);
}


//Result Graphics::positionTextInRect(sf::Text& text, const int width, const int height) {
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
//    return Result::success;
//}


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


//std::string Graphics::normalizeStr(std::string s) {
//    for (int i = 0; i < s.size(); i++) {
//        if (s[i] == '\n') s[i] = ' ';
//    }
//    Graphics::trim(s);
//    
//    return s;
//}
