#include "stdafx.h"
#include "Ship.h"

// default constructor
Ship::Ship() {
	// resever space for vectors
	shipLines.reserve(SHIP_LINE_COUNT);
	bullets.reserve(20);

	Init();
}

// destructor
Ship::~Ship() {
	OnDestroy();
}

// called from destructor
void Ship::OnDestroy() {
	// as long as bullets aren't empty
	if (!bullets.empty()) {
		// deallocate memory for bullet pointers
		for (auto b : bullets) {
			delete b;
			b = nullptr;
		}
		// clear vector
		bullets.clear();
	}
	// clear vector
	shipLines.clear();
}

// initalize generic attributes
void Ship::Init()
{
	// set starting attributes
	lives = STARTING_LIVES;
	pos = 0;
	movementTimer = MOVEMENT_TIMER;
	shootingTimer = SHOOTING_TIMER;

	colourR = colourG = colourB = 255.0f;
}

// Math behind creating the ship's lines based on the level! is drawn later
// basically it is find direction, find rotation, create line, update prevLine!
void Ship::CreateShipLines(Level* l_) {
	// first clear the previous ship's lines
	shipLines.clear();
	// create the ship based off of the level's front lines
	// find the direction
	Vec2 dir = l_->GetFrontLines().at(pos).end - l_->GetFrontLines().at(pos).start;

	// rotate direction - clockwise 30 deg.
	dir = VMath::Rotate(dir, -30.0f);

	// CREATE HELPER METHOD BEN
	// First Line
	Line oldLine = Line(l_->GetFrontLines().at(pos).start, l_->GetFrontLines().at(pos).start + dir / 2.0f);
	shipLines.push_back(oldLine);

	// Second Line
	Line nextLine = Line(oldLine.end, l_->GetFrontLines().at(pos).end);
	oldLine = nextLine;
	shipLines.push_back(oldLine);

	// Third Line
	dir = VMath::Rotate(dir, 180.0f);
	nextLine = Line(oldLine.end, oldLine.end + dir / 3.0f);
	oldLine = nextLine;
	shipLines.push_back(oldLine);

	// Fourth Line
	dir = VMath::Rotate(dir, 170.0f);
	nextLine = Line(oldLine.end, oldLine.end + dir / 3.8f);
	oldLine = nextLine;
	shipLines.push_back(oldLine);

	// Fifth Line
	dir = VMath::Rotate(dir, -120.0f);
	nextLine = Line(oldLine.end, oldLine.end + dir / 2.0f);
	oldLine = nextLine;
	shipLines.push_back(oldLine);

	// Sixth Line
	dir = VMath::Rotate(dir, -45.0f);
	nextLine = Line(oldLine.end, oldLine.end + dir / 2.5f);
	oldLine = nextLine;
	shipLines.push_back(oldLine);

	// Seventh Line
	dir = VMath::Rotate(dir, -110.0f);
	nextLine = Line(oldLine.end, oldLine.end + dir / 3.5f);
	oldLine = nextLine;
	shipLines.push_back(oldLine);

	// Eigth Line
	nextLine = Line(oldLine.end, l_->GetFrontLines().at(pos).start);
	oldLine = nextLine;
	shipLines.push_back(oldLine);

	// Lines that go from the ship into the back of the screen
	oldLine = Line(l_->GetFrontLines().at(pos).start, l_->GetBackLines().at(pos).start);
	shipLines.push_back(oldLine);

	oldLine = Line(l_->GetFrontLines().at(pos).end, l_->GetBackLines().at(pos).end);
	shipLines.push_back(oldLine);

	// set position
	spherePos = (l_->GetFrontLines().at(pos).start + l_->GetFrontLines().at(pos).end) / 2.0f;

	// Testing Radius
	//shipLines.push_back(Line(spherePos, Vec2(spherePos.x - radius, spherePos.y)));
}

// return the shipLines vector
std::vector<Line> Ship::GetShipLines() {
	return shipLines;
}

// draw the ship
void Ship::Draw() {
	// as long as the vectors aren't empty, draw the ship and bullets!
	if (!shipLines.empty()) {
		for (int i = 0; i < shipLines.size(); i++) {
			App::DrawLine(shipLines.at(i).start, shipLines.at(i).end, colourR, colourG, colourB);
		}
	}
	if (!bullets.empty()) {
		for (auto b : bullets) {
			b->DrawBullet();
		}
	}
}

