#include <iostream>

#include "ResourceVault.h"
#include "../../Enums.h"


std::map <TextureType, std::shared_ptr<sf::Texture>> ResourceVault::map_texture = {};
std::map <FontType, std::shared_ptr<sf::Font>> ResourceVault::map_font = {};


bool ResourceVault::findTexture(const TextureType type) {
    if (map_texture.find(type) == map_texture.end()) {
        return false;
    }
    if (map_texture.at(type)->getSize().x == 0 || map_texture.at(type)->getSize().y == 0) {
        return false;
    }

    return true;
}


bool ResourceVault::findFont(const FontType type) {
    if (map_font.find(type) == map_font.end()) {
        return false;
    }
    if (map_font.at(type)->getInfo().family.empty()) {
        return false;
    }

    return true;
}


std::shared_ptr<sf::Texture> ResourceVault::getTexture(const TextureType type) {
    if (!findTexture(type)) {
        return std::make_unique<sf::Texture>(sf::Texture());
    }

    return map_texture.at(type);
}


std::shared_ptr<sf::Font> ResourceVault::getSafeFont(const FontType type) {
    if (findFont(type)) {
        return map_font.at(type);
    }
    if (findFont(FontType::FontDefault)) {
        return map_font.at(FontType::FontDefault);

    }
    return nullptr;
}


std::shared_ptr<sf::Font> ResourceVault::getFont(const FontType type) {
    if (!findFont(type))
        return std::make_shared<sf::Font>(sf::Font());

    return map_font.at(type);
}



Result ResourceVault::setTexture(const TextureType type, const std::string& file_path) {
    auto texture = std::make_shared<sf::Texture>(sf::Texture());

    if (Graphics::loadTextureFromFilepath(*texture, file_path) == Result::failure) {
        return Result::failure;
    }

    map_texture[type] = texture;

    return Result::success;
}


Result ResourceVault::setFont(const FontType type, const std::string& file_path) {
    auto font = std::make_shared<sf::Font>(sf::Font());

    if (Graphics::loadFont(*font, file_path) == Result::failure) {
        return Result::failure;
    }

    map_font[type] = font;

    return Result::success;
}