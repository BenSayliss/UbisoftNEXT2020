#include "stdafx.h"
#include "StatTracker.h"

// initialize static variables
std::unique_ptr<StatTracker> StatTracker::statTrackerInstance = nullptr;

// default private constructor
StatTracker::StatTracker() {}

// private destructor
StatTracker::~StatTracker() {}

// returns the instance of StatTracker
StatTracker* StatTracker::GetInstance() {
	// if there is not instance, 
	if (statTrackerInstance.get() == nullptr) {
		// create one
		statTrackerInstance.reset(new StatTracker);
	}
	// return the instance (will only ever be one!)
	return statTrackerInstance.get();
}

// draws the ship's info (lives, score, etc...)
void StatTracker::DrawInfo(Ship* s_) {
	// setup strings for displaying lives and score
	std::string stringLives = "Lives: " + std::to_string(s_->GetLives());
	std::string stringScore = "Score: " + std::to_string(s_->GetScore());

	// convert string to char*
	char* charLives = const_cast<char*>(stringLives.c_str());
	char* charScore = const_cast<char*>(stringScore.c_str());

	// print the lines on the screen
	App::Print(100, APP_INIT_WINDOW_HEIGHT - 100, charLives, s_->GetRGBValues().x, s_->GetRGBValues().y, s_->GetRGBValues().z);
	App::Print(100, APP_INIT_WINDOW_HEIGHT - 150, charScore, s_->GetRGBValues().x, s_->GetRGBValues().y, s_->GetRGBValues().z);	
	App::Print(100, APP_INIT_WINDOW_HEIGHT - 200, "Players lives reset for testing!", s_->GetRGBValues().x, s_->GetRGBValues().y, s_->GetRGBValues().z);
	App::Print(100, APP_INIT_WINDOW_HEIGHT - 50, "A - left   D - right   S - shoot", s_->GetRGBValues().x, s_->GetRGBValues().y, s_->GetRGBValues().z);

}