#include <iostream>

#include "Cell.h"


Cell::Cell() {
	button_at_state.clear();
	setDefaultImages();

	top_left_pos.x = top_left_pos.y = 0;

	cell_type = CellType::Unknown;
	cell_state = CellState::Closed;
	cell_number = 0;
}


sf::Vector2f Cell::getScale() const {
	auto img_size = button_at_state.at(getState()).getImageSize();
	sf::Vector2f scale;
	scale.x = cell_size / img_size.x;
	scale.y = cell_size / img_size.y;
	return scale;
}


Result Cell::setDefaultImages() {
	Button& closed = button_at_state[CellState::Closed];
	Button& flagged = button_at_state[CellState::Flagged];

	if (closed.setImage(TextureType::CellClosed) == Result::failure)
		return Result::failure;

	if (flagged.setImage(TextureType::CellFlagged) == Result::failure)
		return Result::failure;

	return Result::success;
}


Result Cell::setImageForMineType() {
	Button& opened = button_at_state[CellState::Opened];

	if (opened.setImage(TextureType::CellMine) == Result::failure)
		return Result::failure;

	return Result::success;
}


Result Cell::setImageForBlankType() {
	Button& opened = button_at_state[CellState::Opened];

	if (opened.setImage(TextureType::CellBlank) == Result::failure)
		return Result::failure;

	return Result::success;
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

	return Result::success;
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
		if (setImageForMineType() == Result::failure) {
			std::cout << "failed!!!!\n";
			return Result::failure;
		}
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
	return sf::Vector2f(cell_size, cell_size);
}


sf::Vector2u Cell::getImageSize() const {
	return button_at_state.at(getState()).getImageSize();
}


void Cell::getDefaultSprite(sf::Sprite& sprite) const {
	button_at_state.at(cell_state).getDefaultSprite(sprite);
	sprite.scale(getScale());
	sprite.setPosition(top_left_pos);
}


void Cell::getHoveredSprite(sf::Sprite& sprite) const {
	button_at_state.at(cell_state).getHoveredSprite(sprite);
	sprite.scale(getScale());
	sprite.setPosition(top_left_pos);
}


void Cell::setTopLeftPos(const sf::Vector2f& top_left_pos) {
	this->Button::setTopLeftPos(top_left_pos);
}


void Cell::setSize(const sf::Vector2f& size) {
	if (std::abs(size.x - size.y) > EPS) return;
	cell_size = size.x;
}


Result Cell::setImage(const TextureType texture_type, const sf::Vector2f& top_left_pos, const sf::Vector2f& scale) {
	return Result::failure;
}


void Cell::setPadding(const sf::Vector2f& padding) {}


void Cell::setScale(const sf::Vector2f& scale) {}


void Cell::alignImageAndText() {}


Result Cell::centerTextInButton() {
	return Result::failure;
}
