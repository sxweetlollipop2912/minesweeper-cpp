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
	friend class Window;

private:
	std::vector <std::vector <Cell> > board;
	int number_of_rows;
	int number_of_cols;

	sf::RenderTexture board_rendertexture;
	sf::Vector2i hovered_cell;

	// Sets type of the cell at requested position.
	// `number` param is for CellType::Number.
	// Returns Result::success / Result::failure:
	//	> success: cell type is successfully set.
	//	> failure: cell has been set to the desired type b4 calling this method OR image cannot be loaded.
	// Regardless of the result, the cell is at desired type at return time.
	Result setCellType(const Position& pos, const CellType type, const int number = -1);
	// Updates board RenderTexture base on current board.
	void updateBoardRenderTexture();

public:
	Board() : Button() {
		button_type = ButtonType::Board;
		number_of_rows = number_of_cols = 0;
		pos_top_left.x = pos_top_left.y = 0;

		hovered_cell = sf::Vector2i(-1, -1);

		board.clear();
	}

	Board(const int rows, const int cols) : Button() {
		std::cout << "BOARD INITING\n";

		button_type = ButtonType::Board;
		pos_top_left.x = pos_top_left.y = 0;
		number_of_rows = rows;
		number_of_cols = cols;

		hovered_cell = sf::Vector2i(-1, -1);
		
		board.resize(number_of_rows);
		for (int i = 0; i < number_of_rows; i++) {
			board[i].resize(number_of_cols);

			for (int j = 0; j < number_of_cols; j++) {
				sf::Vector2f rel_pos;
				rel_pos.x = DEFAULT_CELL_SIZE * j;
				rel_pos.y = DEFAULT_CELL_SIZE * i;

				board[i][j].setTopLeftPosition(rel_pos);

				std::cout << "CELL " << i << ' ' << j << ' ' << board[i][j].getPosTopLeft().x << ' ' << board[i][j].getPosTopLeft().y << '\n';
			}
		}

		updateBoardRenderTexture();

		std::cout << "BOARD INIT COMPLETED\n";
	}

	// Updates the grahics side of the board.
	// Returns Result::success / Result::failure:
	//	> success: board is successfully updated.
	//	> failure: board has not been changed after calling this method.
	// Regardless of the result, the board is up-to-date at return time.
	Result updateBoard(const GameCell new_board[][MAX_COLUMN], const char mine_board[][MAX_COLUMN], const int rows, const int cols);
	// Assigns all elements in board to default value.
	void resetAllCells();

	bool isValidPos(const Position& pos) const;


	// OVERRIDED BUTTON METHODS

	// Gets size of the button (after apply scaling).
	sf::Vector2f getSize() const override;
	// Gets original size of the button's image (b4 apply scaling).
	sf::Vector2u getImageSize() const override;
	// Gets default (not hovered) button's sprite.
	sf::Sprite getDefaultSprite() const override;
	// Gets hovered (not hovered) button's sprite.
	sf::Sprite getHoveredSprite() const override;

	void setButtonType(const ButtonType& button_type) override;
	Result setImage(const std::string& img_path, const sf::Vector2f& pos_top_left = sf::Vector2f(-1, -1), const sf::Vector2f& scale = sf::Vector2f(1, 1)) override;
	void setPadding(const sf::Vector2f& padding) override;
	void setScale(const sf::Vector2f& scale) override;
	void alignImageAndText() override;
	Result centerTextInButton() override;
};