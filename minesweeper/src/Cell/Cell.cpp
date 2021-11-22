#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "../Button/Button.h"
#include "../Enums.h"
#include "../Constants.h"


sf::Vector2f Cell::getScale() const {
	sf::Vector2f scale;

	scale.x = DEFAULT_CELL_SIZE / (float)button_at_state.at(cell_state).getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)button_at_state.at(cell_state).getImageSize().y;

	return scale;
}


Result Cell::setDefaultImages() {
	Button& closed = button_at_state[CellState::Closed];
	Button& flagged = button_at_state[CellState::Flagged];

	if (closed.setImage(TextureType::CellClosed) == Result::failure)
		return Result::failure;

	if (flagged.setImage(TextureType::CellFlagged) == Result::failure)
		return Result::failure;

	sf::Vector2f scale;
	scale.x = DEFAULT_CELL_SIZE / (float)closed.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)closed.getImageSize().y;
	closed.setScale(scale);

	scale.x = DEFAULT_CELL_SIZE / (float)flagged.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)flagged.getImageSize().y;
	closed.setScale(scale);

	return Result::success;
}


Result Cell::setImageForMineType() {
	Button& opened = button_at_state[CellState::Opened];

	if (opened.setImage(TextureType::CellMine) == Result::failure)
		return Result::failure;

	sf::Vector2f scale;
	scale.x = DEFAULT_CELL_SIZE / (float)opened.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)opened.getImageSize().y;
	opened.setScale(scale);

	return Result();
}


Result Cell::setImageForBlankType() {
	Button& opened = button_at_state[CellState::Opened];

	if (opened.setImage(TextureType::CellBlank) == Result::failure)
		return Result::failure;

	sf::Vector2f scale;
	scale.x = DEFAULT_CELL_SIZE / (float)opened.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)opened.getImageSize().y;
	opened.setScale(scale);

	return Result();
}


Result Cell::setImageForNumberType() {
	Button& opened = button_at_state[CellState::Opened];

	TextureType texture_type = TextureType::Unknown;
	switch (cell_number) {
	case 1:
		texture_type = TextureType::CellNum1;
		break;
	case 2:
		texture_type = TextureType::CellNum2;
		break;
	case 3:
		texture_type = TextureType::CellNum3;
		break;
	case 4:
		texture_type = TextureType::CellNum4;
		break;
	case 5:
		texture_type = TextureType::CellNum5;
		break;
	case 6:
		texture_type = TextureType::CellNum6;
		break;
	case 7:
		texture_type = TextureType::CellNum7;
		break;
	case 8:
		texture_type = TextureType::CellNum8;
		break;
	default:
		return Result::failure;
	}

	if (opened.setImage(texture_type) == Result::failure)
		return Result::failure;

	sf::Vector2f scale;
	scale.x = DEFAULT_CELL_SIZE / (float)opened.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)opened.getImageSize().y;
	opened.setScale(scale);

	return Result();
}


Result Cell::setType(const CellType type, const int number) {
	if (cell_type == type && (cell_type != CellType::Number || cell_number == number))
		return Result::failure;

	cell_type = type;

	if (type == CellType::Number)
		cell_number = number;
	if (type == CellType::Mine)
		cell_number = -1;

	switch (type) {
	case CellType::Mine:
		if (setImageForMineType() == Result::failure)
			return Result::failure;
		break;
	case CellType::Blank:
		if (setImageForBlankType() == Result::failure)
			return Result::failure;
		break;
	case CellType::Number:
		if (setImageForNumberType() == Result::failure)
			return Result::failure;
		break;
	default:
		break;
	}

	return Result::success;
}


Result Cell::setNumber(const int number) {
	if (cell_type != CellType::Number || cell_number == number)
		return Result::failure;

	cell_number = number;

	if (setImageForNumberType() == Result::failure)
		return Result::failure;

	return Result::success;
}


Result Cell::setState(const CellState state) {
	if (cell_state == state)
		return Result::failure;

	cell_state = state;

	return Result::success;
}


void Cell::reset() {
	cell_type = CellType::Unknown;
	cell_state = CellState::Closed;
	cell_number = 0;
}


CellType Cell::getType() const {
	return cell_type;
}


CellState Cell::getState() const {
	return cell_state;
}


int Cell::getNumber() const {
	switch (cell_type) {
	case CellType::Mine:
		return -1;
	case CellType::Number:
		return cell_number;
	}
	return 0;
}



// OVERRIDING METHODS

sf::Vector2f Cell::getSize() const {
	return sf::Vector2f(DEFAULT_CELL_SIZE, DEFAULT_CELL_SIZE);
}


sf::Vector2u Cell::getImageSize() const {
	return sf::Vector2u(DEFAULT_CELL_SIZE, DEFAULT_CELL_SIZE);
}


sf::Sprite Cell::getDefaultSprite() const {
	sf::Sprite sprite = button_at_state.at(cell_state).getDefaultSprite();
	sprite.scale(getScale());

	return sprite;
}


sf::Sprite Cell::getHoveredSprite() const {
	sf::Sprite sprite = button_at_state.at(cell_state).getHoveredSprite();
	sprite.scale(getScale());

	return sprite;
}


void Cell::setTopLeftPosition(const sf::Vector2f& pos_top_left) {
	this->Button::setTopLeftPosition(pos_top_left);

	for (auto i = button_at_state.begin(); i != button_at_state.end(); i++) {
		i->second.setTopLeftPosition(this->pos_top_left);
	}
}


Result Cell::setImage(const TextureType texture_type, const sf::Vector2f& pos_top_left, const sf::Vector2f& scale) {
	return Result::failure;
}


void Cell::setPadding(const sf::Vector2f& padding) {}


void Cell::setScale(const sf::Vector2f& scale) {}


void Cell::alignImageAndText() {}


Result Cell::centerTextInButton() {
	return Result::failure;
}
