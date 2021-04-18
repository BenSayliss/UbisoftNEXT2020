#ifndef LEVELBUILDER_H
#define LEVELBUILDER_H

// this will change depending on how many level design patterns you implement!
#define NUM_LEVEL_PATTERNS 1

#include "../GameTest/SingletonT.h"
#include "Level.h"

// Singleton Design Pattern
// This level builder will generate a level
struct LevelBuilder
{
	// delete the copy and move constructors
	LevelBuilder(const LevelBuilder&) = delete;
	LevelBuilder(LevelBuilder&&) = delete;
	LevelBuilder& operator = (const LevelBuilder&) = delete;
	LevelBuilder& operator = (LevelBuilder&&) = delete;

	// levelType_ is meant to be created randomly and passed in to create ranomd levels!
	static Level* CreateLevel(int levelType_);	
	// return the instance of the LevelBuilder
	static LevelBuilder* GetInstance();
	

private:
	// private constructor so you cannot create an object of type CollisionHandler
	LevelBuilder();
	// private destructor
	~LevelBuilder();
	
	// pointer for containing the instance of CollisionHandler
	static std::unique_ptr<LevelBuilder> levelBuilderInstance;
	// default delete function for the above pointer ^^
	friend std::default_delete<LevelBuilder>;

	// helper methods
	static void CreateLinePattern1(std::vector<Line> &l_, float angle_, float lineSize_, Vec2 pos_);
};

#endif

