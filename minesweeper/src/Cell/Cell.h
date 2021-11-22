#pragma once

#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Button/Button.h"
#include "../Enums.h"
#include "../Constants.h"


class Cell : public Button {
	friend class Board;

private:
	std::map <CellState, Button> button_at_state;

	CellType cell_type;
	CellState cell_state;
	int cell_number;

	
	// Gets scale for the cell base on current image's size and DEFAULT_CELL_SIZE.
	sf::Vector2f getScale() const;

	// Sets default images for `closed` and `flagged` states.
	Result setDefaultImages();
	Result setImageForMineType();
	Result setImageForBlankType();
	Result setImageForNumberType();

	// Sets type of the cell.
	// `number` param is for CellType::Number.
	// Returns Result::success / Result::failure:
	//	> success: cell type is successfully set.
	//	> failure: cell has been set to the desired type b4 calling this method OR image cannot be loaded.
	// Regardless of the result, the cell is at desired type at return time.
	Result setType(const CellType type, const int number = -1);
	// Sets number of the cell.
	// Returns Result::success / Result::failure:
	//	> success: cell's number is successfully set.
	//	> failure: cell's type is not in `CellType::number` OR number is already set b4 calling this method OR image cannot be loaded.
	Result setNumber(const int number);
	// Sets state of the cell.
	// Returns Result::success / Result::failure:
	//	> success: cell state is successfully set.
	//	> failure: cell has been set to the desired state b4 calling this method.
	// Regardless of the result, the cell is at desired state at return time.
	Result setState(const CellState state);
	// Resets a cell to initial state (cell_type, cell_state, cell_number).
	void reset();

public:
	Cell() : Button() {
		button_at_state.clear();
		setDefaultImages();

		button_type = ButtonType::Cell;
		pos_top_left.x = pos_top_left.y = 0;

		cell_type = CellType::Unknown;
		cell_state = CellState::Closed;
		cell_number = 0;
	}

	// Returns CellType `type` of the cell.
	CellType getType() const;
	// Returns CellState `state` of the cell
	CellState getState() const;
	// Returns the number of the cell if it is not a mine cell.
	// If it is a mine cell, returns -1.
	// If its type is `CellType::unknown` and `CellType::blank`, returns 0.
	int getNumber() const;


	// OVERRIDING BUTTON METHODS

	// Gets size of the cell.
	sf::Vector2f getSize() const override;
	// Gets original size of the cell's image.
	sf::Vector2u getImageSize() const override;
	// Gets default (not hovered) cell's sprite.
	sf::Sprite getDefaultSprite() const override;
	// Gets hovered (not hovered) cell's sprite.
	sf::Sprite getHoveredSprite() const override;

	// Sets top-left position of the cell in respect of window size.
	void setTopLeftPosition(const sf::Vector2f& pos_top_left) override;

	void setButtonType(const ButtonType& button_type) override;
	Result setImage(const TextureType texture_type, const sf::Vector2f& pos_top_left = sf::Vector2f(-1, -1), const sf::Vector2f& scale = sf::Vector2f(1, 1)) override;
	void setPadding(const sf::Vector2f& padding) override;
	void setScale(const sf::Vector2f& scale) override;
	void alignImageAndText() override;
	Result centerTextInButton() override;
};