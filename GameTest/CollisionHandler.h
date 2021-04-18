#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Vectors.h"
#include "Sphere.h"

// This struct is a singleton and will deal with collision between objects
struct CollisionHandler
{
	// delete the copy and move constructors
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator = (const CollisionHandler&) = delete;
	CollisionHandler& operator = (CollisionHandler&&) = delete;

	// return the instance
	static CollisionHandler* GetInstance();

	// simple sphere point collision
	static bool SpherePointCollision(Sphere* s_, Vec2 pt_);
	// simple sphere sphere collision
	static bool SphereSphereCollision(Sphere* s1_, Sphere* s2_);

private:
	// private constructor so you cannot create an object of type CollisionHandler
	CollisionHandler();
	// private destructor
	~CollisionHandler();

	// pointer for containing the instance of CollisionHandler
	static std::unique_ptr<CollisionHandler> collisionHandlerInstance;
	// default delete function for the above pointer ^^
	friend std::default_delete<CollisionHandler>;
	
};
#endif

