#include "Position.h"


void Position::operator=(const Position& pos) {
	x = pos.x;
	y = pos.y;
}


Position Position::operator+(const Position& pos) const {
	Position res;
	res.x = x + pos.x;
	res.y = y + pos.y;
	return res;
}


Position Position::operator-(const Position& pos) const {
	Position res;
	res.x = x - pos.x;
	res.y = y - pos.y;
	return res;
}


bool Position::operator==(const Position& pos) const {
	return x == pos.x && y == pos.y;
}


bool Position::operator<(const Position& pos) const {
	return x < pos.x || (x == pos.x && y < pos.y);
}
