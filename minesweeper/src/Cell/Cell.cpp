#include <iostream>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "../Button/Button.h"
#include "../Enums.h"
#include "../Constants.h"


Result Cell::setDefaultImages() {
	Button& closed = button_at_state[CellState::Closed];
	Button& flagged = button_at_state[CellState::Flagged];

	if (closed.setImage(CLOSED_CELL_IMG_PATH) == Result::failure)
		return std::cout << "FAILED\n", Result::failure;

	if (flagged.setImage(FLAGGED_CELL_IMG_PATH) == Result::failure)
		return std::cout << "FAILED\n", Result::failure;

	sf::Vector2f scale;
	scale.x = DEFAULT_CELL_SIZE / (float)closed.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)closed.getImageSize().y;
	closed.setScale(scale);

	scale.x = DEFAULT_CELL_SIZE / (float)flagged.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)flagged.getImageSize().y;
	closed.setScale(scale);

	std::cout << "SET IMAGE COMPLETED\n";
	return Result::success;
}


Result Cell::setImageForMineType() {
	Button& opened = button_at_state[CellState::Opened];

	if (opened.setImage(MINE_CELL_IMG_PATH) == Result::failure)
		return Result::failure;

	sf::Vector2f scale;
	scale.x = DEFAULT_CELL_SIZE / (float)opened.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)opened.getImageSize().y;
	opened.setScale(scale);

	return Result();
}


Result Cell::setImageForBlankType() {
	Button& opened = button_at_state[CellState::Opened];

	if (opened.setImage(BLANK_CELL_IMG_PATH) == Result::failure)
		return Result::failure;

	sf::Vector2f scale;
	scale.x = DEFAULT_CELL_SIZE / (float)opened.getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)opened.getImageSize().y;
	opened.setScale(scale);

	return Result();
}


Result Cell::setImageForNumberType() {
	Button& opened = button_at_state[CellState::Opened];

	std::string img_path;
	switch (cell_number) {
	case 1:
		img_path = NUM_1_CELL_IMG_PATH;
		break;
	case 2:
		img_path = NUM_2_CELL_IMG_PATH;
		break;
	case 3:
		img_path = NUM_3_CELL_IMG_PATH;
		break;
	case 4:
		img_path = NUM_4_CELL_IMG_PATH;
		break;
	case 5:
		img_path = NUM_5_CELL_IMG_PATH;
		break;
	case 6:
		img_path = NUM_6_CELL_IMG_PATH;
		break;
	case 7:
		img_path = NUM_7_CELL_IMG_PATH;
		break;
	case 8:
		img_path = NUM_8_CELL_IMG_PATH;
		break;
	default:
		return Result::failure;
	}

	if (opened.setImage(img_path) == Result::failure)
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



// OVERRIDED METHODS

sf::Vector2f Cell::getSize() const {
	return sf::Vector2f(DEFAULT_CELL_SIZE, DEFAULT_CELL_SIZE);
}


sf::Vector2u Cell::getImageSize() const {
	return sf::Vector2u(DEFAULT_CELL_SIZE, DEFAULT_CELL_SIZE);
}


sf::Sprite Cell::getDefaultSprite() const {
	sf::Sprite sprite = button_at_state.at(cell_state).getDefaultSprite();
	sf::Vector2f scale;

	scale.x = DEFAULT_CELL_SIZE / (float)button_at_state.at(cell_state).getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)button_at_state.at(cell_state).getImageSize().y;
	sprite.scale(scale);

	return sprite;
}


sf::Sprite Cell::getHoveredSprite() const {
	sf::Sprite sprite = button_at_state.at(cell_state).getHoveredSprite();
	sf::Vector2f scale;

	scale.x = DEFAULT_CELL_SIZE / (float)button_at_state.at(cell_state).getImageSize().x;
	scale.y = DEFAULT_CELL_SIZE / (float)button_at_state.at(cell_state).getImageSize().y;
	sprite.scale(scale);

	return sprite;
}


void Cell::setButtonType(const ButtonType& button_type) {}


Result Cell::setImage(const std::string& img_path, const sf::Vector2f& pos_top_left, const sf::Vector2f& scale) {
	return Result::failure;
}


void Cell::setPadding(const sf::Vector2f& padding) {}


void Cell::setScale(const sf::Vector2f& scale) {}


void Cell::alignImageAndText() {}


Result Cell::centerTextInButton() {
	return Result::failure;
}
