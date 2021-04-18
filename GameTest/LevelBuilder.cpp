#include "stdafx.h"
#include "LevelBuilder.h"

// for window width and height
#include "App/app.h"

// static variables
std::unique_ptr<LevelBuilder> LevelBuilder::levelBuilderInstance = nullptr;

// default constructor
LevelBuilder::LevelBuilder() {}

// destructor
LevelBuilder::~LevelBuilder() {}

// returns the instance of the LevelBuilder, will only ever be one instance (singleton)
LevelBuilder* LevelBuilder::GetInstance() {
	// if there isn't an instance,
	if (levelBuilderInstance.get() == nullptr) {
		// create one
		levelBuilderInstance.reset(new LevelBuilder);
	}
	// return the instance of LevelBuilder
	return levelBuilderInstance.get();
}

// creates a level based on i (in the future, i will be what type of level will be created)
// this makes adding more levels very easy
Level* LevelBuilder::CreateLevel(int levelType_) {
	// initialize vectors for lines
	std::vector<Line> front;
	std::vector<Line> back;
	std::vector<Line> joining;

	front.reserve(LEVEL_LINE_COUNT);
	back.reserve(LEVEL_LINE_COUNT);
	joining.reserve(LEVEL_LINE_COUNT);

	// make sure the numbers are random - based off of the seconds in the clock of the computer
	srand(time(0));
	// ---------------------------------------------------------------------- PLEASE READ! --------------------------------------------------------------------------------
	// I have hardcoded an angle for randomAngle for testing purposes!
	// My math is a little bit off down below and the backLevelLines are a little scews left or right depending on the angle
	// but you are more than welcome to use the random angle!
	//            vv
	// float randomAngle = (rand() % 100) + 20; // 0.0f - 89.999f
	float randomAngle = 90.0f; // - testing

	float lineSize = APP_INIT_WINDOW_WIDTH / 8;

	// which kind of level pattern we are building - only one right now
	switch (levelType_) {
	case 0:
		// Pattern 1
		// FRONT LINES	
		// Creates the initial pattern
		if (randomAngle >= 90.0f) {
			CreateLinePattern1(front, randomAngle, lineSize, Vec2(APP_INIT_WINDOW_WIDTH - APP_INIT_WINDOW_WIDTH / 4 * (randomAngle / 90.0f), APP_INIT_WINDOW_HEIGHT / 2));
		}
		else {
			// ------------------------------------------------------------------------------------- FIX THIS LATER ---vv-------------------------------------------
			CreateLinePattern1(front, randomAngle, lineSize, Vec2(APP_INIT_WINDOW_WIDTH - APP_INIT_WINDOW_WIDTH / 4 * (randomAngle / 90.0f), APP_INIT_WINDOW_HEIGHT / 2));
		}

		// BACK LINES
		// This is the part that is always a little bit skewed
		CreateLinePattern1(back, randomAngle, lineSize / 8, Vec2(APP_INIT_WINDOW_WIDTH / 2 + lineSize / 4, APP_INIT_WINDOW_HEIGHT / 2 - lineSize / 4));

		// JOINING LINES
		// Basically connect the front and back parts of the level
		for (int i = 0; i < LEVEL_LINE_COUNT; i++) {
			joining.push_back(Line(back.at(i).start, front.at(i).start));
		}
		break;
	}

	// return the new level *
	return new Level(front, back, joining);
}

// This function simply starts off at a certain position and creates a vertical line
// After that it rotates one way, then rotates the other, and repeats this 3 more times in order to create a different looking level (same pattern though, just different angle!)
// Takes in which section (front, back, or joining), an angle, the length of each line, and a starting position
void LevelBuilder::CreateLinePattern1(std::vector<Line>& l_, float angle_, float lineSize_, Vec2 pos_) {
	// FUN MATH
	Vec2 oldLineDir = (pos_ + Vec2(0, lineSize_)) - pos_;
	// starting 
	Line oldLine = Line(pos_, pos_ + oldLineDir);

	// orients the level
	Vec2 initialDir = VMath::Rotate(oldLine.end - oldLine.start, (90 - angle_) / 2);
	
	// orients the first line
	oldLine = Line(oldLine.start, oldLine.start + initialDir);

	// store the startingLine as a reference for later
	Line startingLine = oldLine;
	// push the line onto the vector
	l_.push_back(oldLine);
	// create an equal amount of sections (mine is 16 / 4)
	for (int i = 0; i < LEVEL_LINE_COUNT / LEVEL_SECTIONS; i++) {
		// creates the firts line direction
		Vec2 startingDir = startingLine.end - startingLine.start;
		// for each section, create the line
		for (int j = 0; j < LEVEL_LINE_COUNT / LEVEL_SECTIONS - 1; j++) {
			// VECTOR MATH TIME
			// swap every other time which way it rotates!
			Vec2 dir = oldLine.end - oldLine.start;
			// every other line will rotate
			if (j % 2 == 0) {
				dir = VMath::Rotate(dir, angle_);
			}
			else {
				dir = VMath::Rotate(dir, -angle_);
			}
			// create next line
			Line nextLine = Line(oldLine.end, oldLine.end + dir);
			// add to vector
			l_.push_back(nextLine);
			// change the oldLine to this one
			oldLine = nextLine;
		}

		// update the direction
		startingDir = VMath::Rotate(startingDir, 90.0f);
		// create the line
		oldLine = Line(oldLine.end, oldLine.end + startingDir);
		// add to vector
		l_.push_back(oldLine);
		// update the new line (point of reference)
		startingLine = oldLine;
	}
}