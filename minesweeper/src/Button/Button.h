#pragma once

#include <SFML/Graphics.hpp>

#include "../Enums.h"
#include "../Constants.h"
#include "../GraphicsObject/GraphicsObject.h"
#include "../Text/Text.h"


// A button is basically an image, but with label and interactive.
// Remember to rescale image after changing text,
// and recenter image after changing window dimension.
class Button : public GraphicsObject {
protected:
	ButtonType button_type;

	sf::Texture texture;
	sf::Vector2f scale;

	sf::Vector2f pos_top_left, padding;

public:
	Text label;

	// Initializes button with:
	// - Default button type (unknown type).
	// - Label with empty text, default font, font size, text color, text style.
	// - Button is positioned at (0, 0).
	// - Default padding.
	// - Empty image, image scale = 1.
	Button() {
		button_type = ButtonType::Unknown;

		pos_top_left = sf::Vector2f(0, 0);
		padding = DEFAULT_PADDING_SIZE;
		scale = sf::Vector2f(1, 1);
	}

	// Equalizes 2 buttons' size, padding, font_size, and centers text in button's image.
	// > Returns Result::failure if text is wider than screen,
	// > otherwise, returns Result::success.
	static Result equalizeButtonsSize(Button& button1, Button& button2);

	// Gets button type.
	ButtonType getButtonType() const;
	// Gets size of the button (after apply scaling).
	sf::Vector2f getSize() const;
	// Gets original size of the button's image (b4 apply scaling).
	sf::Vector2u getImageSize() const;
	// Gets top-left position of button.
	sf::Vector2f getPosTopLeft() const;
	// Gets right-down position of button.
	sf::Vector2f getPosRightDown() const;
	// Gets padding size.
	sf::Vector2f getPadding() const;
	// Gets default (not hovered) button's sprite.
	sf::Sprite getDefaultSprite() const;
	// Gets hovered (not hovered) button's sprite.
	sf::Sprite getHoveredSprite() const;

	// Checks a mouse position if it is hovered over the button.
	bool isMouseHovering(const sf::Vector2f& mouse_position) const;

	// Sets button type.
	void setButtonType(const ButtonType& button_type);
	// Sets and scales image for the button. Also, sets its top-left position, padding size, scale.
	// > Returns Result::failure if image cannot be loaded,
	// > otherwise, returns Result::success.
	Result setImage(const std::string& img_path, const sf::Vector2f& pos_top_left = sf::Vector2f(-1, -1), const sf::Vector2f& scale = sf::Vector2f(1, 1));
	// Sets top-left position of the button.
	void setTopLeftPosition(const sf::Vector2f& pos_top_left);
	// Sets padding size of the button.
	// NOTE: if button is already scaled to fit text, it is recommended to rescale it.
	void setPadding(const sf::Vector2f& padding);
	// Sets scale for button's image.
	void setScale(const sf::Vector2f& scale);

	// Rescales image & positions text so that CURRENT text is within image's padding.
	void alignImageAndText();
	// Centers image and text on X-axis.
	// > Returns Result::failure if image or text is wider than screen,
	// > otherwise, returns Result::success.
	Result centerButtonHorizontally(const float window_width);
	// Centers text in button's image.
	// NOTE: This method does not resize or re-position image.
	// > Returns Result::failure if text is wider than screen,
	// > otherwise, returns Result::success.
	Result centerTextInButton();
};