#ifndef STATTRACKER_H
#define STATTRACKER_H

#define STARTING_LIVES 3

#include "App/app.h"
#include <sstream>
#include "Ship.h"

// Singleton - we only want one instance of the stat tracker
struct StatTracker
{
	// delete the copy and move constructors
	StatTracker(const StatTracker&) = delete;
	StatTracker(StatTracker&&) = delete;
	StatTracker& operator = (const StatTracker&) = delete;
	StatTracker& operator = (StatTracker&&) = delete;

	// return instance 
	static StatTracker* GetInstance();
	
	// draw the text that displays the lives and score
	static void DrawInfo(Ship* s_);

private:
	// private constructor so you cannot create an object of type StatTracker
	StatTracker();
	// private destructor
	~StatTracker();

	// pointer for containing the instance of StatTracker
	static std::unique_ptr<StatTracker> statTrackerInstance;
	// default delete function for the above pointer ^^
	friend std::default_delete<StatTracker>;
	

};
#endif