// change the ship's position (left)
// remember the pos is based on the Level::frontLevelLines iterator's position!
void Ship::MoveShipLeft() {
	// jump to the end of the 
	if (pos == 0) {
		pos = LEVEL_LINE_COUNT - 1;
	}
	else {
		pos--;
	}
}

// change the ship's position (left)
// remember the pos is based on the Level::frontLevelLines iterator's position!
void Ship::MoveShipRight() {
	if (pos == LEVEL_LINE_COUNT - 1) {
		pos = 0;
	}
	else {
		pos++;
	}
}

// Shoot a projectile based on the pos and level you're in
void Ship::Shoot(Level* l_) {
	// find the middle of the line the ship is on
	Vec2 bulletPos = (l_->GetFrontLines().at(pos).end + l_->GetFrontLines().at(pos).start) / 2.0f;
	Vec2 bulletDir = (l_->GetBackLines().at(pos).end + l_->GetBackLines().at(pos).start) / 2 - bulletPos;
	// each bullet knows where it's end is
	Bullet* b = new Bullet(bulletPos, bulletDir, Vec2((l_->GetBackLines().at(pos).end + l_->GetBackLines().at(pos).start) / 2));
	bullets.push_back(b);
	
}

void Ship::Update(float dt_) {
	// dealing with the ship's bullets
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets.at(i)->Update(dt_);
			// MY NEXT STEP WOULD BE TO CHANGE THE COLLISION SYSTEM AND INCLUDE SPATIAL PARTITIONING
			// It is rather costly to loop through every bullet and check to see if it collides with every enemy
			// see if any bullet collide with any enemy (not ideal at all, sorry!)
			for (int j = 0; j < EnemyManager::GetInstance()->GetEnemies().size(); j++) {
				if (CollisionHandler::GetInstance()->SphereSphereCollision(bullets.at(i),
					EnemyManager::GetInstance()->GetEnemies().at(j))) {
					// Add points
					score += EnemyManager::GetInstance()->GetEnemies().at(j)->GetPointValue();
					// destroy the enemy
					EnemyManager::GetInstance()->RemoveEnemy(j);
					// destroy the bullet
					RemoveBullet(i);
					break;
				}
			}
			// stops out of bounds exceptions!
			if (!bullets.empty() && i < bullets.size()) {
				if (bullets.at(i) != nullptr) {
					if (CollisionHandler::GetInstance()->SpherePointCollision(bullets.at(i), bullets.at(i)->GetEndLoc())) {
						RemoveBullet(i);
					}
				}
			}
		}
	}
}

// return int pos
int Ship::GetPos() {
	return pos;
}

// return int movement timer
int Ship::GetMovementTimer() {
	return movementTimer;
}

// return int shooting timer
int Ship::GetShootingTimer() {
	return shootingTimer;
}

// reset the movement timer
void Ship::ResetMovementTimer() {
	movementTimer = MOVEMENT_TIMER;
}

// reset the shooting timer
void Ship::ResetShootingTimer() {
	shootingTimer = SHOOTING_TIMER;
}

// decrease the movement timer by 1
void Ship::DecrementMovementTimer() {
	movementTimer--;
}

// decrease the shooting timer by 1
void Ship::DecrementShootingTimer() {
	shootingTimer--;
}

// set the rgbvalues based on 3 floats
void Ship::SetRGBValues(float r_, float g_, float b_) {
	colourR = r_;
	colourG = g_;
	colourB = b_;
}

// set the rgb values based on vec3
void Ship::SetRGBValues(Vec3 rgb_)
{
	colourR = rgb_.x;
	colourG = rgb_.y;
	colourB = rgb_.z;
}

// returns vec3 rgb values
Vec3 Ship::GetRGBValues() {
	return Vec3(colourR, colourG, colourB);
}

// helper method for removing a bullet and properly deallocating the memory
void Ship::RemoveBullet(int i_)
{
	delete bullets.at(i_);
	bullets.at(i_) = nullptr;
	bullets.erase(bullets.begin() + i_);
}

// return int lives
int Ship::GetLives() {
	return lives;
}

// return int score
int Ship::GetScore()
{
	return score;
}

// increase lives by 1
void Ship::IncrementLives()
{
	if (lives < STARTING_LIVES) {
		lives++;
	}
}

// decrease lives by 1, should call GAME OVER when lives !> 0
void Ship::DecrementLives()
{
	if (lives > 0) {
		lives--;
	}
	// this is just for testing purposes, should normally be GAME OVER
	else {
		ResetLives();
	}
}

// resets lives to STARTING_LIVES
void Ship::ResetLives()
{
	lives = STARTING_LIVES;
}

