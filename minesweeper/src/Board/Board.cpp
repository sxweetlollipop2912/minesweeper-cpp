#include "Board.h"
#include "Position.h"
#include "../Enums.h"


Result Board::setCellType(const Position& pos, const CellType type, const int number) {
	if (board[pos.r][pos.c].setType(type, number) == Result::failure)
		return Result::failure;

	updateBoardRenderTexture();
	
	return Result::success;
}


void Board::updateBoardRenderTexture() {
	board_rendertexture.clear();

	for (int i = 0; i < number_of_rows; i++) {
		for (int j = 0; j < number_of_cols; j++) {
			if (sf::Vector2i(i, j) != hovered_cell) {
				board_rendertexture.draw(board[i][j].getDefaultSprite());
			}
			else {
				board_rendertexture.draw(board[i][j].getHoveredSprite());
			}
		}
	}
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

	if (change) updateBoardRenderTexture();

	return change ? Result::success : Result::failure;
}


void Board::resetAllCells() {
	for (int i = 0; i < number_of_rows; i++)
		for (int j = 0; j < number_of_cols; j++) {
			board[i][j].reset();
		}

	updateBoardRenderTexture();
}


bool Board::isValidPos(const Position& pos) const {
	return pos.r >= 0 && pos.r < number_of_rows&& pos.c >= 0 && pos.c < number_of_cols;
}



// OVERRIDED METHODS

sf::Vector2f Board::getSize() const {
	return sf::Vector2f(DEFAULT_CELL_SIZE * number_of_cols, DEFAULT_CELL_SIZE * number_of_rows);
}


sf::Vector2u Board::getImageSize() const {
	return sf::Vector2u(DEFAULT_CELL_SIZE * number_of_cols, DEFAULT_CELL_SIZE * number_of_rows);
}


sf::Sprite Board::getDefaultSprite() const {
	std::cout << "SPRITE DEFAULT\n";
	sf::Sprite sprite;
	loadSpriteFromTexture(sprite, board_rendertexture.getTexture(), pos_top_left);
	return sprite;
}


sf::Sprite Board::getHoveredSprite() const {
	std::cout << "SPRITE HOVERED\n";
	sf::Sprite sprite;
	loadSpriteFromTexture(sprite, board_rendertexture.getTexture(), pos_top_left);
	return sprite;
}


void Board::setButtonType(const ButtonType& button_type) {}


Result Board::setImage(const std::string& img_path, const sf::Vector2f& pos_top_left, const sf::Vector2f& scale) {
	return Result::failure;
}


void Board::setPadding(const sf::Vector2f& padding) {}


void Board::setScale(const sf::Vector2f& scale) {}


void Board::alignImageAndText() {}


Result Board::centerTextInButton() {
	return Result::failure;
}


