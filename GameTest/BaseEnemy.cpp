#include "stdafx.h"
#include "BaseEnemy.h"

BaseEnemy::BaseEnemy() {}

// constructor that takes in a float radius and rgb values stored in a vec3
BaseEnemy::BaseEnemy(float r_, Vec3 rgb_) {
	// set radius
	SetRadius(r_);	
	// set rgb value
	SetRGBValues(rgb_);
}

// constructor that takes in a vec2 position, vec2 direction, and float radius
BaseEnemy::BaseEnemy(Vec2 pos_, Vec2 dir_, float r_) {
	// set position
	SetSpherePos(pos_);
	// set radius
	SetRadius(r_);
	// set direction
	SetDir(dir_);
}
// constructor that takes in a vec2 position, vec2 direction, and float radius, and vec3 rgb values
BaseEnemy::BaseEnemy(Vec2 pos_, Vec2 dir_, float r_, Vec3 rgb_) {
	// set position
	SetSpherePos(pos_);
	// set radius
	SetRadius(r_);
	// set direction
	SetDir(dir_);
	// sets the RGBValues
	SetRGBValues(rgb_);
}

// destructor
BaseEnemy::~BaseEnemy() {
	OnDestroy();
}

// called when the destructor is called
void BaseEnemy::OnDestroy() {
	// clear the vector
	shipLines.clear();
}

// sets the rgb values based on 3 floats
void BaseEnemy::SetRGBValues(float r_, float g_, float b_) {
	colourR = r_;
	colourG = g_;
	colourB = b_;
}

// set the rgb values based on a vec3
void BaseEnemy::SetRGBValues(Vec3 rgb_) {
	colourR = rgb_.x;
	colourG = rgb_.y;
	colourB = rgb_.z;
}

// returns a vec3 containing the R, G, B values
Vec3 BaseEnemy::GetRGBValues() {
	return Vec3(colourR, colourG, colourB);
}

// sets the vec2 direction
void BaseEnemy::SetDir(Vec2 dir_)
{
	dir = dir_;
}

// sets the vec2 endLoc
void BaseEnemy::SetEndLoc(Vec2 endLoc_)
{
	endLoc = endLoc_;
}

// Updates movement - is usually overridden
void BaseEnemy::Update(float dt_) {
	spherePos += dir * dt_ * speed;
}

// sets the speed based on a float
void BaseEnemy::SetSpeed(float s_) {
	speed = s_;
}

// returns the vec2 endLoc
Vec2 BaseEnemy::GetEndLoc()
{
	return endLoc;
}

// returns the int pointValue
int BaseEnemy::GetPointValue()
{
	return pointValue;
}

// Draws each line in the shipLines vector! - Draws the enemy
void BaseEnemy::Draw() {
	if (!shipLines.empty()) {
		for (int i = 0; i < shipLines.size(); i++) {
			App::DrawLine(shipLines.at(i).start, shipLines.at(i).end, colourR, colourG, colourB);
		}
	}
}