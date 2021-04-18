//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "LevelBuilder.h"
#include "EnemyShip.h"
#include "StatTracker.h"
#include "EnemyManager.h"
#include "EnemyShooter.h"

#include <string>
// initialize variables for scope of GameTest.cpp
// pointers so we can control how we use memory!
Level* level = new Level();
Ship* ship = new Ship();
// this 8 is the opposite position as the ship, should make it dynamic though vv
EnemyShip* enemyShip = new EnemyShip(8);

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	// create the initial level, and initial ship lines!
	level = LevelBuilder::GetInstance()->CreateLevel(0);
	ship->CreateShipLines(level);
	ship->SetRadius(25.0f);
	ship->SetRGBValues(0.8f, 0.8f, 0.2f);
	enemyShip->CreateShipLines(level);
	enemyShip->SetRGBValues(0.9f, 0.0f, 0.0f);
	
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	// Controls!
	// move left
	if (App::IsKeyPressed('A') && ship->GetMovementTimer() == 0) {
		// move by changing the ship's position
		ship->MoveShipLeft();
		// redraw the ship
		ship->CreateShipLines(level);
		ship->ResetMovementTimer();

		// move the enemyShip
		enemyShip->MoveShipLeft();
		enemyShip->CreateShipLines(level);
	}
	// move right
	if (App::IsKeyPressed('D') && ship->GetMovementTimer() == 0) {
		// move by changing the ship's position
		ship->MoveShipRight();
		// redraw the ship
		ship->CreateShipLines(level);
		ship->ResetMovementTimer();

		// move the enemyShip
		enemyShip->MoveShipRight(); 
		enemyShip->CreateShipLines(level);
		
	}

	// shoot
	if (App::IsKeyPressed('S') && ship->GetShootingTimer() == 0) {
		// create and shoot a bullet
		ship->Shoot(level);
		ship->ResetShootingTimer();
	}

	// decrease ship's movement timer
	if (ship->GetMovementTimer() > 0) {
		ship->DecrementMovementTimer();
	}

	// decrease ship's shooting timer
	if (ship->GetShootingTimer() > 0) {
		ship->DecrementShootingTimer();
	}

	// enemy ship shooting
	if (enemyShip->GetShootingTimer() > 0) {
		enemyShip->DecrementShootingTimer();
	}
	else {
		enemyShip->Shoot(ship, level);
		enemyShip->ResetShootingTimer();
	}

	ship->Update(deltaTime);
	enemyShip->Update(deltaTime, ship);

	// other enemies (EnemyManager)
	EnemyManager::GetInstance()->CreateEnemies(level);
	EnemyManager::GetInstance()->Update(deltaTime, ship);

	// GAME OVER
	if (ship->GetLives() == 0) {
		// SHUTDOWN
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	// draw level
	level->DrawLevel();

	// draw stats
	StatTracker::GetInstance()->DrawInfo(ship);

	// draw ship
	ship->Draw();

	// draw enemy ship
	enemyShip->Draw();

	// draw rest of enemies (EnemyManager)
	EnemyManager::GetInstance()->DrawEnemies();

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	// properly deallocate pointers!
	delete level;
	level = nullptr;

	delete ship;
	ship = nullptr;

	delete enemyShip;
	enemyShip = nullptr;

	// deallocates enemy classes! enemyShip is an exception
	EnemyManager::GetInstance()->RemoveAllEnemies();
}