#ifndef BULLET_H
#define BULLET_H

#include "App/app.h"
#include "Sphere.h"

// speed multiplier
#define BASE_BULLET_SPEED 0.005f

// should make a gameobject class to inherit ship, bullet, and enemies from

// Bullets go straight from ship to the middle of the screen
class Bullet : public Sphere
{
public:
	// constructor that takes in a vec2 position, vec2 direction, and vec2 ending location
	Bullet(Vec2 pos_, Vec2 dir_, Vec2 endLoc_);\
	// constructor that takes in a vec2 position, vec2 direction, vec2 ending location, a sprite fileName (as well as column and row)
	Bullet(Vec2 pos_, Vec2 dir_, Vec2 endlLoc_, char* fileName_, int column_, int row_);
	// destructor
	~Bullet();
	
	// draws the bullet based on the sprite
	void DrawBullet();
	// updates the movement based on deltaTime and the sprite's positiong
	void Update(float dt_);

	// returns vec2 dir
	Vec2 GetDir();
	// returns float speed
	float GetSpeed();
	// returns vec2 endLoc
	Vec2 GetEndLoc();

	// sets vec2 dir
	void SetDir(Vec2 dir_);
	// sets float speed
	void SetSpeed(float speed_);
	// sets vec2 endLoc
	void SetEndLoc(Vec2 endLoc_);

	// sets the scale of the sprite
	void SetSpriteScale(float scale_);

private:
	// pointer for the sprite
	CSimpleSprite* sprite;
	// direction
	Vec2 dir;
	// speed
	float speed;
	// ending Location
	Vec2 endLoc;

	// Initialize other attributes
	void Init();
	
};
#endif