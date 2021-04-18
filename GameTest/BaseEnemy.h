#ifndef BASEENEMY_H
#define BASEENEMY_H

#include "Sphere.h"
#include "Line.h"
// for drawing
#include "App/app.h"

// Abstract base class for enemies! Just the EnemyShooter right now... EnemyShip inherits from the Ship class not BaseEnemy!!
class BaseEnemy : public Sphere
{
public:

	// default constructor
	BaseEnemy();
	// constructor that takes in radius, and rgb values stored in a vec3
	BaseEnemy(float r_, Vec3 rbg_);
	// constructors for future use --------
	// takes in position, direction (for movement), and radius
	BaseEnemy(Vec2 pos_, Vec2 dir_, float r_);
	// takes in position, direction (for movement), radius, and rgb values
	BaseEnemy(Vec2 pos_, Vec2 dir_, float r_, Vec3 rgb_);

	// pure virtual destructor
	virtual ~BaseEnemy() = 0;

	// initialize anything else - this will always run no matter the values that are passed in the constructor!
	// will also change based on the derived enemy class
	virtual void Init() = 0; // must be overriden
	// called when the destructor is called
	void OnDestroy();

	// pure virtual method! this does not have a definition and always needs to be implemented in any derived class!!
	virtual void CreateShipLines() = 0; // this should always be overridden
	
	// sets rgb values based on three floats
	void SetRGBValues(float r_, float g_, float b_);
	// sets rgb values based on a vec3
	void SetRGBValues(Vec3 rgb_);
	// returns the rgb values as a vec3
	Vec3 GetRGBValues();

	// sets the direction, takes in vec2
	void SetDir(Vec2 dir_);
	// sets the end location, takes in vec2
	void SetEndLoc(Vec2 endLoc_);
	// sets the speed, takes in float
	void SetSpeed(float s_);

	// returns the vec2 endLoc
	Vec2 GetEndLoc();
	// returns the int pointValue
	int GetPointValue();

	// updates the enemy based on deltaTime that is passed in
	void Update(float dt_);
	// draws the enemy
	void Draw();

protected:
	// point value for destroying the enemy
	int pointValue;
	// vector of Lines that hold the lines that are drawn
	std::vector<Line> shipLines;
	// vec2 for direction (movement)
	Vec2 dir;
	// vec2 that holds the position in which this object will be destroyed (end of track)
	Vec2 endLoc;
	// floats for R, G, B values
	float colourR, colourG, colourB;
	// float for movement speed multipler
	float speed;
};
#endif

