#include "stdafx.h"
#include "CollisionHandler.h"

// for static variables
std::unique_ptr<CollisionHandler> CollisionHandler::collisionHandlerInstance = nullptr;

// default constructor
CollisionHandler::CollisionHandler() {}

// default destructor
CollisionHandler::~CollisionHandler() {}

// returns the instance of the CollisionHandler
// assures there will only ever be one instance as this is the only way it is created
CollisionHandler* CollisionHandler::GetInstance() {
	// if there is no current instance, 
	if (collisionHandlerInstance.get() == nullptr) {
		// create one
		collisionHandlerInstance.reset(new CollisionHandler);
	}
	// return the instance
	return collisionHandlerInstance.get();
}

// simple sphere point collision
bool CollisionHandler::SpherePointCollision(Sphere* s_, Vec2 pt_) {
	// find the distance of the two vectors by subtracting them then finding their length (magnitude)
	float distance = VMath::Magnitude(s_->GetSpherePos() - pt_);
	// if the distance is less than the sphere's radius, there is a collision
	if (distance < s_->GetRadius()) {
		return true;
	}
	// otherwise no collision
	return false;
}

// sphere sphere collision - very similar to above, this time using two radius when you check
bool CollisionHandler::SphereSphereCollision(Sphere* s1_, Sphere* s2_) {
	// find the distance of the two vectors by subtracting them then finding their length (magnitude)
	float distance = VMath::Magnitude(s1_->GetSpherePos() - s2_->GetSpherePos());
	// if the distance is less than both spheres' radius, there is a collision
	if (distance < s1_->GetRadius() + s2_->GetRadius()) {
		return true;
	}
	// otherwise no collision
	return false;
}