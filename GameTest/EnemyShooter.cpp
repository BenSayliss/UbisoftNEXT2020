#include "stdafx.h"
#include "EnemyShooter.h"

// default constructor
EnemyShooter::EnemyShooter() {}

// constructor that takes in float radius and vec3 rbg values
EnemyShooter::EnemyShooter(float r_, Vec3 rgb_) {
	SetRadius(r_);
	SetRGBValues(rgb_);

	Init();
}

// constructor that takes in vec2 position, vec2 direction, and float radius
EnemyShooter::EnemyShooter(Vec2 pos_, Vec2 dir_, float r_) {
	SetSpherePos(pos_);
	SetRadius(r_);
	dir = dir_;

	Init();
}

// constructor that takes in vec2 position, vec2 direction, float radius, and vec3 rgb values
EnemyShooter::EnemyShooter(Vec2 pos_, Vec2 dir_, float r_, Vec3 rgb_) {
	SetSpherePos(pos_);
	SetRadius(r_);
	dir = dir_;
	SetRGBValues(rgb_);

	Init();
}

// destructor
EnemyShooter::~EnemyShooter() {
	OnDestroy();
}

// on destroy called from destructor
void EnemyShooter::OnDestroy() {
	shipLines.clear();
}

// initialize generic information
void EnemyShooter::Init() {
	shipLines.reserve(ENEMY_SHOOTER_LINE_COUNT);
	speed = ENEMY_SHOOTER_SPEED;
	pointValue = 1000;
}


// create the lines that will be used to draw later on
// this specific ship is simply lines that are evenly rotated based on the ENEMY_SHOOTER_LINE_COUNT
void EnemyShooter::CreateShipLines() {
	// clear the vector
	shipLines.clear();
	
	// initial direction
	Vec2 dir = Vec2(0.0f, radius);

	// creates equally spaced lines based on how many lines you want for the starlike enemy
	for (int i = 0; i < ENEMY_SHOOTER_LINE_COUNT; i++) {
		// creates the line
		Line nextLine = Line(spherePos, spherePos + dir);
		// add to vector
		shipLines.push_back(nextLine);

		// rotate the direction vec2 for the next line!
		dir = VMath::Rotate(dir, 360.0f / ENEMY_SHOOTER_LINE_COUNT);
	}
}

// this enemy has simple movement, doesn't need to be overridden for this specific case,
// but I'd like to see how the enemy moves inside the enemyShooter instead of BaseEnemy
void EnemyShooter::Update(float dt_) {
	spherePos += dir * dt_ * speed;
}
