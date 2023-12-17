#pragma once

#include "../Utils/Vector2D.h"

class Line {

public:
	Line();
	Line(const Vector2D& p0, const Vector2D& p1);

	inline const Vector2D& GetP0() const { return mP0; }
	inline const Vector2D& GetP1() const { return mP1; }
	inline void SetP0(const Vector2D& p0) { mP0 = p0; }
	inline void SetP1(const Vector2D& p1) { mP1 = p1; }

	Vector2D MidPoint() const;
	float Length() const;
	float Slope() const;

	float MinDistanceFrom(const Vector2D& point);
	Vector2D ClosestPoint(const Vector2D& point);

private:
	Vector2D mP0;
	Vector2D mP1;
};