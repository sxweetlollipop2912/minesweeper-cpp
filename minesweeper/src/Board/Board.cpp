#include "Board.h"
#include "Position.h"
#include "../Enums.h"


Result Board::setCellType(const Position& pos, const CellType type, const int number) {
	return board[pos.r][pos.c].setType(type, number);
}


Result Board::updateBoard(const GameCell new_board[][MAX_COLUMN], const char mine_board[][MAX_COLUMN], const int rows, const int cols) {
	bool change = false;
	
	if (number_of_rows != rows || number_of_cols != cols) {
		change = true;

		number_of_rows = rows;
		number_of_cols = cols;

		board.resize(rows);
		for (int i = 0; i < rows; i++)
			board[i].resize(cols);
	}

	for (int i = 0; i < number_of_rows; i++) {
		for (int j = 0; j < number_of_cols; j++) {

			if (mine_board[i][j] == '&') { // Cell is mine.
				if (board[i][j].setType(CellType::Mine) == Result::success)
					change = true;
			}

			else {
				if (new_board[i][j].mineCount != 0) {
					if (board[i][j].setType(CellType::Number, new_board[i][j].mineCount) == Result::success)
						change = true;
				}
				else {
					if (board[i][j].setType(CellType::Blank) == Result::success)
						change = true;
				}

				if (new_board[i][j].isOpened) {
					if (new_board[i][j].isFlag) {
						if (board[i][j].setState(CellState::Flagged) == Result::success)
							change = true;
					}
					else {
						if (board[i][j].setState(CellState::Opened) == Result::success)
							change = true;
					}
				}
				else {
					if (board[i][j].setState(CellState::Closed) == Result::success)
						change = true;
				}
			}
		}
	}

	return change ? Result::success : Result::failure;
}


void Board::resetAllCells() {
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_cols; j++) {
			board[i][j].reset();
		}
}


bool Board::isValidPos(const Position& pos) const {
	return pos.r >= 0 && pos.r < number_of_rows&& pos.c >= 0 && pos.c < number_of_cols;
}

