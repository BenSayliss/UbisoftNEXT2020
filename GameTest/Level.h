#ifndef LEVEL_H
#define LEVEL_H

// how many lines are in the level
// I use lots of defines as I believe it makes the code much more modular!!
#define LEVEL_LINE_COUNT 16
#define LEVEL_SECTIONS 4

#include "Line.h"
#include "App/app.h"

// this class contains three vectors for the three sections of each level:
// frontLevelLines - the front part of the level (the player moves on this section)
// backLevelLines - the back is the same shape as the front, just much smaller! (this is where the projectiles shoot into, and the enemies come from)
// joiningLevelLines - these are the lines that connect the front shape to the back shape
class Level {
public:
	// Default Constructor
	inline Level() {
		// reserve only the space we need!
		frontLevelLines.reserve(LEVEL_LINE_COUNT);
		backLevelLines.reserve(LEVEL_LINE_COUNT);
		joiningLevelLines.reserve(LEVEL_LINE_COUNT);
	}
	// store the three front, back, and joining vectors 
	// assume that the vectors have already been initialized and populated!
	inline Level(std::vector<Line> front_, std::vector<Line> back_, std::vector<Line> joining_) {		
		frontLevelLines = front_;
		backLevelLines = back_;
		joiningLevelLines = joining_;
	}
	
	// Destructor
	inline ~Level() {
		OnDestroy();
	}
	
	// called when the destructor is called
	inline void OnDestroy() {
		// clear out all of the lines
		frontLevelLines.clear();
		backLevelLines.clear();
		joiningLevelLines.clear();
	}

	// draw the level
	inline void DrawLevel() {
		// cycles through each value in the three vectors and draws a line for each!
		for (int i = 0; i < LEVEL_LINE_COUNT; i++) {
			App::DrawLine(frontLevelLines.at(i).start, frontLevelLines.at(i).end, 0.8f, 0.2f, 0.7f);
			App::DrawLine(backLevelLines.at(i).start, backLevelLines.at(i).end, 0.8f, 0.2f, 0.7f);
			App::DrawLine(joiningLevelLines.at(i).start, joiningLevelLines.at(i).end, 0.8f, 0.2f, 0.7f);
		}
	}

	// Getters
	inline std::vector<Line> GetFrontLines() {
		return frontLevelLines;
	}
	inline std::vector<Line> GetBackLines() {
		return backLevelLines;
	}
	inline std::vector<Line> GetJoiningLines() {
		return joiningLevelLines;
	}

private:
	// vectors for each part of the level
	// frontLevelLines - the front part of the level (the player moves on this section)
	std::vector<Line> frontLevelLines;
	// backLevelLines - the back is the same shape as the front, just much smaller! (this is where the projectiles shoot into, and the enemies come from)
	std::vector<Line> backLevelLines;
	// joiningLevelLines - these are the lines that connect the front shape to the back shape
	std::vector<Line> joiningLevelLines;
};

#endif
