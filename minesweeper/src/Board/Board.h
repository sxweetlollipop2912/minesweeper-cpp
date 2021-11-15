#pragma once

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
private:
	std::vector <std::vector <Cell> > board;
	int number_of_rows;
	int number_of_cols;

	// Sets type of the cell at requested position.
	// `number` param is for CellType::Number.
	// Returns Result::success / Result::failure:
	//	> success: cell type is successfully set.
	//	> failure: cell has been set to the desired type b4 calling this method OR image cannot be loaded.
	// Regardless of the result, the cell is at desired type at return time.
	Result setCellType(const Position& pos, const CellType type, const int number = -1);

public:
	Board() {
		button_type = ButtonType::Board;
		number_of_rows = number_of_cols = 0;
		pos_top_left.x = pos_top_left.y = 0;

		board.clear();
	}

	Board(const int rows, const int cols) {
		button_type = ButtonType::Board;
		pos_top_left.x = pos_top_left.y = 0;
		number_of_rows = rows;
		number_of_cols = cols;

		board.clear();
		
		board.resize(rows);
		for (int i = 0; i < rows; i++)
			board[i].resize(cols);
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
};