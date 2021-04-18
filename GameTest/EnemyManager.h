#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

// how many different enemy types, just add more types and changes this number!
// also have to update AddEnemy with a new switch case and what kind of enemy to spawn there!
#define NUM_ENEMY_TYPES 1

// values to randomize the speed of generating new enemies
#define ENEMY_GENERATOR_TIMER_MIN 30
#define ENEMY_GENERATOR_TIMER_MAX 60

#include "EnemyShooter.h"

// needed to include these to avoid circular dependancy
class Ship;
class Level;

// Singleton - we only want one instance of the stat tracker
struct EnemyManager {
	// delete the copy and move constructors
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator = (const EnemyManager&) = delete;
	EnemyManager& operator = (EnemyManager&&) = delete;

	// returns instance of EnemyManager
	static EnemyManager* GetInstance();

	// returns the vector containing all the current enemies
	static std::vector<BaseEnemy*> GetEnemies();
	
	// function that creates enemies based on a level! needs to be called every frame
	static void CreateEnemies(Level* l_);

	// reset the timer for spawning enemies
	static void ResetTimer();

	// add an enemy based on the level and the enemy type! - just one for now
	static void AddEnemy(Level* l_, int type_);
	// remove an enemy based in an index (for enemies vector)
	static void RemoveEnemy(int i_);
	// remove all the enemies
	static void RemoveAllEnemies();

	// update based on deltaTime and the player ship, eventually I would like a better collision system as well as include spatial partitioning!
	static void Update(float dt_, Ship* s_);

	// draw all the enemies 
	static void DrawEnemies();
private:
	// private constructor so you cannot create an object of type EnemyManager
	EnemyManager();
	// private destructor
	~EnemyManager();

	// pointer for containing the instance of EnemyManager
	static std::unique_ptr<EnemyManager> enemyManagerInstance;
	// default delete function for the above pointer ^^
	friend std::default_delete<EnemyManager>;

	// this vector will hold a pointer to each type of enemy
	// allows me to cycle through here and pull out a random enemy type to add to the level
	static std::vector<BaseEnemy*> enemies;
	
	// integer for a timer for spawning enemies
	static int timer;
};

#endif