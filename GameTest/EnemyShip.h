#ifndef ENEMY_H
#define ENEMY_H 

// define min and max for a shooting timer
#define ENEMY_SHOOTING_TIMER_MIN 20
#define ENEMY_SHOOTING_TIMER_MAX 70

#include "Ship.h"

// This specific enemy mimics a ship!
class EnemyShip : public Ship
{
public:
	// constructor that takes in a pos (this pos is related to the level's line locations, and affect how it is being drawn
	EnemyShip(int pos_);
	// destructor
	~EnemyShip();
	// on destroy method
	void OnDestroy();

	// shoots based on the player's ship and level!
	void Shoot(Ship* s_, Level* l_);
	// resets the shooting timer
	void ResetShootingTimer();
	// updates based on deltaTime and checks the enemyShip's bullets' collision
	void Update(float dt_, Ship* s_);


};
#endif