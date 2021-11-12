#pragma once


class Position {
public:
	int x, y;
	Position() {
		x = -1; y = -1;
	}
	Position(const int x, const int y) {
		this->x = x; this->y = y;
	}
 
	void operator=(const Position&);
	Position operator+(const Position&) const;
	Position operator-(const Position&) const;
	bool operator==(const Position&) const;
	bool operator<(const Position&) const;
};