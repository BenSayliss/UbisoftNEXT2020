#ifndef VECTORS_H
#define VECTORS_H

// defining some useful math items
#define VERY_SMALL 1.0e-7f
#define PI 3.14159265358979323f
#define DEGREES_TO_RADIANS PI / 180.0f


#include <math.h>

// this class contains a Vec2 struct, Vec3 struct, and a VMath struct used for performing equations
// Vector 2: (x, y)
struct Vec2 {
	// variables - x, y
	float x, y;

	// constructor that zeros x and y
	inline Vec2() {
		x = y = 0;
	}
	// contructor that sets x and y to the same one value
	inline Vec2(float s_) {
		x = s_;
		y = s_;
	}
	// constructor that sets x and y to their own values
	inline Vec2(float x_, float y_) {
		x = x_;
		y = y_;
	}
	// copy constructor
	inline Vec2(const Vec2 & v_) {
		x = v_.x;
		y = v_.y;
	}

	// overload operators
	// overload the assignment operator
	inline Vec2& operator = (const Vec2& v_) {
		x = v_.x;
		y = v_.y;
		return *this;
	}

	// addition
	// overload the + operator
	inline const Vec2 operator + (const Vec2 v_) const{
		return Vec2(x + v_.x, y + v_.y);
	}
	// overload the += operator
	inline Vec2& operator += (const Vec2& v_) {
		x += v_.x;
		y += v_.y;
		return *this;
	}

	// subtraction
	// overload the - operator
	inline const Vec2 operator - (const Vec2 v_) const{
		return Vec2(x - v_.x, y - v_.y);
	}
	// overload the -= operator
	inline Vec2& operator -= (const Vec2& v_) {
		x -= v_.x;
		y -= v_.y;
		return *this;
	}

	// multiplication
	// multiplies x and y of vec2 by a scalar
	// overload the * operator
	inline const Vec2 operator * (const float s_) const {
		return Vec2(x * s_, y * s_);
	}
	// overload the *= operator
	inline Vec2& operator *= (const float& s_) {
		x *= s_;
		y *= s_;
		return *this;
	}

	// division
	// divides x and y of vec2 by a scalar
	// overload the / operator
	inline const Vec2 operator / (const float s_) const {
		return Vec2(x / s_, y / s_);
	}
	// overload the /= operator
	inline Vec2& operator /= (const float& s_) {
		x /= s_;
		y /= s_;
		return *this;
	}
};

// stuct for Vec3 - contains x, y, z
// so far just used to hold 3 floats for something such as RGB values
struct Vec3 {
	// member variables - they are public for ease of use
	float x, y, z;

	// default constructor - zeros out x, y, z
	inline Vec3() {
		x = y = z = 0.0f;
	}

	// constructor that individually sets x, y, z
	inline Vec3(float x_, float y_, float z_) {
		x = x_;
		y = y_;
		z = z_;
	}

	// constructor that sets x, y, z to the same s_ value
	inline Vec3(float s_) {
		x = y = z = s_;
	}

	// copy constructor
	inline Vec3(const Vec3& v_) {
		x = v_.x;
		y = v_.y;
		z = v_.z;
	}

	// overload the assignment operator ('=')
	inline Vec3& operator = (const Vec3& v_) {
		x = v_.x;
		y = v_.y;
		z = v_.z;
		return *this;
	}
};

// struct that contains mathematical functions
// only using math on vec2s
struct VMath {
	// other functions
	// returns the magnitude of a vec2
	inline static float Magnitude(const Vec2 v_) {
		return sqrt(v_.x * v_.x + v_.y * v_.y);
	}

	// returns a normalized vec2
	inline static const Vec2 Normalize(const Vec2 v_) {
		return Vec2(v_.x / Magnitude(v_), v_.y / Magnitude(v_));
	}

	// returns the dot product of two vec2s
	inline static float Dot(const Vec2 v1_, const Vec2 v2_) {
		return (v1_.x * v2_.x + v1_.y * v2_.y);
	}

	// rotates a vec2 (counter-clockwise) based on an angle (in degrees)
	// the function will handle conversion to radians!
	inline static const Vec2 Rotate(const Vec2 v_, float angle_) {
		// convert angle to radians
		float angle = angle_ * DEGREES_TO_RADIANS;
		return Vec2(v_.x * cos(angle) - v_.y * sin(angle),
					v_.x * sin(angle) + v_.y * cos(angle));
	}
};


#endif