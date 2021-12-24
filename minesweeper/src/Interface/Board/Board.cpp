#include "Board.h"


Board::Board(const int rows, const int cols) {
	top_left_pos = sf::Vector2f(0, 0);
	number_of_rows = rows;
	number_of_cols = cols;
	cell_size = MIN_CELL_SIZE;

	hovered_cell = Position(-1, -1);

	board.resize(number_of_rows);
	for (int i = 0; i < number_of_rows; i++) {
		board[i].resize(number_of_cols);
	}

	Board::setTopLeftPos(this->top_left_pos);
}


Result Board::setCellType(const Position& pos, const CellType type, const int number) {
	if (board[pos.r][pos.c].setType(type, number) == Result::failure)
		return Result::failure;
	
	return Result::success;
}


void Board::setCellSize(const int cell_size) {
	this->cell_size = cell_size;

	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_cols; j++) {
			board[i][j].setSize(sf::Vector2f(cell_size, cell_size));
		}
}


Result Board::updateBoard(const GAMECELL cell_board[][MAX_COLUMN], const char mine_board[][MAX_COLUMN]) {
	bool change = false;

	for (int i = 0; i < number_of_rows; i++) {
		for (int j = 0; j < number_of_cols; j++) {

			if (mine_board[i][j] == '&') { // Cell is mine.
				if (board[i][j].setType(CellType::Mine) == Result::success)
					change = true;
			}
			else {
				if (cell_board[i][j].mine_Count != 0) {
					if (board[i][j].setType(CellType::Number, cell_board[i][j].mine_Count) == Result::success)
						change = true;
				}
				else {
					if (board[i][j].setType(CellType::Blank) == Result::success)
						change = true;
				}
			}

			if (cell_board[i][j].isOpened) {
				if (board[i][j].setState(CellState::Opened) == Result::success)
					change = true;
			}
			else if (cell_board[i][j].isFlag) {
				if (board[i][j].setState(CellState::Flagged) == Result::success)
					change = true;
			}
			else {
				if (board[i][j].setState(CellState::Closed) == Result::success)
					change = true;
			}
		}
	}

	return change ? Result::success : Result::failure;
}


bool Board::determineHoveredCell(const sf::Vector2i mouse_pos) {
	Position last_hovered = hovered_cell;
	hovered_cell = Position(-1, -1);

	if (isMouseHovering(mouse_pos)) {
		hovered_cell.r = ((float)mouse_pos.y - top_left_pos.y) / cell_size;
		hovered_cell.c = ((float)mouse_pos.x - top_left_pos.x) / cell_size;
	}
	
	return hovered_cell != last_hovered;
}


void Board::resetAllCells() {
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_cols; j++) {
			board[i][j].reset();
		}
}


int Board::getRows() const {
	return number_of_rows;
}


int Board::getCols() const {
	return number_of_cols;
}


bool Board::isValidPos(const Position& pos) const {
	return pos.r >= 0 && pos.r < number_of_rows&& pos.c >= 0 && pos.c < number_of_cols;
}



// OVERRIDING METHODS

sf::Vector2f Board::getSize() const {
	return sf::Vector2f(cell_size * number_of_cols, cell_size * number_of_rows);
}


sf::Vector2u Board::getImageSize() const {
	return sf::Vector2u(cell_size * number_of_cols, cell_size * number_of_rows);
}


void Board::getDefaultSprite(sf::Sprite& sprite) const {}


void Board::getHoveredSprite(sf::Sprite& sprite) const {}


void Board::setTopLeftPos(const sf::Vector2f& top_left_pos) {
	this->Button::setTopLeftPos(top_left_pos);

	for (int i = 0; i < number_of_rows; i++) {
		for (int j = 0; j < number_of_cols; j++) {
			sf::Vector2f rel_pos;
			rel_pos.x = (cell_size) * (float)j;
			rel_pos.y = (cell_size) * (float)i;

			board[i][j].setTopLeftPos(this->top_left_pos + rel_pos);
		}
	}
}


Result Board::setImage(const TextureType texture_type, const sf::Vector2f& top_left_pos, const sf::Vector2f& scale) {
	return Result::failure;
}


void Board::setPadding(const sf::Vector2f& padding) {}


void Board::setScale(const sf::Vector2f& scale) {}


void Board::alignImageAndText() {}


void Board::centerTextInButton() {}


