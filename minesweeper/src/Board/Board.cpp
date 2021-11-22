#include "Board.h"
#include "Position.h"
#include "../Enums.h"


Result Board::setCellType(const Position& pos, const CellType type, const int number) {
	if (board[pos.r][pos.c].setType(type, number) == Result::failure)
		return Result::failure;
	
	return Result::success;
}


void Board::initialize(const int rows, const int cols, const sf::Vector2f pos_top_left) {
	this->Button::Button();

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


bool Board::determineHoveredCell(const sf::Vector2i mouse_pos) {
	Position last_hovered = hovered_cell;
	hovered_cell = Position(-1, -1);

	for (int i = 0; i < number_of_rows; i++) {
		for (int j = 0; j < number_of_cols; j++) {
			if (!board[i][j].isMouseHovering(mouse_pos)) continue;
			hovered_cell = Position(i, j);

			break;
		}
	}

	return hovered_cell != last_hovered;
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



// OVERRIDING METHODS

sf::Vector2f Board::getSize() const {
	return sf::Vector2f(DEFAULT_CELL_AREA * number_of_cols, DEFAULT_CELL_AREA * number_of_rows);
}


sf::Vector2u Board::getImageSize() const {
	return sf::Vector2u(DEFAULT_CELL_AREA * number_of_cols, DEFAULT_CELL_AREA * number_of_rows);
}


sf::Sprite Board::getDefaultSprite() const {
	sf::Sprite sprite;
	return sprite;
}


sf::Sprite Board::getHoveredSprite() const {
	sf::Sprite sprite;
	return sprite;
}


void Board::setTopLeftPosition(const sf::Vector2f& pos_top_left) {
	Button::setTopLeftPosition(pos_top_left);

	for (int i = 0; i < number_of_rows; i++) {
		for (int j = 0; j < number_of_cols; j++) {
			sf::Vector2f rel_pos;
			rel_pos.x = (DEFAULT_CELL_AREA) * (float)j;
			rel_pos.y = (DEFAULT_CELL_AREA) * (float)i;

			board[i][j].setTopLeftPosition(this->pos_top_left + rel_pos);
		}
	}
}


Result Board::setImage(const TextureType texture_type, const sf::Vector2f& pos_top_left, const sf::Vector2f& scale) {
	return Result::failure;
}


void Board::setPadding(const sf::Vector2f& padding) {}


void Board::setScale(const sf::Vector2f& scale) {}


void Board::alignImageAndText() {}


Result Board::centerTextInButton() {
	return Result::failure;
}


