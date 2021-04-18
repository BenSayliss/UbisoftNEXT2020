#include "stdafx.h"
#include "EnemyManager.h"
// to get around circular dependency
#include "Ship.h"

// static variables
std::unique_ptr<EnemyManager> EnemyManager::enemyManagerInstance = nullptr;
std::vector<BaseEnemy*> EnemyManager::enemies = std::vector<BaseEnemy*>();
int EnemyManager::timer = ENEMY_GENERATOR_TIMER_MIN;

EnemyManager::EnemyManager() {
	// this should be updated based on how many enemies you are planning on spawning in
	enemies.reserve(20);
}

EnemyManager::~EnemyManager() {}

// return instance of EnemyManager
EnemyManager* EnemyManager::GetInstance() {
	// if there isn't already an instance,
	if (enemyManagerInstance.get() == nullptr) {
		// create one
		enemyManagerInstance.reset(new EnemyManager);
	}
	// return the EnemyManager instance
	return enemyManagerInstance.get();
}

// return the vector for all the enemies created
std::vector<BaseEnemy*> EnemyManager::GetEnemies()
{
	return enemies;
}

// Create enemies based on a timer
void EnemyManager::CreateEnemies(Level* l_) {
	// once the timer hits 0,
	if (timer < 0) {
		// ensures random numbers (based on computer's clock)
		srand(time(0));
		// random number for which enemy type! - just one for now
		float randNum = (rand() % NUM_ENEMY_TYPES);
		// adds an enemy based on the level and a random type
		AddEnemy(l_, randNum);
		// reset the timer
		ResetTimer();
	}
	
}

// resets the enemy generation timer
void EnemyManager::ResetTimer() {
	// ensures randomness
	srand(time(0));
	// random number between min and max values
	float randNum = (rand() & (ENEMY_GENERATOR_TIMER_MAX - ENEMY_GENERATOR_TIMER_MIN)) + ENEMY_GENERATOR_TIMER_MIN;
	// set timer to random number
	timer = randNum;
}

// add an enemy to the vector of enemies
void EnemyManager::AddEnemy(Level* l_, int type_) {	
	// switch case for which type of enemy - only one for now
	// base enemy needs to be declared first! remember you can't create an object of type BaseEnemy though!
	BaseEnemy* e;
	// only one case right now, each case would initialize e as a different enemy class
	switch (type_) {
	default:
		e = new EnemyShooter(15.0f, Vec3(0.1f, 0.2f, 0.8f));
		break;
	}
	// set position based on the level's backLevelLines
	srand(time(0));
	// randomNum from 0 - LEVEL_LINE_COUNT
	int randNum = (rand() % LEVEL_LINE_COUNT);

	// set the spawn position
	Vec2 pos = (l_->GetBackLines().at(randNum).start + l_->GetBackLines().at(randNum).end) / 2.0f;
	// set its ending position
	Vec2 endPos = (l_->GetFrontLines().at(randNum).start + l_->GetFrontLines().at(randNum).end) / 2.0f;
	// set its direction path
	Vec2 dir = endPos - pos;

	// set other variables
	e->SetSpherePos(pos);
	e->SetDir(dir);
	e->SetSpeed(ENEMY_SHOOTER_SPEED);
	e->SetEndLoc(endPos);
	// create the lines for the ship! - this stores all the lines in the enemy's shipLines vector which are pulled from later to draw based off of!
	e->CreateShipLines();
	// push to enemies vector
	enemies.push_back(e);
}

// remove an enemy based on the index they are at in the vector
void EnemyManager::RemoveEnemy(int i_) {
	// delete the enemy at i_ in vector
	delete enemies.at(i_);
	// sets thatt memory location null
	enemies.at(i_) = nullptr;
	// erase that enemy from the vector so the size is accurate - not doing this well give out of bounds exceptions!
	enemies.erase(enemies.begin() + i_);
}

// clears the enemies 
void EnemyManager::RemoveAllEnemies() {
	// deallocates memory for each enemy pointer
	for (auto e : enemies) {
		delete e;
		e = nullptr;
	}
	// clears the vector
	enemies.clear();	
}

// checks collision with each enemy and the ship
void EnemyManager::Update(float dt_, Ship* s_) {
	// as long as the vector isn't empty
	if (!enemies.empty()) {
		// cycle through each enemy
		for (int i = 0; i < enemies.size(); i++) {
			enemies.at(i)->CreateShipLines();
			enemies.at(i)->Update(dt_);
			// collision check
			if (CollisionHandler::GetInstance()->SphereSphereCollision(enemies.at(i), s_)) {
				// take off one live
				s_->DecrementLives();

				// remove enemy
				RemoveEnemy(i);
			}
			// if the enemy collides with its end location
			else if (CollisionHandler::GetInstance()->SpherePointCollision(enemies.at(i), enemies.at(i)->GetEndLoc())) {
				// Remove enemy
				RemoveEnemy(i);
			}
		}
	}
	// decrement timer
	timer--;
}

// draw all the enemies in the enemies vector
void EnemyManager::DrawEnemies() {
	if (!enemies.empty()) {
		for (auto e : enemies) {
			e->Draw();
		}
	}
}