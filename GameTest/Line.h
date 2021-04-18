#ifndef LINE_H
#define LINE_H

#include "Vectors.h"

// structure that contains two Vec2s
// Makes drawing lines a bit easier to code
struct Line {
	// Vec2 for the staring and ending point of a line
	Vec2 start, end;

	// Constructor for Line taking in two vec2s
	inline Line(Vec2 start_, Vec2 end_) {
		start = start_;
		end = end_;
	}

	// assignment operator
	inline Line& operator = (const Line& l_) {
		start = l_.start;
		end = l_.end;
		return *this;
	}
};

#endif
