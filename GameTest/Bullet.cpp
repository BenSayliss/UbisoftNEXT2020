#include "stdafx.h"
#include "Bullet.h"

// constructor that takes in a vec2 position, vec2 direction, and vec2 ending location
Bullet::Bullet(Vec2 pos_, Vec2 dir_, Vec2 endLoc_) {
	if (sprite == nullptr) {
		sprite = App::CreateSprite(".\\TestData\\bulletsBlue.bmp", 1, 8);
	}
	spherePos = pos_;
	dir = dir_;
	endLoc = endLoc_;
	Init();
}

// constructor that takes in a vec2 position, vec2 direction, vec2 ending location, a sprite fileName (as well as column and row)
Bullet::Bullet(Vec2 pos_, Vec2 dir_, Vec2 endLoc_, char* fileName_, int column_, int row_) {
	if (sprite == nullptr) {
		sprite = App::CreateSprite(fileName_, column_, row_);
	}
	spherePos = pos_;
	dir = dir_;
	endLoc = endLoc_;
	Init();
}

// Initialize other attributes
void Bullet::Init() {
	speed = BASE_BULLET_SPEED;
	sprite->SetPosition(spherePos.x, spherePos.y);
	sprite->SetScale(2.0f);
	SetRadius(10.0f);
}

// destructor - deallocate memory for the CSimpleSprite pointer
Bullet::~Bullet() {
	delete sprite;
	sprite = nullptr;
}

// draws the bullet based on the sprite
void Bullet::DrawBullet() {
	sprite->Draw();	
}

// updates the movement based on deltaTime and the sprite's positiong
void Bullet::Update(float dt_) {
	spherePos += dir * dt_ * speed;
	sprite->SetPosition(spherePos.x, spherePos.y);
}

// returns vec2 dir
Vec2 Bullet::GetDir() {
	return dir;
}

// returns float speed
float Bullet::GetSpeed() {
	return speed;
}

// returns vec2 endLoc
Vec2 Bullet::GetEndLoc() {
	return endLoc;
}

// sets vec2 dir
void Bullet::SetDir(Vec2 dir_) {
	dir = dir_;
}

// sets float speed
void Bullet::SetSpeed(float speed_) {
	speed = speed_;
}

// sets vec2 endLoc
void Bullet::SetEndLoc(Vec2 endLoc_) {
	endLoc = endLoc_;
}

// sets the scale of the sprite
void Bullet::SetSpriteScale(float scale_) {
	sprite->SetScale(scale_);
}