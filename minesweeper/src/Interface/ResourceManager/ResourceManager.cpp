#include <iostream>

#include "ResourceManager.h"


ResourceManager* ResourceManager::instance = nullptr;


ResourceManager::ResourceManager() {
    map_texture.clear();
    map_font.clear();
}


std::shared_ptr<ResourceManager*> ResourceManager::getInstance() {
    if (!instance) {
        instance = new ResourceManager();
    }
    return std::make_shared<ResourceManager*>(instance);
}


bool ResourceManager::findTexture(const TextureType type) const {
    if (map_texture.find(type) == map_texture.end()) {
        return false;
    }
    if (map_texture.at(type)->getSize().x == 0 || map_texture.at(type)->getSize().y == 0) {
        return false;
    }

    return true;
}


bool ResourceManager::findFont(const FontType type) const {
    if (map_font.find(type) == map_font.end()) {
        return false;
    }
    if (map_font.at(type)->getInfo().family.empty()) {
        return false;
    }

    return true;
}


std::shared_ptr<sf::Texture> ResourceManager::getTexture(const TextureType type) const {
    if (!findTexture(type)) {
        return std::make_unique<sf::Texture>(sf::Texture());
    }

    return map_texture.at(type);
}


std::shared_ptr<sf::Font> ResourceManager::getSafeFont(const FontType type) const {
    if (findFont(type)) {
        return map_font.at(type);
    }
    if (findFont(FontType::FontDefault)) {
        return map_font.at(FontType::FontDefault);

    }
    return nullptr;
}


std::shared_ptr<sf::Font> ResourceManager::getFont(const FontType type) const {
    if (!findFont(type))
        return std::make_shared<sf::Font>(sf::Font());

    return map_font.at(type);
}


sf::Time ResourceManager::getElapsedTime() const {
    return game_clock.getElapsedTime();
}



Result ResourceManager::setTexture(const TextureType type, const std::string& file_path) {
    auto texture = std::make_shared<sf::Texture>(sf::Texture());

    if (Graphics::loadTextureFromFilepath(*texture, file_path) == Result::failure) {
        return Result::failure;
    }

    map_texture[type] = texture;

    return Result::success;
}


Result ResourceManager::setFont(const FontType type, const std::string& file_path) {
    auto font = std::make_shared<sf::Font>(sf::Font());

    if (Graphics::loadFont(*font, file_path) == Result::failure) {
        return Result::failure;
    }

    map_font[type] = font;

    return Result::success;
}