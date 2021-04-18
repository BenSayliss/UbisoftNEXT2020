#include "stdafx.h"
#include "EnemyShip.h"

// constructor that takes in an int for pos
EnemyShip::EnemyShip(int pos_) {
	shipLines.reserve(SHIP_LINE_COUNT);
	// changed based on how fast you're shooting bullets
	bullets.reserve(10);

	pos = pos_;
}

// destructor
EnemyShip::~EnemyShip() {
	OnDestroy();
}

// called from destructor
void EnemyShip::OnDestroy() {
	// as long as the bullets vector isn't empty,
	if (!bullets.empty()) {
		// properly deallocate memory 
		for (auto b : bullets) {
			delete b;
			b = nullptr;
		}
		// clear the vector
		bullets.clear();
	}
	// clear the vector, no pointers so no need to deallocate memory as above
	shipLines.clear();
}

// shoots at the ship!
void EnemyShip::Shoot(Ship* s_, Level* l_) {
	// find the direction to the ship
	Vec2 bulletDir = s_->GetSpherePos() - spherePos;
	
	// add a bullet
	// the bullet has a position, direction, ending position, and sprite fileName (and column and row for sprite)
	Bullet* b = new Bullet(spherePos, bulletDir, Vec2(s_->GetSpherePos()), ".\\TestData\\bulletsRed.bmp", 1, 7);

	// set some bullet variables
	b->SetSpeed(b->GetSpeed() / 3.0f);
	b->SetRadius(15.0f); 
	b->SetSpriteScale(3.0f);
	
	// add bullet to vector bullets
	bullets.push_back(b);
}

// resets the timer randomly based on defined constraints!
void EnemyShip::ResetShootingTimer() {
	// ensures randomness!
	srand(time(0));
	float randNum = (rand() % (ENEMY_SHOOTING_TIMER_MAX - ENEMY_SHOOTING_TIMER_MIN)) + ENEMY_SHOOTING_TIMER_MIN;
	// set timer
	shootingTimer = randNum;
}

// updates the bullets for the ship!
void EnemyShip::Update(float dt_, Ship* s_) {
	// dealing with the ship's bullets
	if (!bullets.empty()) {
		// for each bullet
		for (int i = 0; i < bullets.size(); i++) {
			// update the bullet position
			bullets.at(i)->Update(dt_);

			// check for collision with ship
			if (CollisionHandler::GetInstance()->SphereSphereCollision(bullets.at(i), s_)) {
				// decrease player's lives
				s_->DecrementLives();
				// Remove the bullet from the bullets vector and properly deallocates memory
				RemoveBullet(i);
			}

			// check for collision with edge of level
			else if (CollisionHandler::GetInstance()->SpherePointCollision(bullets.at(i), bullets.at(i)->GetEndLoc())) {
				// Remove the bullet from the bullets vector and properly deallocates memory
				RemoveBullet(i);
			}
		}
	}
}