#pragma once

#include "Shape.h"
#include "/PingPong/PingPong/Utils/Vector2D.h"



class Circle : public Shape {

public:
	Circle();
	Circle(const Vector2D& centerPoint, float radius);

	inline float GetRadius() const { return mRadius; }
	inline void SetRadius(float radius) { mRadius = radius; }

	bool ContainPoint(const Vector2D& point) const;
	bool Intersect(const Circle& otherCircle) const;

	void MoveBy(const Vector2D& offset);
	void MoveTo(const Vector2D& position);

	inline virtual Vector2D GetCenterPoint() const override { return mPoints[0]; }

private:
	float mRadius;
};