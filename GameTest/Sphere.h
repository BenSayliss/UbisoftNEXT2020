#ifndef SPHERE_H
#define SPHERE_H

#include "Vectors.h"

// All the game objects inherit from sphere
class Sphere {
public:
	// returns the position of the sphere
	inline Vec2 GetSpherePos() {
		return spherePos;
	}

	// sets the position of the sphere
	inline void SetSpherePos(Vec2 pos_) {
		spherePos = pos_;
	}

	// returns the radius of the sphere
	inline float GetRadius() {
		return radius;
	}

	// sets the radius of the sphere
	inline void SetRadius(float radius_) {
		radius = radius_;
	}

protected:
	// sphere position
	Vec2 spherePos;
	// sphere radius
	float radius;
};
#endif
