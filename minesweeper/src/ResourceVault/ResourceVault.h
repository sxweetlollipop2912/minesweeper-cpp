#pragma once

#include <map>

#include <SFML/Graphics.hpp>

#include "../Enums.h"
#include "../Constants.h"
#include "../GraphicsObject/GraphicsObject.h"
#include "../Text/Text.h"


class ResourceVault {
private:
	static std::map <TextureType, std::shared_ptr<sf::Texture>> map_texture;
	static std::map <FontType, std::shared_ptr<sf::Font>> map_font;

	ResourceVault();

public:
	static bool findTexture(const TextureType type);
	static bool findFont(const FontType type);

	static std::shared_ptr<sf::Texture> getTexture(const TextureType type);
	static std::shared_ptr<sf::Font> getSafeFont(const FontType type);
	static std::shared_ptr<sf::Font> getFont(const FontType type);

	static Result setTexture(const TextureType type, const std::string& file_path);
	static Result setFont(const FontType type, const std::string& file_path);
};