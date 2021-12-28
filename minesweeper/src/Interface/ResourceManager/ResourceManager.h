#pragma once

#include <map>

#include <SFML/Graphics.hpp>

#include "../GraphicsObject/GraphicsObject.h"
#include "../Text/Text.h"
#include "../../Enums.h"
#include "../../Constants.h"


// This is a singleton.
class ResourceManager {
private:
	static ResourceManager* instance;

	std::map <TextureType, std::shared_ptr<sf::Texture>> map_texture;
	std::map <FontType, std::shared_ptr<sf::Font>> map_font;

	sf::Clock game_clock;

	ResourceManager();

public:
	/**
	 * Singletons should not be cloneable.
	 */
	ResourceManager(ResourceManager& other) = delete;
	/**
	 * Singletons should not be assignable.
	 */
	void operator=(const ResourceManager&) = delete;

	static std::shared_ptr<ResourceManager*> getInstance();


	bool findTexture(const TextureType type) const;
	bool findFont(const FontType type) const;

	std::shared_ptr<sf::Texture> getTexture(const TextureType type) const;
	std::shared_ptr<sf::Font> getSafeFont(const FontType type) const;
	std::shared_ptr<sf::Font> getFont(const FontType type) const;

	// Gets current sf::Time from a clock that counts from game start.
	sf::Time getElapsedTime() const;

	Result setTexture(const TextureType type, const std::string& file_path);
	Result setFont(const FontType type, const std::string& file_path);
};