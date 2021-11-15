#include "Position.h"


void Position::operator=(const Position& pos) {
	r = pos.r;
	c = pos.c;
}


Position Position::operator+(const Position& pos) const {
	Position res;
	res.r = r + pos.r;
	res.c = c + pos.c;
	return res;
}


Position Position::operator-(const Position& pos) const {
	Position res;
	res.r = r - pos.r;
	res.c = c - pos.c;
	return res;
}


bool Position::operator==(const Position& pos) const {
	return r == pos.r && c == pos.c;
}


bool Position::operator<(const Position& pos) const {
	return r < pos.r || (r == pos.r && c < pos.c);
}
