#pragma once


class Position {
public:
	int r, c;
	Position() {
		r = -1; c = -1;
	}
	Position(const int r, const int c) {
		this->r = r; this->c = c;
	}
 
	void operator=(const Position&);
	Position operator+(const Position&) const;
	Position operator-(const Position&) const;
	bool operator!=(const Position&) const;
	bool operator==(const Position&) const;
	bool operator<(const Position&) const;
};