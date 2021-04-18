#ifndef SHIP_H
#define SHIP_H

// how many lines are drawn for the ship
#define SHIP_LINE_COUNT 10
// timer for how fast you can move
#define MOVEMENT_TIMER 3
// timer for how fast you can shoot
#define SHOOTING_TIMER 10
// starting number of lives
#define STARTING_LIVES 3

#include "Level.h"
#include "App/app.h"
#include "Bullet.h"
#include "EnemyManager.h"

// inherits from sphere (for position and radius)
class Ship : public Sphere
{
public:
	// default constructor
	Ship();
	// destructor
	~Ship();

	// called from destructor
	void OnDestroy();

	// will be helpful if more constructors are added in the future
	void Init();

	// Math behind creating the ship's lines based on the level! is drawn later
	void CreateShipLines(Level* l_);
	// retursn the shipLines vector
	std::vector<Line> GetShipLines();

	// move the ship left one line
	void MoveShipLeft();
	// move the ship right one line
	void MoveShipRight();
	// draw the ship
	void Draw();

	// shoot towards the center of the screen (based on level)
	void Shoot(Level* l_);

	// return int pos (this pos is once again the iterator for the level's frontLevelLines)
	int GetPos();
	// return int movement timer
	int GetMovementTimer();
	// return int shooting timer
	int GetShootingTimer();

	// return int lives
	int GetLives();
	// return int score
	int GetScore();

	// increase lives by 1 - not used for now
	void IncrementLives();
	// decrease lives by 1 - this is the best place to check to see if live have hit 0 and trigger game over
	void DecrementLives();
	// reset lives 
	void ResetLives();

	// reset movement timer
	void ResetMovementTimer();
	// reset shooting timer
	void ResetShootingTimer();

	// decrease movement timer
	void DecrementMovementTimer();
	// decrease shooting timer
	void DecrementShootingTimer();

	// update the ship based on deltatime and check for bullet collision as bullets are a part of the ship class
	void Update(float dt_);

	// set the rgbvalues based on 3 floats
	void SetRGBValues(float r_, float g_, float b_);
	// set the rgb values based on vec3
	void SetRGBValues(Vec3 rgb_);
	// returns vec3 rgb values
	Vec3 GetRGBValues();

protected:
	// this integer represents the spot at the level's frontLevelLines vector
	int pos;

	// int for lives
	int lives;
	// int for keeping track of score
	int score;
	// ints for both timers
	int movementTimer, shootingTimer;

	// floats for RGB values
	float colourR, colourG, colourB;

	// vector that holds the ship's lines (for drawing)
	std::vector<Line> shipLines;
	// vector that holds all bullets on the screen (that come from the ship)
	std::vector<Bullet*> bullets;

	// helper method for removing a bullet
	void RemoveBullet(int i_);
};
#endif

