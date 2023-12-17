#pragma once

#include "Shape.h"
#include "../Utils/Vector2D.h"

class Rectangle : public Shape {
public:
	Rectangle();
	Rectangle(const Vector2D& point, float width, float height);
	Rectangle(const Vector2D& topLeftPoint, const Vector2D& bottomRightPoint);

	float GetWidth() const;
	float GetHeight() const;

	bool ContainsPoint(const Vector2D& point) const;
	bool Intersect(const Rectangle& otherRectangle) const;

	void MoveBy(const Vector2D& offset);
	void MoveTo(const Vector2D& position);

	inline Vector2D GetTopLeftPoint() const { return mPoints[0]; }
	inline Vector2D GetBottomRightPoint() const { return mPoints[1]; }

	virtual Vector2D GetCenterPoint() const override;
	virtual std::vector<Vector2D> GetPoints() const override;

};