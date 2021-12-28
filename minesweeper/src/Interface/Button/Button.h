#pragma once

#include <SFML/Graphics.hpp>

#include "../GraphicsObject/GraphicsObject.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Text/Text.h"
#include "../../Enums.h"
#include "../../Constants.h"


// A button is basically an image, but with label and interactive.
// Remember to rescale image after changing text,
// and recenter image after changing window dimension.
class Button {
protected:
	TextureType texture_type;
	sf::Vector2f scale;
	sf::Vector2f top_left_pos, padding;
	bool transparent;
	bool stretchable;

public:
	Text label;

	// Initializes button with:
	// - Label with empty text, default font, font size, text color, text style.
	// - Button is positioned at (0, 0).
	// - Default padding.
	// - Empty image, image scale = 1.
	Button();

	// Equalizes 2 buttons' size, padding, font_size, and centers text in button's image.
	// > Returns Result::failure if text is wider than screen,
	// > otherwise, returns Result::success.
	static void equalizeButtonsSize(Button& button1, Button& button2);

	// Gets size of the button (after apply scaling).
	virtual sf::Vector2f getSize() const;
	// Gets original size of the button's image (b4 apply scaling).
	virtual sf::Vector2u getImageSize() const;
	// Gets top-left position of button.
	sf::Vector2f getPosTopLeft() const;
	// Gets right-down position of button.
	sf::Vector2f getPosRightDown() const;
	// Gets padding size.
	sf::Vector2f getPadding() const;
	// Gets default (not hovered) button's sprite.
	virtual void getDefaultSprite(sf::Sprite& sprite) const;
	// Gets hovered (not hovered) button's sprite.
	virtual void getHoveredSprite(sf::Sprite& sprite) const;

	// Checks a mouse position if it is hovered over the button.
	bool isMouseHovering(const sf::Vector2i& mouse_position) const;

	// Sets and scales image for the button. Also, sets its top-left position, padding size, scale.
	// > Returns Result::failure if image cannot be loaded,
	// > otherwise, returns Result::success.
	virtual Result setImage(const TextureType texture_type, const sf::Vector2f& top_left_pos = sf::Vector2f(-1, -1), const sf::Vector2f& scale = sf::Vector2f(1, 1));
	// Sets top-left position of the button.
	virtual void setTopLeftPos(const sf::Vector2f& top_left_pos);
	// Sets top-left position of the button on X-axis.
	virtual void setTopLeftPosX(const float& top_left_pos_x);
	// Sets top-left position of the button on Y-axis.
	virtual void setTopLeftPosY(const float& top_left_pos_y);
	// Sets padding size of the button.
	// NOTE: if button is already scaled to fit text, it is recommended to rescale it.
	virtual void setPadding(const sf::Vector2f& padding);
	// Sets scale of button's image.
	virtual void setScale(const sf::Vector2f& scale);
	// Sets size of button's image (this will calculate appropriate scale of the image).
	virtual void setSize(const sf::Vector2f& size);
	// Sets button's image to be transparent (true) or not (false).
	void setTransparent(const bool set = true);

	// Rescales image & positions text so that CURRENT text is within image's padding.
	virtual void alignImageAndText();
	// Centers image and text on X-axis.
	void centerButtonHorizontally(const float space_width, const float left_pos_x = 0);
	// Centers image and text on Y-axis.
	void centerButtonVertically(const float space_height, const float top_pos_y = 0);
	// Centers text in button's image.
	// NOTE: This method does not resize or re-position image.
	virtual void centerTextInButton();
};