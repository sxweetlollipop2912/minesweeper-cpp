#pragma once

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Cell/Cell.h"
#include "Position.h"
#include "../Button/Button.h"
#include "../Enums.h"
#include "../Constants.h"


struct GameCell {
	bool isOpened;
	bool isFlag;
	int mineCount;
};


class Board : public Button {
	friend class PlayingScene;
	friend class Window;

private:
	std::vector <std::vector <Cell> > board;
	int number_of_rows;
	int number_of_cols;
	Position hovered_cell;

	// Assigns all elements in board to default value.
	void resetAllCells();
	// Updates the grahics side of the board.
	// Returns Result::success / Result::failure:
	//	> success: board is successfully updated.
	//	> failure: board has not been changed after calling this method.
	// Regardless of the result, the board is up-to-date at return time.
	Result updateBoard(const GameCell new_board[][MAX_COLUMN], const char mine_board[][MAX_COLUMN], const int rows, const int cols);
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


	// OVERRIDING BUTTON METHODS

	// Sets top-left position of the whole board in respect of window size.
	void setTopLeftPosition(const sf::Vector2f& pos_top_left) override;

public:
	Board(const int rows = 0, const int cols = 0, const sf::Vector2f pos_top_left = sf::Vector2f(0, 0)) {
		this->pos_top_left = pos_top_left;
		number_of_rows = rows;
		number_of_cols = cols;

		hovered_cell = Position(-1, -1);

		board.resize(number_of_rows);
		for (int i = 0; i < number_of_rows; i++) {
			board[i].resize(number_of_cols);
		}

		Board::setTopLeftPosition(this->pos_top_left);
	}


	int getRows() const;
	int getCols() const;

	// Checks if a coordinate is valid on this board.
	bool isValidPos(const Position& pos) const;


	// OVERRIDING BUTTON METHODS

	// Gets size of the button (after apply scaling).
	sf::Vector2f getSize() const override;
	// Gets original size of the button's image (b4 apply scaling).
	sf::Vector2u getImageSize() const override;
	// Gets default (not hovered) button's sprite.
	sf::Sprite getDefaultSprite() const override;
	// Gets hovered (not hovered) button's sprite.
	sf::Sprite getHoveredSprite() const override;

	Result setImage(const TextureType texture_type, const sf::Vector2f& pos_top_left = sf::Vector2f(-1, -1), const sf::Vector2f& scale = sf::Vector2f(1, 1)) override;
	void setPadding(const sf::Vector2f& padding) override;
	void setScale(const sf::Vector2f& scale) override;
	void alignImageAndText() override;
	Result centerTextInButton() override;
};