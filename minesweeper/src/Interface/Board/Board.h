#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Position.h"
#include "../Cell/Cell.h"
#include "../Button/Button.h"
#include "../../Enums.h"
#include "../../Constants.h"


struct GameCell {
	bool isOpened;
	bool isFlag;
	int mineCount;
};


class Board : public Button {
	friend class PlayingScene;

private:
	std::vector <std::vector <Cell> > board;
	int number_of_rows;
	int number_of_cols;
	float cell_size;

	Position last_pressed_cell;
	Position hovered_cell;

	// Assigns all elements in board to default value.
	void resetAllCells();
	// Updates the grahics side of the board.
	// Returns Result::success / Result::failure:
	//	> success: board is successfully updated.
	//	> failure: board has not been changed after calling this method.
	// Regardless of the result, the board is up-to-date at return time.
	Result updateBoard(const GameCell cell_board[][MAX_COLUMN], const char mine_board[][MAX_COLUMN]);
	// Determines the hovered cell given current mouse position.
	// Returns true if the hovered cell is changed.
	// Otherwise, returns false.
	bool determineHoveredCell(const sf::Vector2i mouse_pos);
	// Sets type of the cell at requested position.
	// `number` param is for CellType::Number.
	// Returns Result::success / Result::failure:
	//	> success: cell type is successfully set.
	//	> failure: cell has been set to the desired type b4 calling this method OR image cannot be loaded.
	// Regardless of the result, the cell is at desired type at return time.
	Result setCellType(const Position& pos, const CellType type, const int number = -1);
	// Sets size of all cells.
	void setCellSize(const int cell_size);


	// OVERRIDING BUTTON METHODS

	// Sets top-left position of the whole board in respect of window size.
	void setTopLeftPos(const sf::Vector2f& top_left_pos) override;

public:
	Board(const int rows = 0, const int cols = 0);


	int getRows() const;
	int getCols() const;
	Position getLastPressedCell() const;

	// Checks if a coordinate is valid on this board.
	bool isValidPos(const Position& pos) const;


	// OVERRIDING BUTTON METHODS

	// Gets size of the button (after apply scaling).
	sf::Vector2f getSize() const override;
	// Gets original size of the button's image (b4 apply scaling).
	sf::Vector2u getImageSize() const override;
	// Gets default (not hovered) button's sprite.
	void getDefaultSprite(sf::Sprite& sprite) const override;
	// Gets hovered (not hovered) button's sprite.
	void getHoveredSprite(sf::Sprite& sprite) const override;

	Result setImage(const TextureType texture_type, const sf::Vector2f& top_left_pos = sf::Vector2f(-1, -1), const sf::Vector2f& scale = sf::Vector2f(1, 1)) override;
	void setPadding(const sf::Vector2f& padding) override;
	void setScale(const sf::Vector2f& scale) override;
	void alignImageAndText() override;
	Result centerTextInButton() override;
};