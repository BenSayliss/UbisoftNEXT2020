#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

// how many lines to draw
#define ENEMY_SHOOTER_LINE_COUNT 8
// speed multipler
#define ENEMY_SHOOTER_SPEED 0.0005f

#include "BaseEnemy.h"

// derived from BaseEnemy
class EnemyShooter : public BaseEnemy
{
public:
	// default constructor
	EnemyShooter();
	// constructor that takes in float radius and vec3 rbg values
	EnemyShooter(float r_, Vec3 rbg_);
	// constructor that takes in vec2 position, vec2 direction, and float radius
	EnemyShooter(Vec2 pos_, Vec2 dir_, float r_);
	// constructor that takes in vec2 position, vec2 direction, float radius, and vec3 rgb values
	EnemyShooter(Vec2 pos_, Vec2 dir_, float r_, Vec3 rgb_);
	// destructor
	~EnemyShooter();

	// on destroy called from destructor
	void OnDestroy();

	// initialize generic information
	void Init();

	// create the lines that will be used to draw later on (different lines, hence why this is overridden)
	void CreateShipLines();

	// update the enemy (all enemies move differently so that is why this is overridden)
	void Update(float dt_);

};
#endif